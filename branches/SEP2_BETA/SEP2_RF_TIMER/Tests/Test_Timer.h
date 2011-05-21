/*
 * Test_Timer.h
 *
 *  Created on: 20.05.2011
 *      Author: User
 */

#ifndef TEST_TIMER_H_
#define TEST_TIMER_H_


#include "../Thread/HAWThread.h"
#include "../Timer/Timer.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include <sys/time.h>


class Test_Timer  : public thread::HAWThread{
public:
	Test_Timer();
	virtual ~Test_Timer();
	Timer *timer;
	void setTimer(Timer *t){ timer = t;}
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* TEST_TIMER_H_ */
