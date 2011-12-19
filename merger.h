#ifndef MERGER_H
#define MERGER_H

#include <QObject>

#include <QStringList>
#include <QString>
#include <QDir>

#include <mergerexception.h>

class Merger : public QObject {
	Q_OBJECT
public:
	explicit Merger(QObject *parent = 0);
	void addPath(const QString& path);
	void setPaths(QStringList& paths);
	long run(const QDir& saveTo);

signals:

public slots:

private:
	QStringList paths;
	static void copyDirectoryRecursive(const QDir from, const QDir to);
	static void mergeDirectory(const QDir from, const QDir to);

};

#endif // MERGER_H
