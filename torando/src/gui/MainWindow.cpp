/*
 * MainWindow.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: bruno
 */

#include "MainWindow.h"

#include <Vision.h>
#include <Control.h>
#include <Communication.h>

MainWindow::MainWindow() {
	// TODO Auto-generated constructor stub
	visionButton = new QPushButton("Vision", this);
	controlButton = new QPushButton("Control", this);
	communicationButton = new QPushButton("Communication", this);

	QVBoxLayout * vbox = new QVBoxLayout(this);

	vbox->addWidget(visionButton);
	vbox->addWidget(controlButton);
	vbox->addWidget(communicationButton);

	QWidget * centralWidget = new QWidget();
	centralWidget->setLayout(vbox);
	setCentralWidget(centralWidget);
	showMaximized();

	connect(visionButton, SIGNAL(clicked()), this, SLOT(visionButtonMethod()));
	connect(controlButton, SIGNAL(clicked()), this, SLOT(controlButtonMethod()));
	connect(communicationButton, SIGNAL(clicked()), this, SLOT(communicationButtonMethod()));
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::visionButtonMethod() {
	static bool running = false;

	if (!running)
		Vision::startModule();
	else
		Vision::stopModule();
	running = !running;
}

void MainWindow::controlButtonMethod() {
	static bool running = false;

	if (!running) {
		Control::startModule();
		printf("Começou\n");
	} else {
		Control::stopModule();
		printf("Parou\n");
	}
	running = !running;
}

void MainWindow::communicationButtonMethod() {
	static bool running = false;

	if (!running) {
		Communication::startModule();
		printf("Começou\n");
	} else {
		Communication::stopModule();
		printf("Parou\n");
	}
	running = !running;
}
