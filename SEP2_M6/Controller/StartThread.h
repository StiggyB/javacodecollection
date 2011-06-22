
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
 * Functor Pattern.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * This class starts all threads for the normal running.
 * Various defines include and start different tests.
 *
 */

class StartThread : public thread::HAWThread {
public:
	StartThread();
	virtual ~StartThread();
	/**
	 * This function deletes and stops some threads.
	 */
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
     * pointer to the lights
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
     * Instance from the Test_M1
     */
    Test_M1 tm;
#endif
#ifdef TEST_HAL
    /**
     * Instance from the Test_HAL
     */
    Test_HAL th;
#endif
#ifdef TEST_IRQ
    /**
     * Instance from the Test_IRQ
     */
    Test_IRQ ti;
#endif
#ifdef TEST_SER
    /**
     * Instance from the Test_Serial
     */
    Test_Serial ser;
#endif
#ifdef TEST_LIGHT
    /**
     * Instance from the timer instance
     */
	Test_Lights tl;
#endif
#ifdef TEST_SEN
    /**
     * Instance from the Test_Sensor
     */
	Test_Sensor ts;
#endif
#ifdef TEST_FSM
    /**
     * Instance from the Test_FSM
     */
    Test_FSM tests_fsm;
#endif
#ifdef TEST_FUN
    /**
     * Instance from the Test_Functor
     */
    Test_Functor tf;
#endif
#ifdef TEST_TIMER
    /**
     * Instance from the Test_Timer
     */
    Test_Timer timer_test;
#endif

};

#endif /* STARTTHREAD_H_ */
