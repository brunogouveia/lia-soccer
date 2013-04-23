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
		Vision::start();
	else
		Vision::stop();
	running = !running;
}

void MainWindow::controlButtonMethod() {
	static bool running = false;

	if (!running) {
		Control::start();
		printf("Começou\n");
	} else {
		Control::stop();
		printf("Parou\n");
	}
	running = !running;
}

void MainWindow::communicationButtonMethod() {
	static bool running = false;

	if (!running) {
		Communication::start();
		Communication::setWheelsVelocity(0, 10.0f, 10.0f, 10.0f, 10.0f);
		Communication::setWheelsVelocity(2,10,-10,10,-10);
		printf("Começou\n");
	} else {
		Communication::stop();
		printf("Parou\n");
	}
	running = !running;
}
