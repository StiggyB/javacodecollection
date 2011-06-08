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
//#include "../HAL/HALCore.h"
//#include "../FSM/Puck_FSM.h"
//#include "../FSM/Puck_FSM_1.h"
#include "../Thread/Mutex.h"
#include "../Thread/Singleton_T.h"
#include "../Thread/HAWThread.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "../Functor/CallInterface.h"
#include "../Functor/CallBackThrower.h"

#include "errno.h"
#include <vector>
#include <sys/time.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>


/**
 * Pulse code enum
 */
enum Pulse_code_timer {
	PUCK_FSM, HALCORE
};
enum timer_section {
	BEGIN_TO_HEIGH_MEASURE, HEIGH_MEASURE_TO_METAL_MEASURE, METAL_MEASURE_TO_SLIDE,
	METAL_MEASURE_TO_END, SWITCH_FORWARD_TIME
};

//template <typename T, typename R>
class Timer : public thread::HAWThread, public Communication, public Singleton_T<Timer>{
	friend class Singleton_T<Timer>;
public:
	Timer();
	virtual ~Timer();
	/**
	 * adds a functor to internal list and activate Timer
	 * \param funcp functor, the function of a Pck_FSM, which will be execute after timer timeout
	 * \param timer time im milliseconds, after this time the given function will be executed
	 * \return a bool, true if action was successful, false if not.
	 */
	//bool addTimerFunction( CallInterface<Puck_FSM_1, void>* funcp, int timer );//CallInterface<Puck_FSM, void, void*>*
	/**
	 * adds a functor to internal list and activate Timer
	 * \param funcp functor, the function of HALCore, which will be execute after timer timeout
	 * \param timer time im milliseconds, after this time the given function will be executed
	 * \return a bool, true if action was successful, false if not.
	 */
	//bool addTimerFunction( CallInterface<HALCore, void>* funcp, int timer );
	bool addTimerFunction( CallInterface<CallBackThrower, void>* funcp, int ms);
//	int addFunction_staticTimer(timer_section timer, CallInterface<HALCore, void>* funcp);
//	int addFunction_staticTimer(timer_section timer, CallInterface<Puck_FSM, void>* funcp);
	int startAllTimer();
	int stopAll_actual_Timer();

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
	std::vector< struct TimerData> timer_list;
	int initTimer_list();
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
	bool addTimerFunction(struct IdTOfunction new_element, int ms);
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

	long getSystemTime_ms();
};

/**
 * struct to avoid double code and optional to expand functionality
 */
union Functionpointer{
	//CallInterface<Puck_FSM_1, void>* funcp_fsm;
	//CallInterface<HALCore, void>* funcp_hal;
	CallInterface<CallBackThrower,void> * funcp_cbt;
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

struct TimerData{
	timer_t	timerid;
	struct itimerspec timer;
	struct sigevent event;
};


#endif /* TIMER_H_ */
