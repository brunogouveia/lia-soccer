/*
 * RobotControl.h
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#ifndef ROBOTCONTROL_H_
#define ROBOTCONTROL_H_

#include <QtCore>
#include <QThread>

class Robot: public QObject {
	Q_OBJECT
	public:
		/**
		 *   Em geral, o robo está parado ou seguindo algum alvo (TargetFixed, RobotInfo, BallInfo,...)
		 *   Ele sozinho possui uma rota para ir ate o caminho, e caso voce passe um alvo dinamico (que
		 * pode mudar de posição repentinamente), como por exemplo BallInfo, ele automaticamente ajusta
		 * o caminho para ir aquela posição. Ele também se adapta a casos em que algum objeto entre no
		 * meio do caminho.
		 *
		 */

		Robot(RobotInfo & info) {
			this->info = info;
			this->lookat = Vision::opponentGoal;
			this->_id = findRobotId();

			connect(&thread, SIGNAL(started()), this, SLOT(loop()));
		}
		virtual ~Robot() {
			disconnect(&thread, SIGNAL(started()), this, SLOT(loop()));
		}

		/**
		 *  Define o target para qual o robo deve ir.
		 */
		void followTarget(Target & target);

		/**
		 *   Define o target para qual o robo deve olhar.
		 */
		void lookAt(Target & lookat = Vision::opponentGoal);

		/**
		 *   Faz o robot chutar com a velocidade velocity m/s
		 */
		void kick(float velocity);

		/**
		 *   Liga ou desliga o dribble.
		 */
		void dribble(bool on);

	private slots:
		/**
		 *   Este método faz o processamento, ou seja, ele que faz o robo seguir o
		 * alvo.
		 */
		void loop();

	private:

		RobotInfo & info;
		Target & destination, lookat;
		Path path;
		int _id;
		QThread thread;

		int findRobotId();

};

#endif /* ROBOTCONTROL_H_ */
