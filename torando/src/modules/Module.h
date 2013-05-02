/*
 * Module.h
 *
 *  Created on: Apr 23, 2013
 *      Author: bruno
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <QObject>
#include <QtCore>

class Module: public QObject {
	Q_OBJECT
	protected:
		Module();
		virtual ~Module();

		/*
		 *
		 *   A classe Module é apenas uma base para se criar novos tipos de módulos,
		 * como por exemplo: ThreadModule(), TimerModule().
		 *   Todos os novos tipos de módulos devem possuir: métodos virtuais start, stop,
		 * onPreExecute, doInBackGround, onPosExecute.
		 */


		virtual void start() = 0;
		virtual void stop() = 0;

		virtual void onPreExecute() =0;
		virtual void doInBackground() =0;
		virtual void onPosExecute() =0;

	private:
		/*   Qualquer classe baseada em Module não pode ser copiada por construtor ou
		 * por operador de atribuição.  */
		Module(const Module&);
		Module& operator=(const Module&);
};

#endif /* MODULE_H_ */
