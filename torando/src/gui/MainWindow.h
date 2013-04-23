/*
 * MainWindow.h
 *
 *  Created on: Apr 17, 2013
 *      Author: bruno
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow: public QMainWindow {
	Q_OBJECT
	public:
		MainWindow();
		virtual ~MainWindow();

	private:
		QPushButton * visionButton;
		QPushButton * controlButton;
		QPushButton * communicationButton;

	private slots:
		void visionButtonMethod();
		void controlButtonMethod();
		void communicationButtonMethod();
};

#endif /* MAINWINDOW_H_ */
