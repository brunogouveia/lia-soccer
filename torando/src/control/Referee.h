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

class Referee: public TimerModule {
	Q_OBJECT
	public:
		static void startModule();
		static void stopModule();
		static Referee & getInstance() {
			static Referee referee;
			return referee;
		}

	signals:
		void newCommand();

	private:

		virtual void doInBackground() {

		}

		Referee();
		virtual ~Referee();

};

#endif /* REFEREE_H_ */
