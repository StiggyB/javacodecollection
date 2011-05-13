/*
 * Error_State_Lamp.cpp
 *
 *  Created on: 12.05.2011
 *      Author: user
 */

#include "Error_State_Lamp.h"
#include "iostream.h"


Error_State_Lamp::Error_State_Lamp() {
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
			std::cout << "Error_State_Lamp: Error for IO Control" << std::endl;
	}
	cc = CoreController::getInstance();
	time = 500000;
}

Error_State_Lamp::~Error_State_Lamp() {
	// TODO Auto-generated destructor stub
}

void Error_State_Lamp::execute(void* data){
	while(!isStopped()){
		(*cc).shine(RED);
		usleep(time);
		(*cc).removeLight(RED);
		usleep(time);
	}
}

void Error_State_Lamp::shutdown(){

}

void Error_State_Lamp::fast_blink(){
	time = 500000;
}

void Error_State_Lamp::slow_blink(){
	time = 1000000;
}
