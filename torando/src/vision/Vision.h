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

#include <TimerModule.h>
#include <ThreadModule.h>

#include <iostream>

#include "robocup_ssl_client.h"
#include "robocup_ssl_referee.h"

#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

#include "RobotList.h"
#include "RobotInfo.h"
#include "BallInfo.h"
#include "FieldInfo.h"

#include <TargetFixed.h>

class Update;

class Vision: public TimerModule {
	Q_OBJECT
	public:

		/**
		 *     Esta classe é baseada no padrão Singleton, onde só permite uma instancia do tipo
		 *  Vision no longo da execução do programa.
		 *     Podemos dividir a classe em duas partes: membros estáticos e nao estáticos.
		 *
		 *     Membros estáticos: é uma interface de comunicação com o módulo, são os unicos membros
		 *  públicos da classe, e servem para simplificar a interação com os outros módulos
		 *
		 *     Membros não estáticos: são os membros reponsáveis por fazer o "trabalho sujo" do
		 *  módulo, eles que realmente fazem o processamento e são acessados a partir da única
		 *  instancia do tipo Vision.
		 */

		static RobotList robots;
		static RobotList opponents;

		static BallInfo ball;
		static FieldInfo field;
		static TargetFixed opponentGoal;
		static TargetFixed goal;

		/**
		 *   Este método inicializa o módulo responsável por atualizar os atributos
		 * dessa classe, por padrão, a cada 1 milisegundos ocorre uma tentativa
		 * de atualização, porém pode-se alterar usando o método changeInterval().
		 *
		 *   O Update atualiza automaticamente os atributos desta classe, então não precisa
		 * se preocupar com isso.
		 *   Enquanto este método não for chamado, a atualização não vai acontecer.
		 */
		static void startModule();

		/**
		 *   Este método para o módulo responsável por atualizar os atributos
		 * dessa classe.
		 *
		 *   Desencorajamos de chamar esse método a qualquer momento, pois pode gerar
		 * atraso nos próximos pacotes recebidos pelo ssl-vision.
		 */
		static void stopModule();

		/**
		 *   Por padrão o módulo de atualização executa a cada 10 milisegundos, porém
		 * esse tempo pode ser alterado com este método.
		 */
		static void changeInterval(int milSeconds);

		/**
		 * 	 Este método retorna se um ponto está ou não ocupado por algum robô e/ou bola.
		 */

		static bool isFree(Target position, double tolerance = 100.0);

	protected:

		/*
		 *   Toda classe derivada da classe Module segue o padrão singleton,
		 * isto é, possui apenas uma instancia da classe durante o longo do
		 * programa.
		 *   Portanto para conseguir esta unica instancia, precisa-se chamar o
		 * método estático getInstance() que retorna uma referencia da
		 * instancia.
		 */
		static Vision & getInstance() {
			static Vision vision;
			return vision;
		}

		/* Atributos utilizados para pegar a informação do ssl-vision.  */
		RoboCupSSLClient client;
		SSL_WrapperPacket packet;

		/**
		 *   Métodos utilizados durante a execução do módulo.
		 *   Quando o módulo é iniciado, o método onPreExecute é chamado
		 * uma vez. Depois o método doInBackGround é chamado enquanto o
		 * módulo estiver ativo.
		 *   Quando o método stopModule() for chamado, o método doInBackGround
		 * para de ser chamado, e é chamado apenas uma vez o método onPosExecute().
		 */
		virtual void onPreExecute();
		virtual void doInBackground();
		virtual void onPosExecute();

	private:

		/*   Este métodos estão privados para evitar que alguem instancie ou copie
		 * um objeto do tipo Vision.*/
		Vision();
		virtual ~Vision();
		Vision(Vision &);
		Vision & operator=(const Vision &);


};

#endif /* VISION_H_ */
