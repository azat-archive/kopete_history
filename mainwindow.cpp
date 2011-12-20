/**
 * Main GUI window
 *
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 */

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
	// add
	QShortcut *shortcutAdd = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Add")), this);
	connect(shortcutAdd, SIGNAL(activated()), ui->addDirButton, SLOT(click()));

	// save
	QShortcut *shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), this);
	connect(shortcutSave, SIGNAL(activated()), ui->saveButton, SLOT(click()));

	// quit
	QShortcut *shortcutQuit = new QShortcut(QKeySequence(tr("Ctrl+Q", "File|Quit")), this);
	connect(shortcutQuit, SIGNAL(activated()), QApplication::instance(), SLOT(quit()));
}

void MainWindow::on_addDirButton_clicked() {
	QString dir = QFileDialog::getExistingDirectory(this, "Select directory", getenv("~"), QFileDialog::ShowDirsOnly);

	try {
		merger->addPath(dir);
		ui->dirsListWidget->addItem(dir);
	} catch (const MergerException& mergerException) {
		ui->statusBar->showMessage(mergerException.getMessage());
	}
}

void MainWindow::on_saveButton_clicked() {
	QDir saveTo(QFileDialog::getExistingDirectory(this, "Select directory", getenv("~"), QFileDialog::ShowDirsOnly));

	try {
		long messages = merger->run(saveTo);

		ui->statusBar->showMessage("Done. Success. " + QString::number(messages) + " messages.");
	} catch (const MergerException& mergerException) {
		ui->statusBar->showMessage(mergerException.getMessage());
	}
}
