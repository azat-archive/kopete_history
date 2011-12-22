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

#include "../../src/merger.h"


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
};


// implementation
TestMerger::TestMerger() {
	instance = new Merger();
}

TestMerger::~TestMerger() {
	delete instance;
}

void TestMerger::initTestCase() {}

void TestMerger::cleanupTestCase() {}

void TestMerger::testRun() {
	QDir data("tests/data");

	instance->addPath(data.path() + "/first/")
		  ->addPath(data.path() + "/second/")
		  ->run(data.path() + "/out/");

	// @TODO - add check
}


// main
QTEST_MAIN(TestMerger)
#include "testmerger.moc"
