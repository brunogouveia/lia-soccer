/*
 * Rnn.h
 *
 *  Created on: Jul 8, 2013
 *      Author: bruno
 */

#ifndef RNN_H_
#define RNN_H_

#include "KdTree.h"
#include "Array.h"
#include "Target.h"
#include "TargetFixed.h"
#include <iostream>

class Rrt {
	public:
		Rrt(Target & begin, Target & goal) :
				goal(goal) {
			RrtNode * root = new RrtNode(begin, 0);
			points.insert(begin, root);
		}
		virtual ~Rrt() {

		}

		Target * getNextPoint() {
			while (points.nearestDist(goal) > 200) {
				points.grow(goal);
			}
			RrtNode * goal = points.getNearestNode(this->goal);

			int size = 0;
			for (RrtNode * ptr = goal; ptr != 0; ptr = ptr->parent) {
				size++;
			}

			Target

			for (RrtNode * ptr = goal; ptr != 0; ptr = ptr->parent) {
				cout << "Caminho " << ptr->target.x() << ", " << ptr->target.y() << endl;
			}

			return goal->target;
		}

	private:
		Target beggin;
		Target goal;

		KdTree points;

};

#endif /* RNN_H_ */
