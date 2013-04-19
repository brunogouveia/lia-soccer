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

Vision Vision::vision;

Vision::Vision() :
		timer(this) {
	connect(&timer, SIGNAL(timeout()), this, SLOT(visionLoop()));
}

Vision::~Vision() {
	disconnect(&timer, SIGNAL(timeout()), this, SLOT(visionLoop()));
}

void Vision::start() {
	vision.timer.start();
}

void Vision::stop() {
	vision.timer.stop();
}

void Vision::changeInterval(int milSeconds) {
	vision.timer.setInterval(milSeconds);
}

void Vision::visionLoop() {
	printf("Vision::visionLoop\n");
	QThread::yieldCurrentThread();
}
