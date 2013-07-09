/*
 * TargetFixed.h
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#ifndef TARGETFIXED_H_
#define TARGETFIXED_H_

#include <Target.h>

class TargetFixed: public Target {
	public:
		TargetFixed(float x, float y);
		TargetFixed(){}
		virtual ~TargetFixed();

		void set(float x, float y) {
			_x = x;
			_y = y;
		}
};

#endif /* TARGETFIXED_H_ */
