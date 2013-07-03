/*
 * BallInfo.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef BALLINFO_H_
#define BALLINFO_H_

#include <Target.h>
#include "messages_robocup_ssl_detection.pb.h"

class BallInfo: public Target {
public:
	BallInfo();
	virtual ~BallInfo();

	float x() {
		return _x;
	}

	float y() {
		return _y;
	}

	float z() {
		return _z;
	}

	float confidence() {
		return _confidence;
	}

	float pixelx() {
		return _pixelx;
	}

	float pixely() {
		return _pixely;
	}

	bool onField() {
		return _onField;
	}

	void updateBall(SSL_DetectionBall & ball) {
		static BallInfo balls[3];
		balls[0] = balls[1];
		balls[1]=balls[2];

		balls[2]._x = ball.x();
		balls[2]._y = ball.y();
		balls[2]._z = ball.z();
		_x = (balls[0]._x + balls[1]._x + balls[2]._x) / 3;
		_y = (balls[0]._y + balls[1]._y + balls[2]._y) / 3;
		_z = (balls[0]._z + balls[1]._z + balls[2]._z) / 3;

	}

private:

	float _x;
	float _y;
	float _z;
	float _confidence;
	float _pixelx;
	float _pixely;
	bool _onField;

	friend class Vision;
};

#endif /* BALLINFO_H_ */
