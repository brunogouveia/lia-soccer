/*
 * RobotControl.h
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#ifndef ROBOTCONTROL_H_
#define ROBOTCONTROL_H_

#include <QtCore>
#include <QThread>

class Robot: public QThread {
	Q_OBJECT
	public:
		Robot();
		virtual ~Robot();

};

#endif /* ROBOTCONTROL_H_ */
