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
	 * checks, if a given ID contains a active timer,
	 * \return a bool, 0 if no Timer is active, 1 if a Timer is active
	 */
	bool existTimer(int id);
	/**
	 * add a functionpointer to an internal list. if a stopAll_actualTimer is
	 * performed and this functionpointer
	 * was found, the Timer of this function will not stop
	 * \return an int, 0 on success, -1 on failure
	 */
	int addUnstoppableFunction(CallInterface<CallBackThrower,void>* funcp);
	/**
	 * unstoppable_funcp_list is a list of function pointer a avoid stopping this timer
	 */
	std::vector< CallInterface<CallBackThrower,void>* > unstoppable_funcp_list;
	/**
	 * adds a functor to internal list and activate Timer
	 * \param funcp functor, the function of HALCore, which will be execute after timer timeout
	 * \param ms time im milliseconds, after this time the given function will be executed
	 * \param id - the id of the timer.
	 * \returns an int, the id on success, or zero on failure.
	 */
	int addTimerFunction( CallInterface<CallBackThrower, void>* funcp, int ms, int id);
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
	struct timeval getSystemTime_struct();
	/**
	 *
	 */
	int deleteAllTimer();
	/**
	 * calculates the next id
	 * \return a integer, this is the next free id (not index)
	 */
	int getnextid();

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
	 * variable to provide a unique id for a getnextId request
	 */
	int id_counter;
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
	 * \param ms time im milliseconds, after this time the given function will be executed
	 * \returns an integer, the id on success, or zero if it failed.
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
	 * ensures threadsafety
	 */
	Mutex locker;

};

/**
 * struct to avoid double code and optional to expand functionality
 */
union Functionpointer{
	CallInterface<CallBackThrower,void> * funcp_cbt_void;
};


/**
 * struct, which store id and functor
 */
struct IdTOfunction{
	int id;
	//int type;
	int timer_id;
	struct timeval struct_time;
	int duration_ms;
	Functionpointer funcp;
};

#endif /* TIMER_H_ */
