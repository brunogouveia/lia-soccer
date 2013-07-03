/*
 * Path.h
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#ifndef PATH_H_
#define PATH_H_

#include <Target.h>
#include <TargetFixed.h>

class Path {
	public:
		Path(Target & from) :
				from(from), to(from) {
		}
		virtual ~Path() {
		}

		// Retorna o próximo ponto no caminho para o destino
		TargetFixed getNextPoint();
		// Retorna a distancia para o destino
		float distanceToTarget();
		// Está no destino
		bool inDestination();
		// porno de cavalos
		bool changeTarget(Target & to);

	private:
		Target & from;
		Target & to;
};

class PathNode {
		PathNode * parent;
		Target target;
};

#endif /* PATH_H_ */
