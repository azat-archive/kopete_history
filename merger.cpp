#include "merger.h"

Merger::Merger(QObject *parent) : QObject(parent) {
}

void Merger::addPath(QString path) {
	paths.push_back(path);
}

void Merger::setPaths(QStringList paths) {
	this->paths = paths;
}

long Merger::run() {
	throw MergerException("Implement this feature");
}
