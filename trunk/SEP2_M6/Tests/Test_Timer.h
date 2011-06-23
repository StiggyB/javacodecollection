
#ifndef TEST_TIMER_H_
#define TEST_TIMER_H_

#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "../Timer/Timer.h"
#include "../HAL/HALCore.h"
#include "../Thread/HAWThread.h"
#include "../Functor/CallBackThrower.h"

/**
 * Test_Timer
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
 *this class will test the functions from Timer.h
 *
 *
 */
class Test_Timer  : public thread::HAWThread{
public:
	Test_Timer();
	virtual ~Test_Timer();
	/**
	 * Timer object, which will tested
	 */
	Timer *timer;
	/**
	 * set the timer object, this object was started from another thread
	 * \param t the Timer object
	 */
	void setTimer(Timer *t){ timer = t;}

protected:
	/**
	 * set the timer object, this object was started from another thread
	 * \param data optional data, which the thread can process
	 */
	virtual void execute(void* data);
	virtual void shutdown();
};

#endif /* TEST_TIMER_H_ */
