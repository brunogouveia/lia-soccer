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
}

Control::~Control() {
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
	while (running){
		controlLoop();
		QThread::yieldCurrentThread();
	}
}

void Control::controlLoop() {
	printf("ControlThread::controlLoop\n");
	QThread::yieldCurrentThread();
}

