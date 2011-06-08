
#ifndef STARTTHREAD_H_
#define STARTTHREAD_H_

#include <stdlib.h>
#include "Sensor.h"
#include "InterruptController.h"
#include "CommunicationServer.h"
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "../Timer/Timer.h"
#include "../Tests/test.h"
#include "../Tests/Test_M1.h"
#include "../Tests/Test_HAL.h"
#include "../Tests/Test_IRQ.h"
#include "../Tests/Test_Serial.h"
#include "../Tests/Test_Lights.h"
#include "../Tests/Test_Functor.h"
#include "../Tests/Test_Timer.h"

/**
 * StartThread
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Starts all components for the System.
 *
 */
class StartThread : public thread::HAWThread {
public:
	StartThread();
	virtual ~StartThread();
	void stopProcess();
protected:
    virtual void execute(void*);
    virtual void shutdown();
private:
    /**
     * pointer to the HAL
     */
    HALCore *halCore;
    /**
     * pointer to the InterruptController
     */
    InterruptController *interruptController;

    /**
     * pointer to the CommunicationServer
     */
    CommunicationServer *communicationServer;
    /**
     * pointer to the Lampen
     */
    Lampen * lampen;
    /**
     * pointer to the serial controller
     */
    Serial * serial;
    /**
	 * pointer to the sensor controller
	 */
	Sensor * sensor;
	/**
	 * pointer to the timer instance
	 */
	Timer* timer;
#ifdef TEST_M1
	/**
	 * Test for Milestone 1
	 */
	Test_M1 tm;
#endif
#ifdef TEST_HAL
	/**
	 * Test for HAL
	 */
	Test_HAL th;
#endif
#ifdef TEST_IRQ
	/**
	 * Test for IRQs
	 */
	Test_IRQ ti;
#endif
#ifdef TEST_SER
	/**
	 * Test for Serial Interface
	 */
	Test_Serial ser;
#endif
#ifdef TEST_LIGHT
	/**
	 * Test for Lights
	 */
	Test_Lights tl;
#endif
#ifdef TEST_SEN
	/**
	 * Test for Sensorik
	 */
	Test_Sensor ts;
#endif
#ifdef TEST_FSM
	/**
	 * Test for FSMs
	 */
	Test_FSM tests_fsm;
#endif
#ifdef TEST_FUN
	/**
	 * Test for Functor
	 */
	Test_Functor tf;
#endif
#ifdef TEST_TIMER
	/**
	 * Test for Timer
	 */
	Test_Timer timer_test;
#endif

};

#endif /* STARTTHREAD_H_ */
