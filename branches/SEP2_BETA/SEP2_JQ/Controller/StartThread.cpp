/*
 * StartThread.cpp
 *
 *  Created on: 13.04.2011
 *      Author: Administrator
 */

#include "StartThread.h"

StartThread::StartThread(){
	h = HALCore::getInstance();
	ic = InterruptController::getInstance();
	cs = CommunicationServer::getInstance();
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
	//ser = Test_Serial();
#endif
}

StartThread::~StartThread() {

}

void StartThread::execute(void*) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	cs->start(NULL);
	h->start(NULL);
	cout << "starting IC" <<endl;
	ic->start(NULL);
	cout << "IC started" <<endl;
	Sensor s;
	s.start(NULL);
#ifdef TEST_IRQ
	Test_IRQ ti;
	ti.start(NULL);
#endif

#ifdef TEST_SER
	cout << "starting SERIAL-Tests" << endl;
	Serial ser;
	ser.init(1,1,true);
	ser.start(NULL);
	cout << "waiting for SERIAL-Tests" << endl;
	//ser.join();
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
/*
	sleep(4);
	int coid = ConnectAttach(0, 0, Communication::serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("InterruptController: failed to attach Channel for Interrupt\n");
	}else{
		short otto = 0;
		short peter = 0;
		while(1){
			//struct _pulse puls;
			//SIGEV_PULSE_INIT(&puls,coid,SIGEV_PULSE_PRIO_INHERIT,otto,peter);
			if(-1 == MsgSendPulse(coid,SIGEV_PULSE_PRIO_INHERIT,otto++,peter++)){
				perror("ST: failed to send puls!");
			}
		}
	}
*/
	sleep(40);
	//h->join();

}

void StartThread::stopProcess() {
	//h->resetAllOutPut();
	//h->deleteInstance();
	//ic->deleteInstance();
}

void StartThread::shutdown(){

}
