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

#include <TimerModule.h>

#include "netraw.h"
#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"

class Communication: TimerModule {
	Q_OBJECT
	public:

		/**
		 *     Esta classe é baseada no padrão Singleton, onde só permite uma instancia do tipo
		 *  Communication no longo da execução do programa.
		 *     Podemos dividir a classe em duas partes: membros estáticos e nao estáticos.
		 *
		 *     Membros estáticos: é uma interface de comunicação com o módulo, são os unicos membros
		 *  públicos da classe, e servem para simplificar a interação com os outros módulos
		 *
		 *     Membros não estáticos: são os membros reponsáveis por fazer o "trabalho sujo" do
		 *  módulo, eles que realmente fazem o processamento e são acessados a partir da única
		 *  instancia do tipo Communication.
		 */

		/*
		 *   Este método inicia o módulo responsável por enviar as ações que
		 * cada robo deve executar, por padrão, a cada 1 milisegundos ocorre
		 * uma tentativa de envio, porém pode-se alterar usando o método
		 * changeInterval().
		 *
		 *   Enquanto este método não for chamado, a atualização não vai acontecer.
		 */
		static void startModule();

		/**
		 *   Para o módulo de comunicação.
		 */
		static void stopModule();

		/**
		 *   Por padrão o modulo envia os pacotes de comunicação a cada 1 mili segundo,
		 * porém isto pode ser alterado com este método.
		 */
		static void changeInterval(int milSeconds);

		/**
		 *   Método que faz o robo chutar "para frente".
		 *   Index é o número do robo, e speed é a velocidade em m/s do chute.
		 */
		static void kickX(int index, float speed);

		/**
		 *   Método que faz o robo chutar "por cobertura".
		 *   index é o número do robo, e speed é a velocidade em m/s do chute.
		 */
		static void kickZ(int index, float speed);

		/**
		 *   Método que ativa ou desativa o drible do robo index.
		 */
		static void drible(int index, bool drible);

		/**
		 *   Define a velocidade de cada roda do robo index em rad/s (pode ser negativa).
		 */
		static void setWheelsVelocity(int index, float frontRight, float frontLeft, float backRight, float backLeft);

	protected:
		/*
		 *   Toda classe derivada da classe Module segue o padrão singleton,
		 * isto é, possui apenas uma instancia da classe durante o longo do
		 * programa.
		 *   Portanto para conseguir esta unica instancia, precisa-se chamar o
		 * método estático getInstance() que retorna uma referencia da
		 * instancia.
		 */

		static Communication & getInstance() {
			static Communication communication;
			return communication;
		}

		/*Utilizado para enviar as ações do robo.*/
		Net::UDP udpsocket;
		Net::Address _addr;

		/**
		 *   Métodos utilizados durante a execução do módulo.
		 *   Quando o módulo é iniciado, o método onPreExecute é chamado
		 * uma vez. Depois o método doInBackGround é chamado enquanto o
		 * módulo estiver ativo.
		 *   Quando o método stopModule() for chamado, o método doInBackGround
		 * para de ser chamado, e é chamado apenas uma vez o método onPosExecute().
		 */
		virtual void onPreExecute();
		virtual void doInBackGround();
		virtual void onPosExecute();

	private:

		/*   Este métodos estão privados para evitar que alguem instancie ou copie
		 * um objeto do tipo Communication.*/
		Communication();
		Communication(const Communication&);
		virtual ~Communication();
		Communication & operator=(const Communication&);

		class Packet {
			public:
				float wheels[4];
				float kickXSpeed;
				float kickZSpeed;
				bool spinner;
				bool able;

				Packet() {
					for (int i = 0; i < 4; i++) {
						wheels[i] = 0.0;
					}
					kickXSpeed = 0.0;
					kickZSpeed = 0.0;
					spinner = false;
					able = false;
				}
				~Packet() {
				}

		};
		Packet packets[10];

};

#endif /* COMMUNICATION_H_ */
