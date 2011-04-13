/*
 * StartThread.cpp
 *
 *  Created on: 13.04.2011
 *      Author: Administrator
 */

#include "StartThread.h"

StartThread::StartThread(){
	cc = CoreController::getInstance();
	ic = InterruptController();
#ifdef TEST_M1
	tm = Test_M1();
#endif
#ifdef TEST_IRQ
	ti = Test_IRQ();
#endif
#ifdef TEST_HAL
	th = Test_HAL();
#endif
#ifdef TEST_SER
	ser = Test_Serial();
#endif
}

StartThread::~StartThread() {

}

void StartThread::execute(void*) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	//InterruptController ic;
	ic.start(NULL);

#ifdef TEST_IRQ
	ti.start(NULL);
#endif

#ifdef TEST_HAL
	cout << "starting HAL-Tests" << endl;
	th.start(NULL);
	cout << "waiting for HAL-Tests" << endl;
	th.join();
#endif

#ifdef TEST_M1
	cout << "starting M1-Tests" << endl;
	tm.start(NULL);
	cout << "waiting for M1-Tests" << endl;
	tm.join();
#endif

#ifdef TEST_SER
	cout << "starting SERIAL-Tests" << endl;
	ser.start(NULL);
	cout << "waiting for SERIAL-Tests" << endl;
	ser.join();
#endif

	ic.join();
}

void StartThread::stopProcess() {
	(*cc).resetAllOutPut();
}

void StartThread::shutdown(){

}
