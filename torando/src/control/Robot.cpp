/*
 * RobotControl.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Robot.h"
#include "Communication.h"
#include <stdio.h>

#define pi 3.14159265359

const int angles[4] = { 60, 135, 225, 300 };

void Robot::loop() {

}

void Robot::lookAt(Target & lookat) {
	this->lookat = lookat;
}

void Robot::followTarget(Target & target) {
	double wheelsAnglesRad[4] = { (double) angles[0] / 180 * pi, (double) angles[1] / 180 * pi, (double) angles[2] / 180 * pi, (double) angles[3] / 180 * pi };

	path.changeTarget(target);

	TargetFixed nextPoint = path.getNextPoint();
	float targetTheta = atan2(nextPoint.y() - info.y(), nextPoint.x() - info.x()) - info.orientation();
	float lookTheta = atan2(lookat.y() - info.y(), lookat.x() - info.x()) - info.orientation();
	float r = -50.0;
	float rl = 30.0;
	printf("NextPoint -  %f %f %f\n", nextPoint.x(), nextPoint.y(), info.orientation());
	printf("Robot -  %f %f %f\n", info.x(), info.y(), info.orientation());

	//printf("theta: %f w1: %lf w2: %lf  w3: %lf w4: %lf\n", theta, sin(wheelsAnglesRad[0] - theta) * r, sin(wheelsAnglesRad[1] - theta) * r, sin(wheelsAnglesRad[2] - theta) * r, sin(wheelsAnglesRad[3] - theta) * r);
	Communication::setWheelsVelocity(0, sin(wheelsAnglesRad[0] - targetTheta) * r + lookTheta * rl, sin(wheelsAnglesRad[1] - targetTheta) * r + lookTheta * rl, sin(wheelsAnglesRad[2] - targetTheta) * r + lookTheta * rl, sin(wheelsAnglesRad[3] - targetTheta) * r + lookTheta * rl);
}

