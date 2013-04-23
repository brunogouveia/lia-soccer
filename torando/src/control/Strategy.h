/*
 * Strategy.h
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

class Strategy {
	public:
		Strategy();
		virtual ~Strategy();

		// Accepted game events.
		typedef enum {
			None, Halt, StartPlay, StopPlay, Neutral, KickOff, KickOffOther, Penalty, PenaltyOther, FreeKick, FreeKickOther, Indirect, IndirectOther,

		} GameEvent;

		// debug: GameState should be set in constructor!

		// Starts a thread to consume events.
		bool start();

		// Stops the event loop thread.
		void stop();

		// Insert a new game event.
		void insertEvent(GameEvent event);

		// The strategy's event loop is running.
		bool isRunning() {
			return _running;
		}

	protected:

		/*** Robot and ball locations information ***/

		// Fills 'team', 'opponent' and 'ball' with information.

		/*** Other informations ***/

		int getTeamId() {
			return _teamId;
		}

		/** Game events
		 */

		virtual void startPlay(){

		}
		virtual void stopPlay(){

		}

		virtual void prepareNeutral() {
		}

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

		// Loop for event consume.
		void eventLoop();

		// Blocks until a new game event arrives and returns it.
		GameEvent waitNextEvent();

		// Consume game events stored in the event queue calling the respective
		// event virtual methods.
		// Obs: not synchronized!
		void consumeEvent(GameEvent event);

		// Cancel all pending command threads and wait them to join.
		void stopAllThreads();

		// Calls eventLoop().
		static void *startLoopThread(void *args);

		// Calls consumeEvent().
		static void *startConsumeThread(void *args);

		// Synchonyzed access:
		//
		int _teamId;    // This strategy team.

		bool _haveToFinish;  // Signals derived class to finish.
		bool _playing;       // Some strategy game method is running.
		bool _running;       // Event loop is running.

		// Thread stuffs.
		//

		//std::list<pthread_t> _threadSet;
};

#endif /* STRATEGY_H_ */
