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

void Robot::followTarget(Target & target) {
	double wheelsAnglesRad[4] = { (double) angles[0] / 180 * pi, (double) angles[1] / 180 * pi, (double) angles[2] / 180 * pi, (double) angles[3] / 180 * pi };

	float theta = atan2(target.y() - info.y(), target.x() - info.x()) - info.orientation();
	float r = -50.0;
	printf("Robot -  %f %f %f\n", info.x(),info.y(), info.orientation());

	//printf("theta: %f w1: %lf w2: %lf  w3: %lf w4: %lf\n", theta, sin(wheelsAnglesRad[0] - theta) * r, sin(wheelsAnglesRad[1] - theta) * r, sin(wheelsAnglesRad[2] - theta) * r, sin(wheelsAnglesRad[3] - theta) * r);
	Communication::setWheelsVelocity(0, sin(wheelsAnglesRad[0] - theta) * r, sin(wheelsAnglesRad[1] - theta) * r, sin(wheelsAnglesRad[2] - theta) * r, sin(wheelsAnglesRad[3] - theta) * r);
}
