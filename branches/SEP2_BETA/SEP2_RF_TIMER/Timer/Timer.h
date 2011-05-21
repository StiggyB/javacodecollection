/*
 * Timer.h
 *
 *  Created on: 19.05.2011
 *      Author: user
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "../Functor/CallInterface.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "Communication.h"
#include "../Thread/HAWThread.h"
#include "../FSM/Puck_FSM.h"
#include "../Tests/Test_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include "../Tests/Test_Functions.h"
#include "../HAL/HALCore.h"
#include <vector>
#include <algorithm>

class Timer : public thread::HAWThread, public Communication{
public:
	Timer();
	virtual ~Timer();
	bool addTimerFunction( CallInterface<Puck_FSM, void, void*>* funcp, int timer );//CallInterface<Puck_FSM, void, void*>*
	bool addTimerFunction( CallInterface<HALCore, void, void*>* funcp, int timer );
protected:
	virtual void execute(void*);
	virtual void shutdown();
	virtual void handlePulsMessage();
	virtual void handleNormalMessage();
	void clean();
	CommunicatorType receiver;
private:
	std::vector< struct idTOfunction > funcp_list;
	CallInterface<Puck_FSM, void, void*>* test_funcp;
	struct idTOfunction find_function(int id);
	int id_index;
};

struct idTOfunction{
	int id;
	CallInterface<Puck_FSM, void, void*>* funcp;
};

#endif /* TIMER_H_ */
