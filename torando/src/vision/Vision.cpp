/*
 * Vision.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#include "Vision.h"

RobotList Vision::robots;
RobotList Vision::opponents;

FieldInfo Vision::field;
BallInfo Vision::ball;
TargetFixed Vision::opponentGoal(3090.0,0.0);
TargetFixed Vision::goal(-3090.0,0.0);

Vision::Vision() {
	printf("Vision::Vision\n");
}

Vision::~Vision() {
	printf("Vision::~Vision\n");
}

void Vision::startModule() {
	printf("Vision::startModule - started\n");
	getInstance().start();
	printf("Vision::startModule - finished\n");
}

void Vision::stopModule() {
	printf("Vision::stopModule - started\n");
	getInstance().stop();
	printf("Vision::stopModule - finished\n");
}

void Vision::changeInterval(int milSeconds) {
	printf("Vision::changeInterval - started\n");

	getInstance().setInterval(milSeconds);

	printf("Vision::changeInterval - finished\n");

}

void Vision::onPreExecute() {
	printf("Vision::onPreExecute - started\n");
	client.open(true);
	printf("Vision::onPreExecute - finished\n");
}

void Vision::doInBackground() {
	//printf("Vision::doInBackGround - started\n");

	if (client.receive(packet)) {
		//printf("-----Received Wrapper Packet---------------------------------------------\n");
		//see if the packet contains a robot detection frame:

		if (packet.has_detection()) {
			SSL_DetectionFrame detection = packet.detection();
			//Display the contents of the robot detection results:

			int balls_n = detection.balls_size();
			int robots_blue_n = detection.robots_blue_size();
			int robots_yellow_n = detection.robots_yellow_size();

			//Ball info:
			int correctBallId = -1;
			SSL_DetectionBall current;
			SSL_DetectionBall correctBall;
			int ballConfidence = 0.0;
			static int ballMiss = 0;
			for (int i = 0; i < balls_n; i++) {
				current = detection.balls(i);
				if (current.confidence() > ballConfidence) {
					ballConfidence = detection.balls(i).confidence();
					correctBallId = i;
					correctBall = current;
				}
			}

			if (correctBallId != -1) {
				Vision::ball.updateBall(correctBall);
				Vision::ball._confidence = correctBall.confidence();
				ballMiss = 0;
			} else {
				ballMiss++;
			}
			Vision::ball._onField = !(ballMiss > 10);

			//Blue robot info:

			for (int i = 0; i < robots_blue_n; i++) {
				Vision::robots.updateRobot(detection.robots_blue(i));
			}
			for (int i = 0; i < 10; i++) {
				Vision::robots.robots[i]._onField = !(++(Vision::robots.robotsMisses[i]) > 10);
			}

			//Yellow robot info:
			for (int i = 0; i < robots_yellow_n; i++) {
				Vision::opponents.updateRobot(detection.robots_yellow(i));
			}
			for (int i = 0; i < 10; i++) {
				Vision::opponents.robots[i]._onField = !(++(Vision::opponents.robotsMisses[i]) > 10);
			}

		}

		//see if packet contains geometry data:
		if (packet.has_geometry()) {
			const SSL_GeometryData & geom = packet.geometry();
			//printf("-[Geometry Data]-------\n");

			const SSL_GeometryFieldSize & field = geom.field();
			/*printf("Field Dimensions:\n");
			 printf("  -line_width=%d (mm)\n", field.line_width());
			 printf("  -field_length=%d (mm)\n", field.field_length());
			 printf("  -field_width=%d (mm)\n", field.field_width());
			 printf("  -boundary_width=%d (mm)\n", field.boundary_width());
			 printf("  -referee_width=%d (mm)\n", field.referee_width());
			 printf("  -goal_width=%d (mm)\n", field.goal_width());
			 printf("  -goal_depth=%d (mm)\n", field.goal_depth());
			 printf("  -goal_wall_width=%d (mm)\n", field.goal_wall_width());
			 printf("  -center_circle_radius=%d (mm)\n", field.center_circle_radius());
			 printf("  -defense_radius=%d (mm)\n", field.defense_radius());
			 printf("  -defense_stretch=%d (mm)\n", field.defense_stretch());
			 printf("  -free_kick_from_defense_dist=%d (mm)\n", field.free_kick_from_defense_dist());
			 printf("  -penalty_spot_from_field_line_dist=%d (mm)\n", field.penalty_spot_from_field_line_dist());
			 printf("  -penalty_line_from_spot_dist=%d (mm)\n", field.penalty_line_from_spot_dist());*/

			int calib_n = geom.calib_size();
			for (int i = 0; i < calib_n; i++) {
				const SSL_GeometryCameraCalibration & calib = geom.calib(i);
				/*printf("Camera Geometry for Camera ID %d:\n", calib.camera_id());
				 printf("  -focal_length=%.2f\n", calib.focal_length());
				 printf("  -principal_point_x=%.2f\n", calib.principal_point_x());
				 printf("  -principal_point_y=%.2f\n", calib.principal_point_y());
				 printf("  -distortion=%.2f\n", calib.distortion());
				 printf("  -q0=%.2f\n", calib.q0());
				 printf("  -q1=%.2f\n", calib.q1());
				 printf("  -q2=%.2f\n", calib.q2());
				 printf("  -q3=%.2f\n", calib.q3());
				 printf("  -tx=%.2f\n", calib.tx());
				 printf("  -ty=%.2f\n", calib.ty());
				 printf("  -tz=%.2f\n", calib.tz());*/

				if (calib.has_derived_camera_world_tx() && calib.has_derived_camera_world_ty() && calib.has_derived_camera_world_tz()) {
					/*printf("  -derived_camera_world_tx=%.f\n", calib.derived_camera_world_tx());
					 printf("  -derived_camera_world_ty=%.f\n", calib.derived_camera_world_ty());
					 printf("  -derived_camera_world_tz=%.f\n", calib.derived_camera_world_tz());*/
				}

			}
		}
	}

	//printf("Vision::doInBackGround - terminated\n");
}

void Vision::onPosExecute() {
	printf("Vision::onPosExecute - started\n");

	client.close();

	printf("Vision::onPosExecute - terminated\n");
}
