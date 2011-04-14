
#ifndef STARTTHREAD_H_
#define STARTTHREAD_H_

//#include "../Lampen/Lampen.h"
#include "../Tests/test.h"
#include "../Tests/Test_M1.h"
#include "../Tests/Test_HAL.h"
#include "../Tests/Test_IRQ.h"
#include "../Tests/Test_Serial.h"
#include "CoreController.h"
#include "InterruptController.h"

class StartThread : public thread::HAWThread {
public:
	StartThread();
	virtual ~StartThread();
	void stopProcess();
protected:
    virtual void execute(void*);
    virtual void shutdown();
private:
    CoreController *cc;
    InterruptController ic;
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
};

#endif /* STARTTHREAD_H_ */
