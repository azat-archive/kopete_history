/**
 * Merger exception
 *
 * @package kopete_history
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

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
