/*
 * Vision.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#include "Vision.h"

List<RobotInfo> Vision::robots;
List<RobotInfo> Vision::opponents;

FIeldInfo Vision::field;
BallInfo Vision::ball;

Update Vision::update;

void Vision::startUpdate() {
	update.start();
}

void Vision::stopUpdate() {
	update.stop();
}

void Vision::changeInterval(int milSeconds) {
	update.changeInterval(milSeconds);
}

void Update::updateMethod() {
	printf("Update::updateMethodExecutando\n");
	QThread::yieldCurrentThread();
}
