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
#include "Array.h"
#include "Vision.h"
#include <stdlib.h>
#include <iostream>

class RrtNode {

	private:
		friend class Rrt;
		friend class KdTree;

		RrtNode(Target target, RrtNode * parent = 0) :
				target(target.x(), target.y()), parent(parent) {
		}
		~RrtNode() {
		}

		void addChild(RrtNode * child) {
			children.add(child);
		}

		void removeChild(RrtNode * child) {
			children.remove(child);
		}

		TargetFixed target;
		RrtNode * parent;
		Array<RrtNode *> children;
};

class KdTree {
	public:
		KdTree() :
				kd(kd_create(2)) {
			srand(time(0));
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
			cout << "Nearest: " << sqrt(deltaX * deltaX + deltaY * deltaY) << endl;
			return sqrt(deltaX * deltaX + deltaY * deltaY);
		}

		Target getNearestPoint(Target & target) {
			RrtNode * node = getNearestNode(target);

			if (node != 0) {
				return node->target;
			}
			return target;
		}

		RrtNode * getNearestNode(Target & target) {
			kdres * kdr = kd_nearest3f(kd, target.x(), target.y(), 0);

			if (kd_res_size(kdr) > 0) {
				RrtNode * node = (RrtNode *) kd_res_item_data(kdr);
				kd_res_free(kdr);

				return node;
			}
			return 0;
		}

		void clear() {
			kd_clear(kd);
		}

		void grow(Target goal) {

			//Cria um ponto aleatório
			float maxX = 3000.0;
			float minX = -3000.0;

			float x = minX + (rand() % (int) (maxX - minX + 1));

			float maxY = 2000.0;
			float minY = -2000.0;

			float y = minY + (rand() % (int) (minY - minY + 1));

			float ran = (float) rand() / (float) RAND_MAX;

			//Existe uma possibilidade de o ponto aleatório ser o ponto de destino
			//Probabilidade de 5%
			if (ran < 0.05) {
				x = goal.x();
				y = goal.y();
			}

			//Cria o Target para o ponto aleatório gerado.
			TargetFixed randTarget(x, y);

			//Procura o nó da árvore que está mais proximo do ponto gerado
			RrtNode * nearestNode = getNearestNode(randTarget);

			//Cria um vetor (pontogerado - pontomaisperto)
			Target newTarget = nearestNode->target;

			float deltaX = randTarget.x() - newTarget.x();
			float deltaY = randTarget.y() - newTarget.y();

			/*normalizar os deltas vetor(delaX,deltaY)*/
			float norm = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (norm != 0) {
				deltaX = (deltaX / norm) * 100;
				deltaY = (deltaY / norm) * 100;
			}


			TargetFixed delta(newTarget.x() + deltaX, newTarget.y() + deltaY);

			//Se o ponto é válido, ou seja, não está perto de nenhum obstáculo, então adiciona o novo ponto na árvore
			if (Vision::isFree(delta)) {
				RrtNode * newNode = new RrtNode(delta, nearestNode);
				nearestNode->addChild(newNode);

				insert(delta, newNode);
			}

		}

	private:
		kdtree * kd;
};

#endif /* KDTREE_H_ */
