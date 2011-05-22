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

#include "../Functor/CallInterface.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "Communication.h"
#include "../Thread/HAWThread.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../HAL/HALCore.h"
#include <vector>

enum Pulse_code_timer {
	PUCK_FSM=(0), HALCORE=(1)
};

class Timer : public thread::HAWThread, public Communication{
public:
	Timer();
	virtual ~Timer();
	bool addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int timer );//CallInterface<Puck_FSM, void, void*>*
	bool addTimerFunction( CallInterface<HALCore, void, void*>* funcp, int timer );
	void testTimer();
protected:
	virtual void execute(void*);
	virtual void shutdown();
	virtual void handlePulsMessage();
	virtual void handleNormalMessage();
	CommunicatorType receiver;
private:
	std::vector< struct idTOfunction> funcp_list_fsm;
	CallInterface<Puck_FSM, void, void*>* test_funcp;
	struct idTOfunction find_function(unsigned int id);
	bool addTimerFunction(struct idTOfunction new_element, int ms);
	int calculateTime(int ms, int *s, int *ns);
	int getnextid();
};

union Functionpointer{
	CallInterface<Puck_FSM, void, void*>* funcp_fsm;
	CallInterface<HALCore, void, void*>* funcp_hal;
};

struct idTOfunction{
	int id;
	int type;
	Functionpointer funcp;
};




#endif /* TIMER_H_ */
