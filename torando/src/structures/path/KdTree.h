/*
 * KdTree.h
 *
 *  Created on: Jul 8, 2013
 *      Author: bruno
 */

#ifndef KDTREE_H_
#define KDTREE_H_

#include "kdtree.h"
#include "TargetFixed.h"

class KdTree {
	public:
		KdTree() :
				kd(kd_create(2)) {

		}
		virtual ~KdTree() {
			kd_free(kd);
		}

		void insert(Target target, RrtNode * node) {
			kd_insert3f(kd, target.x(), target.y(), 0, node);
		}

		float nearestDist(Target target) {
			Target nearest = getNearestPoint(target);

			float deltaX = nearest.x() - target.x();
			float deltaY = nearest.y() - target.y();
			return sqrt(deltaX * deltaX + deltaY * deltaY);
		}

		Target getNearestPoint(Target & target) {
			kdres * kdr = kd_nearest_range3f(kd, target.x(), target.y(), 0, 1);

			if (kd_res_size(kdr) > 0) {

				RrtNode * node = (Rrt *) kd_res_item_data(kdr);
				kd_res_free(kdr);

				return node->target;
			}
			return target;
		}

		void grow(Target goal) {
			srand(time(0));
			float x = (rand() * 6000.0) - 3000.0;
			float y = (rand() * 6000.0) - 3000.0;

			float ran = rand();

			if (ran < 0.05) {
				x = goal.x();
				y = goal.y();
			}

			TargetFixed randTarget(x, y);

			Target newTarget = getNearestPoint(randTarget);

			float deltaX = randTarget.x() - newTarget.x();
			float deltaY = randTarget.y() - newTarget.y();

			/*normalizar os deltas vetor(delaX,deltaY)*/
			float norm = (deltaX * deltaX + deltaY * deltaY);
			if (norm != 0) {
				deltaX = (deltaX / norm) * 30;
				deltaY = (deltaY / norm) * 30;
			}

			TargetFixed delta(deltaX, deltaY);
		insert(delta,)
	}

private:
	kdtree * kd;
};

#endif /* KDTREE_H_ */
