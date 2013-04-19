/*
 * Control.h
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <QObject>
#include <QtCore>
#include <QThread>
#include <stdio.h>

#include "../templates/List.h"

#include "Referee.h"
#include "Robot.h"

class Control: public QObject {
	Q_OBJECT
	public:

		/**
		 *     Esta classe é baseada no padrão Singleton, onde só permite uma instancia do tipo
		 *  Control no longo da execução do programa.
		 *     Podemos dividir a classe em duas partes: membros estáticos e nao estáticos.
		 *
		 *     Membros estáticos: são os membros responsáveis por controlar o módulo de controle
		 *  como por exemplo iniciar, parar, verificar se o módulo está rodando. Estes membros
		 *  que estão visíveis nas demais partes do programa.
		 *
		 *     Membros não estáticos: são os membros reponsáveis por fazer o "trabalho sujo" do
		 *  módulo, eles que realmente fazem o processamento e são acessados a partir da única
		 *  instancia do tipo Control.
		 */

		/**
		 *   Chame esse método para o módulo de controle começar a
		 * ser executado.
		 * 	 Observe que você pode o módulo de controle a qualquer
		 * momento chamando o método stop().
		 */
		static void start();

		/**
		 *   Tenta parar a execuçao do módulo de controle.
		 *   Observe que após este método ser chamado, pode ser
		 * que o módulo de controle não pare imediatamente, para
		 * verificar se o módulo realmente parou, use o método
		 * isRunning().
		 *   Pode-se também chamar o método waitStop(), para forçar
		 * que o seu código continue apenas depois do módulo ter
		 * parado de fato.
		 */
		static void stop();

		/**
		 *   Retorna se o módulo está sendo executado.
		 */
		static bool isRunning();

		/**
		 *   Após este método ser invocado, ele retorna apenas quando
		 * o módulo de controle parar de executar.
		 */
		static void waitStop();

	private:

		static Control control;
		static QThread thread;

		static bool running;;

		/*Parte obscura da classe Controle, se você não é programador, vaza daqui!*/
	private:
		/*   Este métodos estão como privado para evitar que alguem acidentalmente
		 * ou conscientemente instancie  um objeto do tipo Control.*/
		Control();
		virtual ~Control();

		/*   Estes dois métodos não devem ser implementados, pois não faz sentido
		 * permitir um objeto do tipo Control ser copiado.*/
		Control(const Control &);
		Control & operator=(const Control&);

		/*   Este método vai ser executado enquanto o módulo de controle estiver
		 * sendo executado.
		 *   Note que o módulo de controle só poderá ser encerrado entre o fim de
		 * uma execução e no começo de outra execução desse método, portanto tenha
		 * cuidado de não deixar um loop torando aqui dentro ou fazer ela demorar
		 * muito. */
		void controlLoop();

	private slots:
		void exec();

	private:
		List<Robot> robots;
};

#endif /* CONTROL_H_ */
