/*
 * Control.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Control.h"

Control::Control() {
	Referee referee = Referee::getInstance();
	connect(&referee, SIGNAL(newCommand()), this, SLOT(callStrategy()));
}

Control::~Control() {
	Referee referee = Referee::getInstance();
	disconnect(&referee, SIGNAL(newCommand()), this, SLOT(callStrategy()));
}

void Control::onPreExecute() {
}

void Control::doInBackground() {
	printf("Control::doInBackGround - started\n");

	printf("Control::doInBackGround - finished\n");

}

void Control::onPosExecute() {
}

void Control::callStrategy() {

}

