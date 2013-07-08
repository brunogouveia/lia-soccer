/*
 * Rnn.h
 *
 *  Created on: Jul 8, 2013
 *      Author: bruno
 */

#ifndef RNN_H_
#define RNN_H_

class RnnNode;

#include "KdTree.h"
#include "Array.h"

class Rrt {
	public:
		Rrt(Target & begin, Target & goal) {
		}
		virtual ~Rrt();

		Target getNextPoint() {
			while (points.nearestDist(goal) > 100) {
				points.grow(goal);
			}
		}

	private:
		Target beggin;
		Target goal;

		KdTree points;

};

class RrtNode {

	private:
		friend class Rrt;

		RrtNode(Target target, RrtNode * parent = 0) :
				target(target), parent(parent) {
		}
		~RrtNode() {
		}

		void addChild(RrtNode * child) {
			children.add(child);
		}

		void removeChild(RrtNode * child) {
			children.remove(child);
		}

		RrtNode * parent;
		TargetFixed target;
		Array<RrtNode *> children;
};

#endif /* RNN_H_ */
