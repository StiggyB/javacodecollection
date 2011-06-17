/**
 * Timer
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 5: OS-Timer
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 *this class will provide the functionality to execute functions in x milliseconds for Puck_fsm and HALCore objects
 *
 *
 */
#ifndef TIMER_H_
#define TIMER_H_

#include "Communication.h"
#include "../Thread/Mutex.h"
#include "../Thread/Singleton_T.h"
#include "../Thread/HAWThread.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "../Functor/CallInterface.h"
#include "../Functor/CallBackThrower.h"

#include <errno.h>
#include <vector>
#include <sys/time.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>


class Timer : public thread::HAWThread, public Communication, public Singleton_T<Timer>{
	friend class Singleton_T<Timer>;
public:
	Timer();
	virtual ~Timer();
	/**
	 *
	 */
	int addUnstoppableFunction(CallInterface<CallBackThrower,void>* funcp);
	std::vector< CallInterface<CallBackThrower,void>* > unstoppable_funcp_list;
	/**
	 * adds a functor to internal list and activate Timer
	 * \param funcp functor, the function of HALCore, which will be execute after timer timeout
	 * \param timer time im milliseconds, after this time the given function will be executed
	 * \return a bool, true if action was successful, false if not.
	 */
	//bool addTimerFunction( CallInterface<HALCore, void>* funcp, int timer );
	int addTimerFunction( CallInterface<CallBackThrower, void>* funcp, int ms);
	/**
	 * delete a Timer by a specific internal id
	 * \param id specified the timer, which should be stopped
	 */
	int deleteTimer(int id);
	/**
	 * restart all actual timer
	 * if the list contains active timer, this timers will be ignored
	 */
	int startAllTimer();
	/**
	 * stop all active timer
	 * after this operation, new timer can be set
	 */
	int stopAll_actual_Timer();
	/**
	 * get the actual system time in ms
	 * usage for compare between 2 times
	 */
	long getSystemTime_ms();
	/**
	 *
	 */
	int deleteAllTimer();

protected:
	virtual void execute(void*);
	virtual void shutdown();
	virtual void handlePulsMessage();
	virtual void handleNormalMessage();
	/**
	 * default receiver for communication
	 */
	CommunicatorType receiver;


private:
	/**
	 * vector list, which contains the id (comes from pulse message) to find the right functor
	 */
	std::vector< struct IdTOfunction> funcp_list;
	/**
	 * internal function to find a specific functor in actual list
	 * \param id this is the attribute for searching in list
	 * \return a struct idTOfunction, if the id contains -1, the search was not successful, otherwise successful
	 */
	struct IdTOfunction find_function(int id);
	/**
	 * internal function to add functor to list
	 * \param new_element this struct already contains already the given type and functor
	 * \param timer time im milliseconds, after this time the given function will be executed
	 * \return a bool, true if action was successful, false if not.
	 */
	int addTimerFunction(struct IdTOfunction new_element, int ms);
	/**
	 * calculates the seconds and nanoseconds for timer attributes
	 * \param ms milliseconds, will be splitted into seconds and nanoseconds
	 * \param s int pointer, into this the seconds will be stored
	 * \param ns int pointer, into this the nanoseconds will be stored
	 * \return a integer, 0 if action was successful, -1 if not.
	 */
	int calculateTime(int ms, int *s, int *ns);
	/**
	 * calculates the next id to avoid gaps in list and also overflow of list size
	 * \return a integer, this is the next free id (not index) in list
	 */
	int getnextid();
	/**
	 * ensures threadsafety
	 */
	Mutex locker;

};

/**
 * struct to avoid double code and optional to expand functionality
 */
union Functionpointer{
	//CallInterface<Puck_FSM_1, void>* funcp_fsm;
	//CallInterface<HALCore, void>* funcp_hal;
	CallInterface<CallBackThrower,void> * funcp_cbt_void;
};


/**
 * struct, which store id and functor
 */
struct IdTOfunction{
	int id;
	//int type;
	int timer_id;
	long systemtime_ms;
	int duration_ms;
	Functionpointer funcp;
};

#endif /* TIMER_H_ */
