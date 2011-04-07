/*
 * HW_test.cpp
 *
 *  Created on: 30.03.2011
 *      Author: Administrator
 */

#include "HW_test.h"
#include "HWaccess.h"
#include "Lampen.h"

HW_test::HW_test() {
	// TODO Auto-generated constructor stub
	h = HAL();
}

HW_test::~HW_test() {
	// TODO Auto-generated destructor stub
}

/*void HW_test::start(){
	thread::HAWThread::start();
}*/

void HW_test::execute(void*){
	cout << "|Hardwaretest aktiv" << endl;
	//---------------aktoren testen
	sleep(5);

	//lampen testen
	cout << "|-->Lampentest" << endl;
	for(int i = 0; i < 3; i++){
		h.write(PORT_A, BIT_LIGHT_GREEN);
		sleep(1);
		h.write(PORT_A, BIT_LIGHT_YELLOW);
		sleep(1);
		h.write(PORT_A, BIT_LIGHT_RED);
		sleep(1);
	}//for
	h.write(PORT_A, BIT_ENGINE_STOP);//zurücksetzen

	//Bandtest
	cout << "|-->Bandtest rechts" << endl;
	for(int i = 0; i < 3; i++){
		h.write(PORT_A, BIT_ENGINE_RIGHT);
		sleep(1);
		h.write(PORT_A, BIT_ENGINE_S_R);
		sleep(1);
	}//for
	h.write(PORT_A, BIT_ENGINE_STOP);//zurücksetzen

	cout << "|-->Bandtest links" << endl;
	for(int i = 0; i < 3; i++){
		h.write(PORT_A, BIT_ENGINE_LEFT);
		sleep(1);
		h.write(PORT_A, BIT_ENGINE_S_L);
		sleep(1);
	}//for
	h.write(PORT_A, BIT_LIGHT_OFF);//zurücksetzen

	//weiche testen
	cout << "|-->Weichentest" << endl;
	for(int i = 0; i < 1; i++){
		//weiche testen
		sleep(1);
		h.write(PORT_A, BIT_SWITCH);
		sleep(1);
		h.write(PORT_A, BIT_LIGHT_OFF);
	}//for
	h.write(PORT_A, BIT_LIGHT_OFF);//zurücksetzen

	//vier leuchten am Bedienteil
	cout << "|-->Bedienleuchtentest" << endl;
	for(int i = 0; i < 3; i++){
		sleep(1);
		h.write(PORT_C, BIT_LED_START);
		sleep(1);
		h.write(PORT_C, BIT_LED_RESET);
		sleep(1);
		h.write(PORT_C, BIT_LED_Q1);
		sleep(1);
		h.write(PORT_C, BIT_LED_Q2);
		sleep(1);
		h.write(PORT_C, BIT_LIGHT_OFF);
	}//for
	h.write(PORT_C, BIT_LIGHT_OFF);

	cout << "|-->Hardwaretest fertig!" << endl;
}

void HW_test::shutdown(){

}
