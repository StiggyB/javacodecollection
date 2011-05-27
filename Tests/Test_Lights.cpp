/*
 * Test_Lights.cpp
 *
 *  Created on: 17.05.2011
 *      Author: aax691
 */

#include "Test_Lights.h"

Test_Lights::Test_Lights() {
	/**
	 * gaining IO privileges
	 */
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	/**
	 * gets a pointer to an instance of the CoreController
	 */
	h = HALCore::getInstance();
	/**
	 * gets a pointer to an instance of Lampen
	 */
	l = Lampen::getInstance();
}

Test_Lights::~Test_Lights() {

}

void Test_Lights::execute(void*){
	int time = 2000;
	cout << "starting Lights" << endl;
	cout << "aL RED" << endl;
	l->addLight(RED);
	delay(time);
	cout << "aL GREEN" << endl;
	l->addLight(GREEN);
	delay(time);
	cout << "aL YELLOW" << endl;
	l->addLight(YELLOW);
	delay(time);
	l->removeLight(RED);
	l->flash(500,8000,RED);
	delay(time);
	l->removeLight(GREEN);
	l->flash(500,GREEN);
	delay(time);
	l->removeLight(YELLOW);
	l->flash(500,YELLOW);
	delay(4*time);
	l->shine(RED);
	delay(time);
	l->shine(GREEN);
	delay(time);
	l->shine(YELLOW);
	delay(time);
	l->removeLight(YELLOW);
	delay(time);
}

void Test_Lights::shutdown(){

}
