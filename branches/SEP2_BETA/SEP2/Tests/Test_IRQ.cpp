/*
 * Test_IRQ.cpp
 *
 *  Created on: 12.04.2011
 *      Author: Administrator
 */

#include "Test_IRQ.h"

extern CoreController* cc;

Test_IRQ::Test_IRQ() {
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if(cc == NULL) cc = CoreController::getInstance();
}

Test_IRQ::~Test_IRQ() {

}

void Test_IRQ::execute(void*){
	(*cc).engineReset();
	(*cc).engineRight();
}

void Test_IRQ::shutdown(){

}
