/*
 * RobotControl.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Robot.h"
#include "Communication.h"
#include <stdio.h>
#include <math.h>

#define pi 3.14159265359

const int angles[4] = { 60, 135, 225, 300 };

void Robot::loop() {

}

void Robot::lookAt(Target & lookat) {
	this->lookat = lookat;
}

void Robot::followTarget(Target & target) {
	double wheelsAnglesRad[4] = { (double) angles[0] / 180 * pi, (double) angles[1] / 180 * pi, (double) angles[2] / 180 * pi, (double) angles[3] / 180 * pi };

	destination = target;

	TargetFixed nextPoint = getNextPoint();
	float targetTheta = atan2(nextPoint.y() - info.y(), nextPoint.x() - info.x()) - info.orientation();
	float lookTheta = atan2(lookat.y() - info.y(), lookat.x() - info.x()) - info.orientation();
	float r = -50.0;
	float rl = 30.0;
	printf("NextPoint -  %f %f %f\n", nextPoint.x(), nextPoint.y(), info.orientation());
	printf("Robot -  %f %f %f\n", info.x(), info.y(), info.orientation());

	//printf("theta: %f w1: %lf w2: %lf  w3: %lf w4: %lf\n", theta, sin(wheelsAnglesRad[0] - theta) * r, sin(wheelsAnglesRad[1] - theta) * r, sin(wheelsAnglesRad[2] - theta) * r, sin(wheelsAnglesRad[3] - theta) * r);
	Communication::setWheelsVelocity(0, sin(wheelsAnglesRad[0] - targetTheta) * r + lookTheta * rl, sin(wheelsAnglesRad[1] - targetTheta) * r + lookTheta * rl, sin(wheelsAnglesRad[2] - targetTheta) * r + lookTheta * rl, sin(wheelsAnglesRad[3] - targetTheta) * r + lookTheta * rl);
}

TargetFixed Robot::getNextPoint() {
	float x = info.x();
	float y = info.y();

	float verticalDist = 40;
	float diagonalDist = 28;

	TargetFixed n(x, y + verticalDist);
	TargetFixed ne(x + diagonalDist, y + diagonalDist);
	TargetFixed e(x + verticalDist, y);
	TargetFixed se(x + diagonalDist, y - diagonalDist);
	TargetFixed s(x, y - verticalDist);
	TargetFixed sw(x - diagonalDist, y - diagonalDist);
	TargetFixed w(x - verticalDist, y);
	TargetFixed nw(x - diagonalDist, y + diagonalDist);

	float np = potential(n.x(), n.y());

	float minPotential = np;
	TargetFixed minPotentialPoint = n;

	float temp;
	if ((temp = potential(ne.x(), ne.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = ne;
	}
	if ((temp = potential(e.x(), e.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = e;
	}
	if ((temp = potential(se.x(), se.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = se;
	}
	if ((temp = potential(s.x(), s.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = s;
	}
	if ((temp = potential(sw.x(), sw.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = sw;
	}
	if ((temp = potential(w.x(), w.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = w;
	}
	if ((temp = potential(nw.x(), nw.y())) < minPotential) {
		minPotential = temp;
		minPotentialPoint = nw;
	}

	return minPotentialPoint;
}

float Robot::potential(float x, float y) {

	float ka = 0.9;
	float potential = 0.5 * ka * (x - destination.x()) * (x - destination.x()) + (y - destination.y()) * (y - destination.y());

	float kr = 2.9;

	int numRobots = Vision::robots.size();
	printf("Num blue robots: %d\n", numRobots);
	for (int i = 0; i < numRobots; i++) {
		RobotInfo robot = Vision::robots[i];

		float distanceSquare = sqrt((x - robot.x()) * (x - robot.x()) + (y - robot.y()) * (y - robot.y()));

		if (distanceSquare < 1000) {
			potential += 0.5 * kr * (1 / distanceSquare - 1 / 1000);
		}
	}

	int numOpponents = Vision::opponents.size();
	printf("Num yell robots: %d\n", numOpponents);
	for (int i = 0; i < numOpponents; i++) {
		RobotInfo robot = Vision::opponents[i];

		float distanceSquare = sqrt((x - robot.x()) * (x - robot.x()) + (y - robot.y()) * (y - robot.y()));

		if (distanceSquare < 1000) {
			potential += 0.5 * kr * (1 / distanceSquare - 1 / 1000);
		}
	}
	return potential;
}
