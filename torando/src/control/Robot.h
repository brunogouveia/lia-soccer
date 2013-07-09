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

#include <Vision.h>
#include <Target.h>
#include <TargetFixed.h>
#include <RobotInfo.h>
#include <Path.h>
#include <Rrt.h>

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

		Robot(RobotInfo & info) :
				info(info), path(info), destination(info), lookat(info), rrt(info, Vision::ball) {
			this->info = info;
			this->lookat = Vision::opponentGoal;

			/*TODO : encontrar o id correto*/
			//this->_id = findRobotId();
			this->_id = 0;

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
		void kickTo(Target & to, float power);

		/**
		 *   Liga ou desliga o dribble.
		 */
		void dribble(bool on);

	private:
		TargetFixed getNextPoint();
		float potential(float x, float y);

	private slots:
		/**
		 *   Este método faz o processamento, ou seja, ele que faz o robo seguir o
		 * alvo.
		 */
		void loop();

	private:

		RobotInfo & info;
		Path path;
		Target destination, lookat;
		Rrt rrt;

		int _id;
		QThread thread;

		int findRobotId();

};

#endif /* ROBOTCONTROL_H_ */
