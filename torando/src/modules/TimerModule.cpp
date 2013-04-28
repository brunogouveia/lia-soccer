/*
 * TimerModule.cpp
 *
 *  Created on: Apr 25, 2013
 *      Author: bruno
 */

#include "TimerModule.h"

#include <stdio.h>

TimerModule::TimerModule() :
		firstRun(true), running(false) {
	printf("TimerModule::TimerModule\n");
}

TimerModule::~TimerModule() {
	printf("TimerModule::~TimerModule\n");
	disconnect(getTimer(), SIGNAL(timeout()), this, SLOT(exec()));
}

void TimerModule::start() {
	printf("TimerModule::start\n");
	if (firstRun) {
		connect(getTimer(), SIGNAL(timeout()), this, SLOT(exec()));
		getTimer()->setInterval(1);
		firstRun = false;
	}

	onPreExecute();
	running = true;
	getTimer()->start();
}

void TimerModule::stop() {
	printf("TimerModule::stop\n");
	getTimer()->stop();
	onPosExecute();
}

void TimerModule::setInterval(int milSeconds) {
	getTimer()->setInterval(milSeconds);
}

void TimerModule::exec() {
	printf("TimerModule::exec\n");
	doInBackGround();
	QThread::yieldCurrentThread();
}

void TimerModule::onConnectToTimer(QTimer * timer) {
	printf("TimerModule::onConnectToTimer\n");
}
void TimerModule::onDisconnectToTimer(QTimer * timer) {
	printf("TimerModule::onDisconnectToTimer\n");
}

void TimerModule::onPreExecute() {
	printf("TimerModule::onPreExecute\n");
}

void TimerModule::onPosExecute() {
	printf("TimerModule::onPosExecute\n");
}
