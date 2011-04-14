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
}

Test_Serial::~Test_Serial() {

}

void Test_Serial::execute(void*){
	//s_0.init(1,0,true);
	s_1.init(1,0,true);
	//s_0.start(NULL);
	s_1.start(NULL);
	//sleep(25);
	//s_0.stop();
	//s_1.stop();
}

void Test_Serial::shutdown(){
	//s_0.~Serial();
	s_1.~Serial();
}
