#include "merger.h"

Merger::Merger(QObject *parent) : QObject(parent) {
}

void Merger::addPath(QString& path) {
	paths.push_back(path);
}

void Merger::setPaths(QStringList& paths) {
	paths = paths;
}

long Merger::run(QDir& saveTo) {
	int i = 0;

	if (paths.count() < 2) {
		throw MergerException("First you must add more than or equal two path");
	}

	foreach (QDir path, paths) {
		if (++i == 1) {
			copyDirectory(path, saveTo);
		} else {
			mergeDirectory(path, saveTo);
		}
	}
}

void Merger::copyDirectory(QDir from, QDir to) {
	if (!to.Writable) {
		throw MergerException("Path '" + to.dirName() + "' is not writable");
	}

	foreach (QString srcFile, from.entryList()) {
		if (srcFile == "." || srcFile == "..") {
			continue;
		}

		QString dstFile = to.dirName() + "/" + srcFile;

		if (!QFile::copy(srcFile, dstFile)) {
			throw MergerException("Can`t copy file '" + srcFile + "' to '" + dstFile + "'");
		}
	}
}

void Merger::mergeDirectory(QDir from, QDir to) {
	if (!to.Writable) {
		throw MergerException("Path '" + to.dirName() + "' is not writable");
	}

	throw MergerException("Implement this feature");
}
