/*
 * Communication.h
 *
 *  Created on: Apr 18, 2013
 *      Author: bruno
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <QObject>
#include <QtCore>
#include <QTimer>
#include <QtNetwork>

#include "netraw.h"
#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"

class Communication: QObject {
	Q_OBJECT
	public:
		enum Drible {
			Forwards, Backwards, Stop
		};

		static void start();
		static void stop();

		static void kick(int index);

		static void drible(int index, Drible drible);

		static void setWheelsVelocity(int index, float frontRight, float frontLeft, float backRight, float backLeft);

		static void start(int index);

		static void stop(int index);

		static Communication communication;
		QTimer timer;

		Net::UDP udpsocket;
		Net::Address _addr;

	private slots:

		void preExecute();
		void sendPacket();
		void posExecute();

	private:

		Communication();
		Communication(const Communication&);
		virtual ~Communication();
		Communication & operator=(const Communication&);

		class Packet {
			public:
				float wheels[4];
				bool able;

				Packet() {
					able = false;
					for (int i = 0; i < 4; i++) {
						wheels[i] = 0.0;
					}
				}
				~Packet() {
				}

		};
		Packet packets[10];

};

#endif /* COMMUNICATION_H_ */
