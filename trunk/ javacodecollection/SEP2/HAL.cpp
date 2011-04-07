/*
 * HAL.cpp
 *
 *  Created on: 31.03.2011
 *      Author: Administrator
 */

#include "HAL.h"

HAL::HAL() {
	// TODO Auto-generated constructor stub
	controlBits = BIT_CNTRLS;
}

HAL::~HAL() {
	// TODO Auto-generated destructor stub
}


int HAL::setPortToInput(int bits){
	out8(PORT_CNTRL,controlBits | bits);
	return 1;
}

int HAL::setPortToOutput(int bits){
	out8(PORT_CNTRL, controlBits  & (~bits));
	return 1;
}

bool HAL::isInput(int dir){
	return !isOutput(dir);
}

bool HAL::isOutput(int dir){
	return (controlBits & dir);
}

void HAL::resetPortsDirection(){
	out8(PORT_CNTRL,BIT_CNTRLS);
}

void HAL::setPortsTo(int cb){
	out8(PORT_CNTRL,cb);
}

void HAL::write(int dir, int value){
	int cb = controlBits;
	bool reset = !isOutput(dir);
	if(reset){ setPortToOutput(dir); }
	//checkVal(value);
	out8(dir,value);
	if(reset){ setPortToInput(dir); }
	setPortsTo(cb);
}

int HAL::read(int dir){
	int cb = controlBits;
	bool reset = !isInput(dir);
	int bits = getBitsToAdress(dir);
	if(reset){ setPortToInput(bits); }
	int l = in8(dir);
	if(reset){ setPortToInput(bits); }
	setPortsTo(cb);
	return l;
}

int HAL::getBitsToAdress(int dir){
	int bits = 0x00;
	switch (dir) {
		case PORT_A: bits = BIT_PORT_A; break;
		case PORT_B: bits = BIT_PORT_B; break;
		case PORT_C: bits = BIT_PORT_C; break;
		default: bits = 0x00; break;
	}
	return bits;
}

/*void HAL::checkVal(value){
	if (value == BIT_ENGINE_RIGHT || value == BIT_ENGINE_LEFT || value == BIT_ENGINE_SLOW){
		int in = read(PORT_A);
		if (value == BIT_ENGINE_RIGHT) {
			if(in & BIT_ENGINE_LEFT){

			}
		}
		if (value == BIT_ENGINE_LEFT) {
			if(in & BIT_ENGINE_LEFT){

						}
		}
		if (value == BIT_ENGINE_SLOW) {
			if(in & BIT_ENGINE_LEFT){

						}
		}

	}
}
*/
