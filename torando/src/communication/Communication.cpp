/*
 * Communication.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: bruno
 */

#include "Communication.h"

#include <stdio.h>

Communication Communication::communication;

Communication::Communication() {
	timer.setInterval(20);
	connect(&timer, SIGNAL(timeout()), this, SLOT(sendPacket()));
}

Communication::~Communication() {
	disconnect(&timer, SIGNAL(timeout()), this, SLOT(sendPacket()));
}

void Communication::start() {
	communication.preExecute();
	communication.timer.start();
}
void Communication::stop() {
	communication.timer.stop();
	communication.posExecute();
}

void Communication::kick(int index) {

}

void Communication::drible(int index, Drible drible) {

}

void Communication::setWheelsVelocity(int index, float frontRight, float frontLeft, float backRight, float backLeft) {
	communication.packets[index].wheels[0] = frontLeft;
	communication.packets[index].wheels[1] = backLeft;
	communication.packets[index].wheels[2] = backRight;
	communication.packets[index].wheels[3] = frontRight;
}

void Communication::start(int index) {

}

void Communication::stop(int index) {

}

void Communication::preExecute() {
	udpsocket.close();
	bool flag = _addr.setHost("127.0.0.1", 20011);
	if (udpsocket.open(20011, false, false, false) && flag)
		printf("SendPacket conectou\n");

}

void Communication::sendPacket() {
	printf("SendPacket\n");

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
		command->set_kickspeedx(0.0);
		command->set_kickspeedz(0.0);
		command->set_spinner(false);
	}
	std::string s;
	packet.SerializeToString(&s);
	udpsocket.send((void*) s.c_str(), s.length(), _addr);
}

void Communication::posExecute() {
	udpsocket.close();
}
