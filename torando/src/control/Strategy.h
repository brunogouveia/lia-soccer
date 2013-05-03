/*
 * Strategy.h
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <Vision.h>
#include <Robot.h>

class Strategy: public QObject {
		Q_OBJECT
	public:
		Strategy();
		virtual ~Strategy();


		/**
		 *   Cada método retorna um estado do jogo, estes métodos vao ser chamados de acordo
		 * ao comando que o juiz envia.
		 */

		virtual void startPlay() {
		}
		virtual void stopPlay() {
		}
		virtual void halt() {
		}

		/**
		 *   Todos estes métodos preparam o jogo para o estado, ou seja
		 * eles posicionam o robo, porem não retornam a jogar enquanto
		 * o juiz não enviar o comando de start.
		 *
		 *   Chame o método prepareKickOff(), os robos vao se posicionar
		 * para cobrar o kick off, porem nao vao chutar a bola até o comando
		 * ser enviado pelo juiz, e conseguentemente o método startPlay()
		 * ser chamado.
		 */
		virtual void prepareKickOff() {
		}
		virtual void prepareKickOffOther() {
		}
		virtual void preparePenalty() {
		}
		virtual void preparePenaltyOther() {
		}
		virtual void prepareFreeKick() {
		}
		virtual void prepareFreeKickOther() {
		}
		virtual void prepareIndirect() {
		}
		virtual void prepareIndirectOther() {
		}

	private:
		bool running;

		List<Robot> robots;
		friend class Control;

};

#endif /* STRATEGY_H_ */
