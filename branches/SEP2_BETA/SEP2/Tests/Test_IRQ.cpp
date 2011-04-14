/**
 * Testing Class for IRQ
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
#include "Test_IRQ.h"

/**
 * pointer to the CoreController
 */

Test_IRQ::Test_IRQ() {
	/**
	 * gaining IO privileges
	 */
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	/**
	 * gets a pointer to an instance of the CoreController
	 */
	cc = CoreController::getInstance();
}

Test_IRQ::~Test_IRQ() {

}

void Test_IRQ::execute(void*){

}

void Test_IRQ::shutdown(){

}
