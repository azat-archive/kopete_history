/**
 * Merger
 *
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 */

#include "merger.h"

#include <QDomDocument>
#include <QMap>

Merger::Merger(QObject *parent) : QObject(parent) {
}

void Merger::addPath(const QString& path) {
	if (paths.contains(path)) {
		throw MergerException("Path '" + path + "'' already added");
	}
	paths.push_back(path);
}

void Merger::setPaths(QStringList& paths) {
	paths = paths;
}

long Merger::run(const QDir& saveTo) {
	if (paths.count() < 2) {
		throw MergerException("First you must add more than or equal two path");
	}

	// saveTo directory is not empty
	if (!isDirectoryEmpty(saveTo)) {
		throw MergerException("Folder '" + saveTo.path() + "' is not empty");
	}

	int i = 0;
	messages = 0;

	foreach (QString path, paths) {
		if (++i == 1) {
			copyDirectoryRecursive(path, saveTo);
		} else {
			messages += mergeDirectoryRecursive(path, saveTo);
		}
	}

	return messages;
}

void Merger::copyDirectoryRecursive(const QDir from, const QDir to) {
	if (!to.Writable) {
		throw MergerException("Path '" + to.path() + "' is not writable");
	}

	foreach (QString srcFile, from.entryList()) {
		if (srcFile == "." || srcFile == "..") {
			continue;
		}

		QFileInfo srcPath(from.path() + QDir::separator() + srcFile);
		QFileInfo dstPath(to.path() + QDir::separator() + srcFile);

		// not existing directory - create
		if (srcPath.isDir()) {
			QDir dstDir(dstPath.filePath());

			if (!dstDir.exists() && !dstDir.mkdir(dstDir.path())) {
				throw MergerException("Can`t create directory '" + dstDir.path() + "'");
			}

			copyDirectoryRecursive(srcPath.filePath(), dstDir.path());
		} else {
			// copy file
			if (!QFile::copy(srcPath.filePath(), dstPath.filePath())) {
				throw MergerException("Can`t copy file '" + srcPath.filePath() + "' to '" + dstPath.filePath() + "'");
			}
		}
	}
}

long Merger::mergeDirectoryRecursive(const QDir from, const QDir to) {
	if (!to.Writable) {
		throw MergerException("Path '" + to.dirName() + "' is not writable");
	}

	long messages = 0;
	foreach (QString srcFile, from.entryList()) {
		if (srcFile == "." || srcFile == "..") {
			continue;
		}

		QFileInfo srcPath(from.path() + QDir::separator() + srcFile);
		QFileInfo dstPath(to.path() + QDir::separator() + srcFile);

		// recursive
		if (srcPath.isDir()) {
			messages += mergeDirectoryRecursive(srcPath.filePath(), dstPath.filePath());
		} else {
			if (!QFile::exists(dstPath.filePath())) {
				QFile::copy(srcPath.filePath(), dstPath.filePath());
			} else {
				messages += merge(srcPath.filePath(), dstPath.filePath());
			}
		}
	}

	return messages;
}

long Merger::merge(QString from, QString to) {
	qDebug() << "Merge: " << from << ", " << to;

	// to doc
	QDomDocument toDoc;
	QFile toFile(to);
	if (!toFile.open(QIODevice::ReadOnly)) {
		throw MergerException("Can`t open file '" + to + "'");
	}
	if (!toDoc.setContent(&toFile))  {
	    toFile.close();
	    throw MergerException("Can`t set XML content for '" + to + "'");
	}
	toFile.close();

	// from doc
	QDomDocument fromDoc;
	QFile fromFile(from);
	if (!fromFile.open(QIODevice::ReadOnly)) {
		throw MergerException("Can`t open file '" + from + "'");
	}
	if (!fromDoc.setContent(&fromFile))  {
	    fromFile.close();
	    throw MergerException("Can`t set XML content for '" + from + "'");
	}
	fromFile.close();

	// merge
	long messages = 0;
	QDomDocument outDoc("Kopete-History");
	QDomElement root = outDoc.createElement("kopete-history");
	root.setAttribute("version", 0.9);
	root.appendChild(toDoc.elementsByTagName("head").at(0));

	QMap<unsigned, QDomNode> msgMap;
	QDomNodeList toMsgs = toDoc.elementsByTagName("msg");
	for (unsigned i = 0; i < toMsgs.length(); ++i, ++messages) {
		QDomNode node = toMsgs.at(i);
		msgMap[generateKey(node.toElement().attribute("time"))] = node;
		qDebug() << "Message: " << node.firstChild().toText().data();
	}
	QDomNodeList fromMsgs = fromDoc.elementsByTagName("msg");
	for (unsigned i = 0; i < fromMsgs.length(); ++i, ++messages) {
		QDomNode node = fromMsgs.at(i);
		msgMap[generateKey(node.toElement().attribute("time"))] = node;
		qDebug() << "Message: " << node.firstChild().toText().data();
	}
	foreach (QDomNode node, msgMap) {
		root.appendChild(node);
	}
	outDoc.appendChild(root);

	QFile outFile(to);
	if (!outFile.open(QIODevice::WriteOnly)) {
		throw MergerException("Can`t open file '" + to + "'");
	}
	outFile.write(outDoc.toByteArray());
	outFile.close();

	return messages;
}

bool Merger::isDirectoryEmpty(QDir dir) {
	foreach (QString file, dir.entryList()) {
		if (file != "." && file != "..") {
			return false;
		}
	}
	return true;
}

unsigned Merger::generateKey(const QString& dateAttr) {
	QStringList time = dateAttr.split(QRegExp("[ :]"));
	if (time.length() != 4) {
		throw MergerException("Can`t split message date");
	}
	return (time[0].toInt() * SECONDS_IN_DAY) + (time[1].toInt() * SECONDS_IN_HOUR) + (time[2].toInt() * SECONDS_IN_MINUITE) + time[3].toInt();
}
