/**
 * Testing Class for Serial
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Prepares some Testing stuff for the Interrupts.
 *
 * Inherits: thread::HAWThread
 */
#include "Test_Serial.h"

Test_Serial::Test_Serial() {
	s_0 = new Serial();
	s_1 = new Serial();
}

Test_Serial::~Test_Serial() {
	s_0->~Serial();
	s_1->~Serial();
	delete s_0;
	delete s_1;
}

void Test_Serial::execute(void*){
	int msg_test = 0;
	bool test_successful = true;
	s_0->init(1,true);
	s_1->init(2,true);

	s_0->start(NULL);
	s_1->start(NULL);
	sleep(10);
	if(s_0->send(&msg_test, sizeof(msg_test))== 0){printf("s_0 message 1 gesendet \n") ;}else{printf("s_0 message 1 not cool \n");test_successful = false;}
	sleep(5);
	printf("sleep5 done\n") ;
	if(s_1->send(&msg_test, sizeof(msg_test))== 0){printf("s_1 message 1 gesendet\n") ;}else{test_successful = false;}
	sleep(2);
	msg_test = 1;
	if(s_0->send(&msg_test, sizeof(msg_test))== 0){printf("s_0 message 2 gesendet\n") ;}else{test_successful = false;}
	if(s_1->send(&msg_test, sizeof(msg_test))== 0){printf("s_1 message 2 gesendet\n");}else{test_successful = false;}
	sleep(2);
	msg_test = 2;
	if(s_0->send(&msg_test, sizeof(msg_test))== 0){printf("s_0 message 3 gesendet\n") ;}else{test_successful = false;}
	if(s_1->send(&msg_test, sizeof(msg_test))== 0){printf("s_1 message 3 gesendet\n");}else{test_successful = false;}
	//s_0.stop();
	//s_1.stop();
	printf("Test bestanden: %i\n",test_successful);
	sleep(600);
}

void Test_Serial::shutdown(){
	s_0->~Serial();
	s_1->~Serial();
}
