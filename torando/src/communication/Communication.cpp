/*
 * Communication.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: bruno
 */

#include "Communication.h"

#include <stdio.h>

Communication::Communication() {
	printf("Communication::Communication\n");
}

Communication::~Communication() {
	printf("Communication::~Communication\n");
}

void Communication::startModule() {
	printf("Communication::startModule - started\n");
	getInstance().start();
	printf("Communication::startModule - finished\n");
}
void Communication::stopModule() {
	printf("Communication::stopModule - started\n");
	getInstance().stop();
	printf("Communication::stopModule - finished\n");
}

void Communication::changeInterval(int milSeconds){
	printf("Communication::changeInterval - started\n");
	getInstance().setInterval(milSeconds);
	printf("Communication::changeInterval - finished\n");
}

void Communication::kickX(int index, float speed) {
	printf("Communication::kickX - started\n");
	getInstance().packets[index].kickXSpeed = speed;
	printf("Communication::kickX - finished\n");
}

void Communication::kickZ(int index, float speed) {
	printf("Communication::kickZ - started\n");
	getInstance().packets[index].kickZSpeed = speed;
	printf("Communication::kickZ - finished\n");
}

void Communication::drible(int index, bool drible) {
	printf("Communication::drible - started\n");
	getInstance().packets[index].spinner = drible;
	printf("Communication::drible - finished\n");
}

void Communication::setWheelsVelocity(int index, float frontRight, float frontLeft, float backRight, float backLeft) {
	printf("Communication::setWheelsVelocity - started\n");
	getInstance().packets[index].wheels[0] = frontLeft;
	getInstance().packets[index].wheels[1] = backLeft;
	getInstance().packets[index].wheels[2] = backRight;
	getInstance().packets[index].wheels[3] = frontRight;
	printf("Communication::setWheelsVelocity - finished\n");
}

/*void Communication::start(int index) {

 }

 void Communication::stop(int index) {

 }*/

void Communication::onPreExecute() {
	printf("Communication::onPreExecute - started\n");
	udpsocket.close();
	bool flag = _addr.setHost("127.0.0.1", 20011);
	if (udpsocket.open(20011, false, false, false) && flag)
		printf("SendPacket conectou\n");
	printf("Communication::onPreExecute - finished\n");
}

void Communication::doInBackGround() {
	printf("Communication::doInBackGround - started\n");

	grSim_Packet packet;

	bool yellow = true;
	packet.mutable_commands()->set_isteamyellow(yellow);
	packet.mutable_commands()->set_timestamp(0.0);
	for (int i = 0; i < 10; i++) {
		grSim_Robot_Command* command = packet.mutable_commands()->add_robot_commands();
		command->set_id(i);

		command->set_wheelsspeed(true);
		command->set_wheel1(packets[i].wheels[0]);
		command->set_wheel2(packets[i].wheels[1]);
		command->set_wheel3(packets[i].wheels[2]);
		command->set_wheel4(packets[i].wheels[3]);
		command->set_veltangent(0.0);
		command->set_velnormal(0.0);
		command->set_velangular(0.0);
		command->set_kickspeedx(packets[i].kickXSpeed);
		command->set_kickspeedz(packets[i].kickZSpeed);
		command->set_spinner(packets[i].spinner);
	}
	std::string s;
	packet.SerializeToString(&s);
	udpsocket.send((void*) s.c_str(), s.length(), _addr);
	printf("Communication::doInBackGround - finished\n");
}

void Communication::onPosExecute() {
	printf("Communication::onPosExecute - started\n");
	udpsocket.close();
	printf("Communication::onPosExecute - finished\n");
}
