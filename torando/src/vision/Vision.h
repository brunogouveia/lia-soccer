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

//#include <ThreadModule.h>

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
		static void start();

		/**
		 *   Este método para o módulo responsável por atualizar os atributos
		 * dessa classe.
		 *
		 *   Desencorajamos de chamar esse método a qualquer momento, pois pode gerar
		 * atraso nos próximos pacotes recebidos pelo ssl-vision.
		 */
		static void stop();

		/**
		 *   Por padrão o módulo de atualização executa a cada 10 milisegundos, porém
		 * esse tempo pode ser alterado com este método.
		 */
		static void changeInterval(int milSeconds);

	private slots:

		/**
		 *   Aqui é que as coisas acontecem, visionLoop() é o cara responsável por realmente pegar
		 * os pacotes, processar, e atualizar os atributos da classe Vision. O resto são só camadas
		 * superficias para controle ou deixar o código bonito e simples.
		 */
		void visionLoop();

	private:

		static Vision vision;
		QTimer timer;

		/*   Este métodos estão privados para evitar que alguem instancie um objeto do
		 * tipo Vision.*/
		Vision();
		virtual ~Vision();
		Vision(Vision &);
		Vision & operator=(const Vision &);

};

#endif /* VISION_H_ */
