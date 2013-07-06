/*
 * Control.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Control.h"
#include "Robot.h"
#include <unistd.h>

Control::Control() {
	//Referee referee = Referee::getInstance();
	//connect(&referee, SIGNAL(newCommand()), this, SLOT(callStrategy()));
}

Control::~Control() {
	//Referee referee = Referee::getInstance();
	//disconnect(&referee, SIGNAL(newCommand()), this, SLOT(callStrategy()));
}

void Control::onPreExecute() {
}

void Control::doInBackground() {
	//printf("Control::doInBackGround - started\n");


	Robot robot(Vision::robots[0]);
	printf("Ball: %f %f\n",Vision::ball.x(), Vision::ball.y());
	robot.lookAt();
	robot.followTarget(Vision::ball);

	/*printf("%d\n", Vision::robots.size());
	for(int i = 0; i < Vision::robots.size(); i++)
		printf("Robô (%d): %f %f\n", i, Vision::robots[i].x(), Vision::robots[i].y());
	*/usleep(1000);

	//printf("Control::doInBackGround - finished\n");

}

void Control::onPosExecute() {
}

void Control::callStrategy() {

}

