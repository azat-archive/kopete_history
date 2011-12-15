#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QString>

#include <merger.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	merger = new Merger;
}

MainWindow::~MainWindow() {
	delete ui;
	delete merger;
}

void MainWindow::changeEvent(QEvent *e) {
	QMainWindow::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void MainWindow::on_addDirButton_clicked() {
	QString dir = QFileDialog::getExistingDirectory(this, "Select directory", getenv("~"), QFileDialog::ShowDirsOnly);

	merger->addPath(dir);
	ui->dirsListWidget->addItem(dir);
}

void MainWindow::on_saveButton_clicked() {
	try {
		long messages = merger->run();
		ui->statusBar->showMessage("Done. Success. " + QString::number(messages) + " messages.");
	} catch (const MergerException& mergerException) {
		ui->statusBar->showMessage(mergerException.getMessage());
	}
}
