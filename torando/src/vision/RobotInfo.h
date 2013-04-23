/*
 * RobotInfo.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef ROBOTINFO_H_
#define ROBOTINFO_H_

class RobotInfo {
	public:
		RobotInfo();
		virtual ~RobotInfo();

		float x;
		float y;
		float orientation;
};

#endif /* ROBOTINFO_H_ */
