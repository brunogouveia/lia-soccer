/*
 * Referee.h
 *
 *  Created on: Apr 18, 2013
 *      Author: bruno
 */

#ifndef REFEREE_H_
#define REFEREE_H_

#include <QObject>
#include <QtCore>
#include <QTimer>

#include "referee.pb.h"
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MULTICAST_INTERFACE "eth0"
#define MULTICAST_ADDRESS "224.5.23.1"
#define MULTICAST_PORT "10003"

#include <TimerModule.h>

class Referee: public TimerModule {
Q_OBJECT
public:

	static void startModule() {
		getInstance().start();
	}

	static void stopModule() {
		getInstance().stop();
	}

	static Referee & getInstance() {
		static Referee referee;
		return referee;
	}

signals:
	void newCommand();

private:

	enum Stage {
		// The first half is about to start.
		// A kickoff is called within this stage.
		// This stage ends with the NORMAL_START.
		NORMAL_FIRST_HALF_PRE = 0,
		// The first half of the normal game, before half time.
		NORMAL_FIRST_HALF = 1,
		// Half time between first and second halves.
		NORMAL_HALF_TIME = 2,
		// The second half is about to start.
		// A kickoff is called within this stage.
		// This stage ends with the NORMAL_START.
		NORMAL_SECOND_HALF_PRE = 3,
		// The second half of the normal game, after half time.
		NORMAL_SECOND_HALF = 4,
		// The break before extra time.
		EXTRA_TIME_BREAK = 5,
		// The first half of extra time is about to start.
		// A kickoff is called within this stage.
		// This stage ends with the NORMAL_START.
		EXTRA_FIRST_HALF_PRE = 6,
		// The first half of extra time.
		EXTRA_FIRST_HALF = 7,
		// Half time between first and second extra halves.
		EXTRA_HALF_TIME = 8,
		// The second half of extra time is about to start.
		// A kickoff is called within this stage.
		// This stage ends with the NORMAL_START.
		EXTRA_SECOND_HALF_PRE = 9,
		// The second half of extra time.
		EXTRA_SECOND_HALF = 10,
		// The break before penalty shootout.
		PENALTY_SHOOTOUT_BREAK = 11,
		// The penalty shootout.
		PENALTY_SHOOTOUT = 12,
		// The game is over.
		POST_GAME = 13
	};

	enum Command {
		// All robots should completely stop moving.
		HALT = 0,
		// Robots must keep 50 cm from the ball.
		STOP = 1,
		// A prepared kickoff or penalty may now be taken.
		NORMAL_START = 2,
		// The ball is dropped and free for either team.
		FORCE_START = 3,
		// The yellow team may move into kickoff position.
		PREPARE_KICKOFF_YELLOW = 4,
		// The blue team may move into kickoff position.
		PREPARE_KICKOFF_BLUE = 5,
		// The yellow team may move into penalty position.
		PREPARE_PENALTY_YELLOW = 6,
		// The blue team may move into penalty position.
		PREPARE_PENALTY_BLUE = 7,
		// The yellow team may take a direct free kick.
		DIRECT_FREE_YELLOW = 8,
		// The blue team may take a direct free kick.
		DIRECT_FREE_BLUE = 9,
		// The yellow team may take an indirect free kick.
		INDIRECT_FREE_YELLOW = 10,
		// The blue team may take an indirect free kick.
		INDIRECT_FREE_BLUE = 11,
		// The yellow team is currently in a timeout.
		TIMEOUT_YELLOW = 12,
		// The blue team is currently in a timeout.
		TIMEOUT_BLUE = 13,
		// The yellow team just scored a goal.
		// For information only.
		// For rules compliance, teams must treat as STOP.
		GOAL_YELLOW = 14,
		// The blue team just scored a goal.
		GOAL_BLUE = 15
	};

	virtual void onPreExecute() {

		addrinfo hints;
		std::memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = 0;
		hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
		addrinfo *ai = 0;
		int gai_err;
		if ((gai_err = getaddrinfo(0, MULTICAST_PORT, &hints, &ai)) != 0) {
			exit(1);
		}

		// Look up the index of the network interface from its name.
		unsigned int ifindex = if_nametoindex(MULTICAST_INTERFACE);
		if (!ifindex) {
			printf("OK\n");
			exit(1);
		}

		// Create and bind a socket.
		sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (sock < 0) {
			exit(1);
		}
		if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
			exit(1);
		}

		// Join the multicast group.
		ip_mreqn mcreq;
		mcreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDRESS);
		mcreq.imr_address.s_addr = INADDR_ANY;
		mcreq.imr_ifindex = ifindex;
		if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcreq,
				sizeof(mcreq)) < 0) {
			exit(1);
		}

	}

	virtual void doInBackground() {

		// Receive a packet.
		uint8_t buffer[65536];
		ssize_t len = recv(sock, buffer, sizeof(buffer), 0);
		if (len < 0) {
			exit(1);
		}

		// Parse a Protobuf structure out of it.
		if (!status.ParseFromArray(buffer, len)) {
			exit(1);
		}

		// Display some information.
		std::cout << "TS=" << status.packet_timestamp() << ", stage="
				<< status.stage() << ", stage_time_left="
				<< status.stage_time_left() << ", command=" << status.command()
				<< ", yscore=" << status.yellow().score() << ", bscore="
				<< status.blue().score() << '\n';

	}

	virtual void onPosExecute() {
		close(sock);
	}

	SSL_Referee status;
	int sock;

	Referee();
	virtual ~Referee();

};

#endif /* REFEREE_H_ */
