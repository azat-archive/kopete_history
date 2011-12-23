/**
 * Test for Merger
 *
 * @package kopete_history
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <QtTest/QtTest>
#include <QProcess>

#include "../../src/merger.h"

#define TCALL(callback) try { callback; } catch (const MergerException& e) { QFAIL(e.getMessage().toStdString().c_str()); }

// interface
class TestMerger : public QObject {
	Q_OBJECT

public:
	TestMerger();
	~TestMerger();

private slots:
	void initTestCase();
	void cleanupTestCase();

	void testRun();

private:
	Merger* instance;
	QDir* dataDirectory;

	bool checkDirectoryRecursive(const QDir src, const QDir dst);
	void removeDirectoryRecursive(const QDir what);
};

class TestMergerException : public MergerException {
public:
	TestMergerException(QString message) : MergerException(message) {}
};


// implementation
TestMerger::TestMerger() {
	instance = new Merger();

	QDir relativeDataDirectory("data");
	dataDirectory = new QDir(relativeDataDirectory.absolutePath());
}

TestMerger::~TestMerger() {
	delete instance;
	delete dataDirectory;
}

void TestMerger::initTestCase() {
	QDir out = dataDirectory->absolutePath() + "/out";

	if (!out.exists()) {
		out.mkdir(out.absolutePath());
	} else {
		TCALL(removeDirectoryRecursive(out));
	}
}

void TestMerger::cleanupTestCase() {
	QDir out = dataDirectory->absolutePath() + "/out";

	TCALL(removeDirectoryRecursive(out));
}

void TestMerger::testRun() {
	int messages = 0;

	TCALL(
		messages = instance->addPath(dataDirectory->path() + "/first/")
						->addPath(dataDirectory->path() + "/second/")
						->run(dataDirectory->path() + "/out/")
	);

	QVERIFY(messages > 0);

	bool status = false;
	TCALL(status = checkDirectoryRecursive(dataDirectory->path() + "/out_dist/", dataDirectory->path() + "/out/"));
	QVERIFY(status == true);
}

bool TestMerger::checkDirectoryRecursive(const QDir src, const QDir dst) {
	QProcess *diff = new QProcess(this);

	QStringList arguments;
	arguments << "-r" << src.path() << dst.path();

	diff->start("diff", arguments);

	if (!diff->waitForFinished()) {
		throw TestMergerException("Failed to execute diff");
	}

	return diff->exitCode() == 0;
}

void TestMerger::removeDirectoryRecursive(const QDir what) {
	foreach (QString srcFile, what.entryList()) {
		if (srcFile == "." || srcFile == "..") {
			continue;
		}

		QFileInfo srcPath(what.path() + QDir::separator() + srcFile);

		// recursive
		if (srcPath.isDir()) {
			removeDirectoryRecursive(srcPath.filePath());

			QDir dir(srcPath.filePath());
			dir.rmdir(srcPath.filePath());
		} else {
			if (!QFile::remove(srcPath.filePath())) {
				throw TestMergerException("Failed to remove '" + srcPath.filePath() + "'");
			}
		}
	}
}


// main
QTEST_MAIN(TestMerger)
#include "testmerger.moc"
