/**
 * Merger
 *
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 */

#ifndef MERGER_H
#define MERGER_H

#include <QObject>

#include <QStringList>
#include <QString>
#include <QDir>

#include "mergerexception.h"

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
	static const unsigned SECONDS_IN_MINUITE = 60;
	static const unsigned SECONDS_IN_HOUR = SECONDS_IN_MINUITE * 60;
	static const unsigned SECONDS_IN_DAY = SECONDS_IN_HOUR * 24;

	QStringList paths;
	long messages;

	static void copyDirectoryRecursive(const QDir from, const QDir to);
	static long mergeDirectoryRecursive(const QDir from, const QDir to);
	static long merge(QString from, QString to);
	static bool isDirectoryEmpty(QDir dir);
	static unsigned generateKey(const QString& dateAttr);
};

#endif // MERGER_H
