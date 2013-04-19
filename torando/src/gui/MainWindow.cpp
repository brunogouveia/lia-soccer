/*
 * MainWindow.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: bruno
 */

#include "MainWindow.h"

#include <Vision.h>
#include <Control.h>

MainWindow::MainWindow() {
	// TODO Auto-generated constructor stub
	visionButton = new QPushButton("Vision",this);
	controlButton = new QPushButton("Control",this);

	QVBoxLayout * vbox = new QVBoxLayout(this);

	vbox->addWidget(visionButton);
	vbox->addWidget(controlButton);

	QWidget * centralWidget = new QWidget();
	centralWidget->setLayout(vbox);
	setCentralWidget(centralWidget);
	showMaximized();

	connect(visionButton, SIGNAL(clicked()), this, SLOT(visionButtonMethod()));
	connect(controlButton, SIGNAL(clicked()), this, SLOT(controlButtonMethod()));
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::visionButtonMethod() {
	static bool running = false;

	if (!running)
		Vision::startUpdate();
	else
		Vision::stopUpdate();
	running = !running;
}

void MainWindow::controlButtonMethod() {
	static bool running = false;

	if (!running){
		Control::start();
		printf("Começou\n");
	}
	else {
		Control::stop();
		printf("Parou\n");
	}
	running = !running;
}

