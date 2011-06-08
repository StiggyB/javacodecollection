/*
 * StartThread.cpp
 *
 *  Created on: 13.04.2011
 *      Author: Administrator
 */

#include "StartThread.h"
#include "../Timer/Timer.h"

StartThread::StartThread(){
	halCore = HALCore::getInstance();
	interruptController = InterruptController::getInstance();
	communicationserver = CommunicationServer::getInstance();
	lampen = Lampen::getInstance();
}

StartThread::~StartThread() {

}

void StartThread::execute(void*) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}

	communicationserver->start(NULL);
	halCore->start(NULL);

	cout << "starting IC" <<endl;
	interruptController->start(NULL);
	cout << "IC started" <<endl;

	//lampen->start(NULL);


	timer = Timer::getInstance();
	//timer->startInstance();

	Serial serial;
	Sensor sensor;
	sensor.serial = &serial;

	sensor.start(NULL);
	cout << "sensor started" << endl;




#ifdef TEST_IRQ
	Test_IRQ ti;
	ti.start(NULL);
#endif

#ifdef TEST_SER
	cout << "starting SERIAL-Tests" << endl;
	ser.start(NULL);
	cout << "waiting for SERIAL-Tests" << endl;
	ser.join();
	cout << "SERIAL-Tests ended" << endl;
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

#ifdef TEST_LIGHT
	cout << "starting Light-Tests" << endl;
	tl.start(NULL);
	cout << "waiting for Light-Tests" << endl;
	tl.join();
#endif
#ifdef TEST_SEN
	cout << "starting Sensor-Tests" << endl;
	ts.start(NULL);
	cout << "waiting for Sensor-Tests" << endl;
	ts.join();
#endif
#ifdef TEST_FSM
	cout << "starting FSM-Tests" << endl;
	tests_fsm.init_tests();
	tests_fsm.serial = &serial;
	sensor.testFSM(&tests_fsm);
	tests_fsm.start(NULL);
	cout << "waiting for FSM-Tests" << endl;
	//tests_fsm.join();
#endif
#ifdef TEST_FUN
	cout << "starting Functor-Test"	 << endl;
	tf.start(NULL);
	cout << "waiting for Functor-Test" << endl;
	tf.join();
#endif
#ifdef TEST_TIMER
	cout << "starting Timer-Test"	 << endl;
	//timer_test.serial = &serial;

	timer_test.start(NULL);
	cout << "waiting for Timer-Test" << endl;
	timer_test.join();
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
//	sleep(40);
	sensor.join();
	//h->join();

}

void StartThread::stopProcess() {
	//h->resetAllOutPut();
	//h->deleteInstance();
	//ic->deleteInstance();
}

void StartThread::shutdown(){
	lampen->deleteInstance();
	communicationserver->deleteInstance();
	interruptController->deleteInstance();
	halCore->resetAllOutPut();
	halCore->deleteInstance();
}
