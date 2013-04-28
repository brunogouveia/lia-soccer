/*
 * ThreadModule.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: bruno
 */

#include "ThreadModule.h"

ThreadModule::ThreadModule() :
		firstRun(true), running(false) {
	printf("ThreadModule::ThreadModule()\n");
}

ThreadModule::~ThreadModule() {
	printf("ThreadModule::~ThreadModule()\n");
	disconnect(getThread(), SIGNAL(started()), this, SLOT(exec()));
}

void ThreadModule::start() {
	printf("ThreadModule::start()\n");
	if (firstRun) {
		moveToThread(getThread());
		connect(getThread(), SIGNAL(started()), this, SLOT(exec()));
		onConnectToThread(getThread());
	}

	running = true;
	getThread()->start();
}

void ThreadModule::stop() {
	printf("ThreadModule::stop()\n");
	running = false;
	getThread()->quit();
}

void ThreadModule::exec() {
	printf("ThreadModule::exec()\n");
	onPreExecute();
	while (running) {
		doInBackGround();
		QThread::yieldCurrentThread();
	}
	onPosExecute();
}

void ThreadModule::onConnectToThread(QThread * thread) {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

void ThreadModule::onDisconnectToThread(QThread * thread) {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

void ThreadModule::onPreExecute() {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

void ThreadModule::onPosExecute() {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

