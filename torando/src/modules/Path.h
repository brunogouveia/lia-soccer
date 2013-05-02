/*
 * Path.h
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#ifndef PATH_H_
#define PATH_H_

class Path {
	public:
		Path(Target & from) {
			this->from = from;
			this->to = from;
		}
		virtual ~Path();

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

#endif /* PATH_H_ */
