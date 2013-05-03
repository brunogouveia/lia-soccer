/*
 * RobotInfo.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef ROBOTINFO_H_
#define ROBOTINFO_H_

#include <Target.h>

class RobotInfo : public Target {
	public:
		RobotInfo();
		virtual ~RobotInfo();

	private:
		float x;
		float y;
		float orientation;

		friend class Vision;
};

#endif /* ROBOTINFO_H_ */
