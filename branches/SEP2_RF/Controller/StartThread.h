
#ifndef STARTTHREAD_H_
#define STARTTHREAD_H_

#include <stdlib.h>
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "../Tests/test.h"
#include "../Tests/Test_M1.h"
#include "../Tests/Test_HAL.h"
#include "../Tests/Test_IRQ.h"
#include "../Tests/Test_Serial.h"
#include "../Tests/Test_Lights.h"
#include "../Tests/Test_Functor.h"
#include "Sensor.h"
#include "InterruptController.h"
#include "CommunicationServer.h"
#include "../Tests/Test_Timer.h"
#include "../Timer/Timer.h"

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
    HALCore *h;
    /**
     * pointer to the InterruptController
     */
    InterruptController *ic;

    /**
     * pointer to the CommunicationServer
     */
    CommunicationServer *cs;
    /**
     * pointer to the Lampen
     */
    Lampen * l;
#ifdef TEST_M1
    Test_M1 tm;
#endif
#ifdef TEST_HAL
    Test_HAL th;
#endif
#ifdef TEST_IRQ
    Test_IRQ ti;
#endif
#ifdef TEST_SER
    Test_Serial ser;
#endif
#ifdef TEST_LIGHT
	Test_Lights tl;
#endif
#ifdef TEST_SEN
	Test_Sensor ts;
#endif
#ifdef TEST_FSM
    Test_FSM tests_fsm;
#endif
#ifdef TEST_FUN
    Test_Functor tf;
#endif
#ifdef TEST_TIMER
    Test_Timer timer_test;
    Timer timer;
#endif

};

#endif /* STARTTHREAD_H_ */
