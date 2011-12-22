/**
 * Main GUI window
 *
 * @package kopete_history
 * @author Azat Khuzhin <dohardgopro@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "merger.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void bindShortcuts();

	Ui::MainWindow *ui;
	Merger* merger;

private slots:
	void on_addDirButton_clicked();
	void on_saveButton_clicked();
};

#endif // MAINWINDOW_H
