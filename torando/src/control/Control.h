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

#include <ThreadModule.h>

#include "../templates/List.h"


#include "Strategy.h"
#include "Referee.h"
#include "Robot.h"

class Control: public ThreadModule {
	Q_OBJECT
	public:

		/**
		 *     Esta classe é baseada no padrão Singleton, onde só permite uma instancia do tipo
		 *  Control no longo da execução do programa.
		 *     Podemos dividir a classe em duas partes: membros estáticos e nao estáticos.
		 *
		 *     Membros estáticos: é uma interface de comunicação com o módulo, são os unicos membros
		 *  públicos da classe, e servem para simplificar a interação com os outros módulos
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
		static void startModule() {
			getInsance().start();
		}
		/**
		 *   Tenta parar a execuçao do módulo de controle.
		 */
		static void stopModule() {
			getInsance().stop();
		}

	protected:
		/*
		 *   Toda classe derivada da classe Module segue o padrão singleton,
		 * isto é, possui apenas uma instancia da classe durante o longo do
		 * programa.
		 *   Portanto para conseguir esta unica instancia, precisa-se chamar o
		 * método estático getInstance() que retorna uma referencia da
		 * instancia.
		 */
		static Control & getInsance() {
			static Control control;
			return control;
		}

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
		 * um objeto do tipo Control.*/
		Control();
		virtual ~Control();
		Control(const Control &);
		Control & operator=(const Control&);
};

#endif /* CONTROL_H_ */
