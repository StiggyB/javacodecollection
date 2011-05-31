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
#include "../HAL/HALCore.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "../Functor/CallInterface.h"
#include "errno.h"
#include <vector>

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

class Timer : public thread::HAWThread, public Communication{
public:
	Timer();
	virtual ~Timer();
	/**
	 * adds a functor to internal list and activate Timer
	 * \param funcp functor, the function of a Pck_FSM, which will be execute after timer timeout
	 * \param timer time im milliseconds, after this time the given function will be executed
	 * \return a bool, true if action was successful, false if not.
	 */
	bool addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int timer );//CallInterface<Puck_FSM, void, void*>*
	/**
	 * adds a functor to internal list and activate Timer
	 * \param funcp functor, the function of HALCore, which will be execute after timer timeout
	 * \param timer time im milliseconds, after this time the given function will be executed
	 * \return a bool, true if action was successful, false if not.
	 */
	bool addTimerFunction( CallInterface<HALCore, void, void*>* funcp, int timer );
	int addFunction_staticTimer(timer_section timer, CallInterface<HALCore, void, void*>* funcp);
	int addFunction_staticTimer(timer_section timer, CallInterface<Puck_FSM, void, void*>* funcp);
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
};

/**
 * struct to avoid double code and optional to expand functionality
 */
union Functionpointer{
	CallInterface<Puck_FSM, void, void*>* funcp_fsm;
	CallInterface<HALCore, void, void*>* funcp_hal;
};

/**
 * struct, which store id and functor
 */
struct IdTOfunction{
	int id;
	int type;
	int timer_id;
	Functionpointer funcp;
};

struct TimerData{
	timer_t	timerid;
	struct itimerspec timer;
	struct sigevent event;
};


#endif /* TIMER_H_ */
