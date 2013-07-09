/*
 * Target.h
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#ifndef TARGET_H_
#define TARGET_H_

#include<math.h>

class Target {
	public:
		Target();
		virtual ~Target();

		inline float x() {return _x;}
		inline float y() {return _y;}

		float distance(Target & t) {
			float distX = _x - t.x();
			float distY = _y - t.y();

			return sqrt(distX * distX + distY * distY);
		}

	protected:

		float _x;
		float _y;

		friend class Vision;

};

#endif /* TARGET_H_ */
