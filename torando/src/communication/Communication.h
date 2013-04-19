/*
 * Communication.h
 *
 *  Created on: Apr 18, 2013
 *      Author: bruno
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

class Communication {
	public:
		enum Drible {
			Forwards, Backwards, Stop
		};

		static void kick(int index);

		static void drible(int index, Drible drible);

		static void setWheelsVelocity(int index, float frontRight, float frontLeft, float backRight, float backLeft);

		static void start(int index);

		static void stop(int index);

	private:
		Communication();
		Communication(const Communication&);
		virtual ~Communication();
		Communication & operator=(const Communication&);

};

#endif /* COMMUNICATION_H_ */
