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
		virtual ~TargetFixed();
};

#endif /* TARGETFIXED_H_ */
