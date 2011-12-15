#ifndef MERGEREXCEPTION_H
#define MERGEREXCEPTION_H

#include <QtCore>

class MergerException : public QtConcurrent::Exception {
public:
	MergerException(QString message) : message(message) {}
	~MergerException() throw() {};
	QString getMessage() const { return message; };
private:
	QString message;
};

#endif // MERGEREXCEPTION_H
