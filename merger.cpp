#include "merger.h"

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
	int i = 0;

	if (paths.count() < 2) {
		throw MergerException("First you must add more than or equal two path");
	}

	foreach (QString path, paths) {
		if (++i == 1) {
			copyDirectoryRecursive(path, saveTo);
		} else {
			mergeDirectory(path, saveTo);
		}
	}
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

void Merger::mergeDirectory(const QDir from, const QDir to) {
	if (!to.Writable) {
		throw MergerException("Path '" + to.dirName() + "' is not writable");
	}

	throw MergerException("Implement this feature");
}
