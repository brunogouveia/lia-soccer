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

class Referee: public QObject {
	Q_OBJECT
	public:

		static void start();

		static void stop();

	signals:
		void refereeReceived();

	private slots:
		void refereeLoop();

	private:

		static Referee referee;
		QTimer timer;

		Referee();
		virtual ~Referee();

};

#endif /* REFEREE_H_ */
