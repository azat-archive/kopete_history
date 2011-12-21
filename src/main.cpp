/**
 * Main
 *
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 */

#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
