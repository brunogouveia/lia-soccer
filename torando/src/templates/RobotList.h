/*
 * RobotList.h
 *
 *  Created on: 02/03/2013
 *      Author: yuriclaure
 */

#ifndef ROBOTLIST_H_
#define ROBOTLIST_H_

#ifndef ROBOTINFO_H_
#include "RobotInfo.h"
#endif

class RobotList {
	private:
		RobotInfo prevRobots[3][10];
		RobotInfo robots[10];
		int robotsMisses[10];

		friend class Vision;

	public:
		RobotList() {
		}

		virtual ~RobotList() {
		}

		void updateRobot(const SSL_DetectionRobot & robot) {
			prevRobots[0][robot.robot_id()] = prevRobots[1][robot.robot_id()];
			prevRobots[1][robot.robot_id()] = prevRobots[2][robot.robot_id()];

			prevRobots[2][robot.robot_id()]._x = (robot.x() + prevRobots[2][robot.robot_id()]._x) / 2;
			prevRobots[2][robot.robot_id()]._y = (robot.y() + prevRobots[2][robot.robot_id()]._y) / 2;
			prevRobots[2][robot.robot_id()]._orientation = robot.orientation();
			robotsMisses[robot.robot_id()] = -1;

			robots[robot.robot_id()]._x = (prevRobots[0][robot.robot_id()]._x + prevRobots[1][robot.robot_id()]._x + prevRobots[2][robot.robot_id()]._x) / 3.0;
			robots[robot.robot_id()]._y = (prevRobots[0][robot.robot_id()]._y + prevRobots[1][robot.robot_id()]._y + prevRobots[2][robot.robot_id()]._y) / 3.0;
			robots[robot.robot_id()]._orientation = (prevRobots[0][robot.robot_id()]._orientation + prevRobots[1][robot.robot_id()]._orientation + prevRobots[2][robot.robot_id()]._orientation) / 3.0;
			robots[robot.robot_id()]._confidence = robot.confidence();
		}

		int size() {
			int s = 0;
			for (int i = 0; i < 10; i++) {
				s = (robots[i].onField()) ? s + 1 : s;
			}
			return s;
		}

		const RobotInfo & operator[](int i) const throw (char const *) {

			int index = -1;
			for (int j = 0; j < 10 && index != i; j++) {
				if (robots[j].onField()) {
					index++;
				}
			}

			if (index != -1) {
				return robots[index];
			} else {
				throw "RobotList empty.";
			}
		}
		RobotInfo & operator[](int i) throw (char const *) {

			int index = -1;
			for (int j = 0; j < 10 && index != i; j++) {
				if (robots[j].onField()) {
					index++;
				}
			}

			if (index != -1) {
				return robots[index];
			} else {
				throw "RobotList empty.";
			}
		}
};

#endif /* ROBOTLIST_H_ */
