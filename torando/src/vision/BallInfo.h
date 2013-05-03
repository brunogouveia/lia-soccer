/*
 * BallInfo.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef BALLINFO_H_
#define BALLINFO_H_

#include <Target.h>

class BallInfo : public Target {
	public:
		BallInfo();
		virtual ~BallInfo();

	private:

		float x;
		float y;
		float z;

		friend class Vision;
};

#endif /* BALLINFO_H_ */
