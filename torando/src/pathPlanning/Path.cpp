/*
 * Path.cpp
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#include "Path.h"

bool Path::inDestination() {

	return from.distance(to) < 30.0;
}

TargetFixed Path::getNextPoint() {
	TargetFixed nearestPoints[8];

	generateNearestPoints(nearestPoints, from, 400.0);

	printf("%f %f\n", from.x(), from.y());

	int nearestPossiblePoint = 0;

	for (int i = 1; i < 8; i++) {
		if (Vision::isFree(nearestPoints[i], 300.0)
				&& nearestPoints[i].distance(to)
						< nearestPoints[nearestPossiblePoint].distance(to)) {
			nearestPossiblePoint = i;
		}
	}

	printf("i: %d\n", nearestPossiblePoint);

	return nearestPoints[nearestPossiblePoint];

}

void Path::generateNearestPoints(TargetFixed * vector, Target position,
		double distance) {
	if (distance > 500.0)
		distance = 500.0;
	if (distance < 100.0)
		distance = 100.0;

	vector[0].set(position.x() + distance, position.y());
	vector[1].set(position.x() + distance * 0.6, position.y() + distance * 0.6);
	vector[2].set(position.x(), position.y() + distance);
	vector[3].set(position.x() - distance * 0.6, position.y() + distance * 0.6);
	vector[4].set(position.x() - distance, position.y());
	vector[5].set(position.x() - distance * 0.6, position.y() - distance * 0.6);
	vector[6].set(position.x(), position.y() - distance);
	vector[7].set(position.x() + distance * 0.6, position.y() - distance * 0.6);

	return;
}
