/*
 * RobotInfo.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef ROBOTINFO_H_
#define ROBOTINFO_H_

#include <Target.h>
#include "messages_robocup_ssl_detection.pb.h"

class RobotInfo: public Target {
	public:
		RobotInfo();
		virtual ~RobotInfo();

		float x() const {
			return _x;
		}

		float y() const {
			return _y;
		}

		float orientation() const {
			return _orientation;
		}

		float confidence() const {
			return _confidence;
		}
		float pixelx() const {
			return _pixelx;
		}

		float pixely() const {
			return _pixely;
		}

		bool onField() const {
			return _onField;
		}
	private:
		float _x;
		float _y;
		float _orientation;
		float _confidence;
		float _pixelx;
		float _pixely;
		bool _onField;

		friend class Vision;
		friend class RobotList;
};

#endif /* ROBOTINFO_H_ */
