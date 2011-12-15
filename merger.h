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
	void addPath(QString& path);
	void setPaths(QStringList& paths);
	long run(QDir& saveTo);

signals:

public slots:

private:
	QStringList paths;
	static void copyDirectory(QDir from, QDir to);
	static void mergeDirectory(QDir from, QDir to);

};

#endif // MERGER_H
