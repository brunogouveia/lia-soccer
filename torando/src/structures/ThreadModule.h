/*
 * ThreadModule.h
 *
 *  Created on: Apr 23, 2013
 *      Author: bruno
 */

#ifndef THREADMODULE_H_
#define THREADMODULE_H_

#include <Module.h>

#include <QObject>
#include <QtCore>
#include <QThread>

class ThreadModule: public Module {
	Q_OBJECT
	protected:
		/*
		 *
		 *   ThreadModule é uma classe derivada de Module, onde possui uma QThread.
		 *   Qualquer módulo que derivar de ThreadModule, tem uma característica:
		 * a repetição do método doInBackGround() será controlada por uma thread.
		 */

		ThreadModule();
		virtual ~ThreadModule();

		QThread t;
		QThread * getThread() {
			return &t;
		}

		/*   O método start() e stop() são métodos importantes e ja implentados que
		 * controlam a execução do módulo.
		 *   O cilo de um módulo é o seguinte: quando ele for iniciado, é executado
		 * uma vez o método start(), depois o método doInBackGround() fica sendo executado
		 * repetidamente até o módulo parar (método stop() ser invocado), depois o método
		 * onPosExecute() é chamado uma unica vez.
		 *
		 *   IMPORTANTE: Aconselhamos a não reimplementar estes métodos. */
		void start();
		void stop();

		virtual void onConnectToThread(QThread * thread);
		virtual void onDisconnectToThread(QThread * thread);

		virtual void onPreExecute();
		virtual void doInBackground()=0;
		virtual void onPosExecute();

	protected slots:
		void exec();

	protected:
		bool firstRun;
		bool running;
};

#endif /* THREADMODULE_H_ */
