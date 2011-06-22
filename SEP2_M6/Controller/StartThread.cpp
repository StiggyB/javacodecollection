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

#include "StartThread.h"

StartThread::StartThread(){
	halCore = HALCore::getInstance();
	interruptController = InterruptController::getInstance();
	communicationServer = CommunicationServer::getInstance();
	lampen = Lampen::getInstance();
	timer = Timer::getInstance();
	sensor = Sensor::getInstance();
	serial = Serial::getInstance();
}

StartThread::~StartThread() {

}

void StartThread::execute(void*) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}

	cout << "Starting Instances..." << endl;
	halCore->start(NULL);
	cout << "halCore started" << endl;
	communicationServer->start(NULL);
	cout << "communicationServer started" << endl;
	interruptController->start(NULL);
	cout << "interruptController started" <<endl;

	lampen->start(NULL);
	cout << "lampen started" << endl;
	timer->start(NULL);
	cout << "timer started" << endl;
	sensor->start(NULL);
	cout << "sensor started" << endl;
	serial->init(1, true);
	serial->start(NULL);
	cout << "serial started" << endl;

#ifdef TEST_IRQ
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
	sensor->ts = &ts;
	ts.start(NULL);
	cout << "waiting for Sensor-Tests" << endl;
	ts.join();
#endif
#ifdef TEST_FSM
	cout << "starting FSM-Tests" << endl;
	tests_fsm.init_tests();
	sensor->tests_fsm = &tests_fsm;
	tests_fsm.start(NULL);
	cout << "waiting for FSM-Tests" << endl;
	tests_fsm.join();
#endif
#ifdef TEST_FUN
	cout << "starting Functor-Test"	 << endl;
	cout << "waiting for Functor-Test" << endl;
	tf.start(NULL);
	tf.join();
#endif
#ifdef TEST_TIMER
	cout << "starting Timer-Test"	 << endl;
	timer_test.start(NULL);
	cout << "waiting for Timer-Test" << endl;
	timer_test.join();
#endif

//	sleep(40);
	halCore->join();
}

void StartThread::stopProcess() {
	//halCore->resetAllOutPut();
	//halCore->deleteInstance();
	//interruptController->deleteInstance();
}

void StartThread::shutdown(){
	serial->deleteInstance();
	sensor->deleteInstance();
	lampen->deleteInstance();
	communicationServer->deleteInstance();
	interruptController->deleteInstance();
	halCore->resetAllOutPut();
	halCore->deleteInstance();
}
