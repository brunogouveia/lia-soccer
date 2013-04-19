/*
 * Vision.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef VISION_H_
#define VISION_H_

#include <QObject>
#include <QtCore>

#include "../templates/List.h"
#include "RobotInfo.h"
#include "BallInfo.h"
#include "FIeldInfo.h"

class Update;

class Vision: public QObject {
	Q_OBJECT
	public:

		static List<RobotInfo> robots;
		static List<RobotInfo> opponents;

		static BallInfo ball;
		static FIeldInfo field;

		/**
		 *   Este método inicializa o módulo responsável por atualizar os atributos
		 * dessa classe, por padrão, a cada 10 milisegundos ocorre uma tentativa
		 * de atualização, porém pode-se alterar usando o método changeInterval().
		 *
		 *   O Update atualiza automaticamente os atributos desta classe, então não precisa
		 * se preocupar com isso.
		 *   Enquanto este método não for chamado, a atualização não vai acontecer.
		 */
		static void startUpdate();

		/**
		 *   Este método para o módulo responsável por atualizar os atributos
		 * dessa classe.
		 *
		 *   Desencorajamos de chamar esse método a qualquer momento, pois pode gerar
		 * atraso nos próximos pacotes recebidos pelo ssl-vision.
		 */
		static void stopUpdate();

		/**
		 *   Por padrão o módulo de atualização executa a cada 10 milisegundos, porém
		 * esse tempo pode ser alterado com este método.
		 */
		static void changeInterval(int milSeconds);

	private:


		static Update update;

		/*   Este métodos estão privados para evitar que alguem instancie um objeto do
		 * tipo Vision.*/
		Vision();
		virtual ~Vision(){
		}
		Vision(Vision &);
		Vision & operator=(const Vision &);

};

class Update: public QObject {
	Q_OBJECT
	private:
		friend class Vision;

		int milSeconds;
		QTimer timer;

		Update() :
				milSeconds(1), timer(NULL) {
			connect(&timer, SIGNAL(timeout()), this, SLOT(updateMethod()));
		}
		~Update() {
			disconnect(&timer, SIGNAL(timeout()), this, SLOT(updateMethod()));
		}

		/**
		 *   Inicia o timer responsável por executar o método que pega os pacotes do
		 * ssl-vision pela rede e atualizar os atributos da classe Vision.
		 */
		void start() {
			timer.start(milSeconds);
		}

		/**
		 *   Para o timer, ou seja, para de atualizar os atributos da classe Vision.
		 */
		void stop() {
			timer.stop();
		}

		/**
		 *   Muda a quantidade de tempo que o método responsável pelo update espera para
		 * executar de novo. Após a chamada desse método, a atualização ocorrerá a cada
		 * milSecond milisegundos.
		 */
		void changeInterval(int milSeconds) {
			timer.setInterval(milSeconds);
			this->milSeconds = milSeconds;
		}

	private slots:

		/**
		 *   Aqui é que as coisas acontecem, updateMethod é o cara responsável por realmente pegar
		 * os pacotes, processar, e atualizar os atributos da classe Vision. O resto são só camadas
		 * superficias para controle ou deixar o código bonito e simples.
		 */
		void updateMethod();
};

#endif /* VISION_H_ */
