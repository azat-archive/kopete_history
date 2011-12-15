#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QString>
#include <QShortcut>

#include <merger.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	merger = new Merger(this);

	bindShortcuts();
}

MainWindow::~MainWindow() {
	delete ui;
	delete merger;
}

void MainWindow::bindShortcuts() {
	QShortcut *shortcut = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Add")), this);
	connect(shortcut, SIGNAL(activated()), ui->addDirButton, SLOT(click()));
}

void MainWindow::on_addDirButton_clicked() {
	QString dir = QFileDialog::getExistingDirectory(this, "Select directory", getenv("~"), QFileDialog::ShowDirsOnly);

	merger->addPath(dir);
	ui->dirsListWidget->addItem(dir);
}

void MainWindow::on_saveButton_clicked() {
	try {
		QDir saveTo(QFileDialog::getExistingDirectory(this, "Select directory", getenv("~"), QFileDialog::ShowDirsOnly));
		long messages = merger->run(saveTo);

		ui->statusBar->showMessage("Done. Success. " + QString::number(messages) + " messages.");
	} catch (const MergerException& mergerException) {
		ui->statusBar->showMessage(mergerException.getMessage());
	}
}
