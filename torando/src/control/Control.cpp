/*
 * Control.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Control.h"

Control Control::control;
QThread Control::thread;

bool Control::running = false;

Control::Control() {
	//connect(&Referee::referee, SIGNAL(refereeReceived()), this, SLOT(controlLoop()));
}

Control::~Control() {
	//disconnect(&Referee::referee, SIGNAL(refereeReceived()), this, SLOT(controlLoop()));
}

void Control::start() {
	bool firstRun = true;

	if (firstRun) {
		control.moveToThread(&thread);
		control.connect(&thread, SIGNAL(started()), SLOT(exec()));
	}

	running = true;
	thread.start();
}

void Control::stop() {
	running = false;
	thread.quit();
}

void Control::exec() {
	while (running) {
		controlLoop();
		QThread::yieldCurrentThread();
	}
}

void Control::controlLoop() {
	printf("ControlThread::controlLoop\n");
}

