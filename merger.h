#ifndef MERGER_H
#define MERGER_H

#include <QObject>

#include <QStringList>
#include <QString>

#include <mergerexception.h>

class Merger : public QObject {
	Q_OBJECT
public:
	explicit Merger(QObject *parent = 0);
	void addPath(QString path);
	void setPaths(QStringList paths);
	long run(QString saveTo);

signals:

public slots:

protected:
	QStringList paths;

};

#endif // MERGER_H
