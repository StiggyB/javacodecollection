/*
 * HAL.cpp
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#include "HAL.h"

const struct sigevent * ISR(void *arg, int id);
volatile int portA;
volatile int portB;
volatile int portC;
volatile int portIRE;
volatile int portIRQ;
volatile int controlBits;

HAL* HAL::instance = NULL;
Mutex HAL::mutEx;

HAL* HAL::getInstance(){

	if( !instance){
		mutEx.lock();
		if(!instance){
			instance = new HAL;
		}
		mutEx.unlock();
	}
	return instance;
}

HAL::HAL() {
	controlBits = BIT_CNTRLS;
	portA = read(PORT_A);
		portB = read(PORT_B);
		portC = read(PORT_C);
		portIRE = read(PORT_IRE);
		portIRQ = read(PORT_IRQ);
}

HAL::~HAL() {
	mutEx.~Mutex();
}

int HAL::setPortToInput(int bits){
	controlBits = controlBits | bits;
	out8(PORT_CNTRL,controlBits);
	return 1;
}

int HAL::setPortToOutput(int bits){
	controlBits = controlBits  & (~bits);
	out8(PORT_CNTRL, controlBits);
	return 1;
}


bool HAL::isInput(int dir){
	return !isOutput(dir);
}

bool HAL::isOutput(int dir){
	switch(dir){
	case PORT_A:dir = BIT_PORT_A;break;
	case PORT_B:dir = BIT_PORT_B;break;
	case PORT_C:dir = BIT_PORT_C;break;
	default:break;
	}
	return (controlBits & dir);
}

bool HAL::isOutput2(int dir){
	return !isInput2(dir);
}

bool HAL::isInput2(int dir){
	switch(dir){
	case PORT_A:dir = BIT_PORT_A; break;
	case PORT_B:dir = BIT_PORT_B; break;
	case PORT_C:dir = BIT_PORT_C; break;
	default: dir = 0x00; break;
	}
	return (controlBits & dir);
}


void HAL::resetPortsDirection(){
	out8(PORT_CNTRL,BIT_CNTRLS);
}

void HAL::setPortsTo(int cb){
	out8(PORT_CNTRL,cb);
}

int HAL::write(int dir, int value, bool set){
	//if(!set) std::cout<< "Write: port: "<< std::hex <<dir << " StartVal="<< std::hex<< value << " set?" << set <<std::endl;
	int val = getBitsToAdress(dir);
	bool reset = false;
	// if(!isOutput(dir)){ setPortToOutput(dir); reset = true }
	if((controlBits & val ) != 0){
		setPortToOutput(dir);
		reset = true;
	}
	//if(!set) std::cout<< "Write: reset: "<< reset << " controlBits: " << controlBits << " val:" << std::hex << val  <<std::endl;
	value = checkVal(dir,value, set);
	int volatile *port = 0;
	switch(dir){
		case PORT_B: port = &portB;/* val = portB & value;*/ break;
		case PORT_C: port = &portC;/* val = portC & value;*/ break;
		case PORT_CNTRL: port = &controlBits;/* val = controlBits & value;*/ break;
		case INTERRUPT_SET_ADRESS: port = &portIRE;/* val = portIRE & value;*/ break;
		case INTERRUPT_RESET_ADRESS: port = &portIRQ;/* val = portIRQ & value;*/ break;
		default: port = &portA;/* val = portA & value;*/ break; //PORT_A
	}
	val = value;
	int newVal = 0;
	for (int i = 0; i < 8; i++) {
		int tmp = ((value & (1 << i)) >> i);
		int zahl = (((*port) & (1 << i)) >> i);
		//if(!set) std::cout<< "Write: tmp: "<< std::hex <<tmp << " zahl="<< std::hex<< zahl <<std::endl;
		if (tmp != 0) {
			if (set) {
				if (tmp == 1 && zahl == 0) {
					tmp = 1;
				}
			} else {
				tmp = 0;
			}
		} else {
			tmp = zahl;
		}
		//if(!set) std::cout<< "Write: newVal: "<< std::hex << newVal << " tmp="<< std::hex<< tmp ;
		newVal = newVal | (tmp << i);
		//if(!set) std::cout<< " newVal_newer: "<< std::hex << newVal <<std::endl;
	}
	*port = newVal;
	//if(!set) std::cout<< "Write: port: "<< std::hex <<dir << " val="<< std::hex<< *port  << " newVal="<<std::hex<<newVal<< std::endl;
	out8(dir,newVal);
	if(reset){ setPortToInput(dir); }
	return newVal;
}

int HAL::write(int dir, int value){
	return write(dir, value, true);
}

int HAL::reset(int dir, int value){
	return write(dir, value, false);
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

int HAL::getValueToAdress(int dir){
	int value = 0x00;
	switch (dir) {
		case PORT_CNTRL: value = controlBits; break;
		case PORT_B: value = portB; break;
		case PORT_C: value = portC; break;
		case PORT_IRE: value = portIRE;break;
		case PORT_IRQ: value = portIRQ;break;
		default: value = portA; break;
	}
	return value;
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

int HAL::checkVal(int dir, int value,bool set) {
	if (dir == PORT_A && set) {
		if ((value == BIT_ENGINE_RIGHT || value == BIT_ENGINE_S_R) && (portA & BIT_ENGINE_LEFT)) {
			reset(PORT_A,BIT_ENGINE_LEFT);
		} else if ((value == BIT_ENGINE_LEFT || value == BIT_ENGINE_S_L) && (portA & BIT_ENGINE_RIGHT)) {
			reset(PORT_A,BIT_ENGINE_RIGHT);
		}
	}
	return value;
}

bool HAL::engineStart(int direction) {
	bool ret = false;
	if (!engineStopped()) {
		if (direction == BIT_ENGINE_LEFT) {
			ret = reset(PORT_A,BIT_ENGINE_RIGHT);
			ret = ret && write(PORT_A,BIT_ENGINE_LEFT);
		} else if (direction == BIT_ENGINE_RIGHT) {
			ret = reset(PORT_A,BIT_ENGINE_LEFT);
			ret = ret && write(PORT_A,BIT_ENGINE_RIGHT);
		}

	}
	return ret;
}
bool HAL::openSwitch(){
	return setSwitchDirection(BIT_SET);
}
bool HAL::closeSwitch(){
	return setSwitchDirection(BIT_DELETE);
}
bool HAL::setSwitchDirection(bool dir){
	if(dir){
		return write(PORT_A,BIT_SWITCH);
	}else{
		return reset(PORT_A,BIT_SWITCH);
	}
}
bool HAL::engineReset(){
	bool ret = reset(PORT_A,BIT_ENGINE_RIGHT);
	ret = ret && reset(PORT_A,BIT_ENGINE_LEFT);
	return (ret && reset(PORT_A,BIT_ENGINE_SLOW));
}
bool HAL::engineStop(){
	return write(PORT_A,BIT_ENGINE_STOP);
}
bool HAL::engineContinue(){
	return reset(PORT_A,BIT_ENGINE_STOP);
}
bool HAL::engineRight(){
	return engineStart(BIT_ENGINE_RIGHT);
}
bool HAL::engineLeft(){
	return engineStart(BIT_ENGINE_LEFT);
}
bool HAL::engineSlowSpeed(){
	if(!engineStopped()){
		write(PORT_A, BIT_ENGINE_SLOW);
	}
	return false;
}
bool HAL::engineNormalSpeed(){
	if(!engineStopped()){
		return reset(PORT_A, BIT_ENGINE_SLOW);
	}
	return false;
}

bool HAL::engineStopped(){
	return (portA & BIT_ENGINE_STOP);
}

bool HAL::engineSlowSpeed(int dir) {
	if(!engineStopped()){
		if (BIT_ENGINE_LEFT || BIT_ENGINE_S_L) {
			reset(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_SLOW);
		} else if (BIT_ENGINE_RIGHT || BIT_ENGINE_S_R) {
			reset(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_SLOW);
		}else{
			write(PORT_A, BIT_ENGINE_SLOW);
		}
		return true;
	}
	return false;
}

bool HAL::engineSpeed(bool slow) {
	if(!engineStopped()){
		if (slow) {
			write(PORT_A, BIT_ENGINE_SLOW);
		} else{
			reset(PORT_A, BIT_ENGINE_SLOW);
		}
		return true;
	}
	return false;
}


bool HAL::engineSlowLeft(){
	return engineSlowSpeed(BIT_ENGINE_LEFT);
}
bool HAL::engineSlowRight(){
	return engineSlowSpeed(BIT_ENGINE_RIGHT);
}

bool HAL::resetAllOutPut(){
	return reset(PORT_A,0xFF);
}

bool HAL::addLight(Color col) {
	int old = getValueToAdress(PORT_A);
	old = old | getColorCode(col);
	return write(PORT_A, old);
}

bool HAL::removeLight(Color col) {
	int old = getColorCode(col);
	return reset(PORT_A, old);
}

bool HAL::shine(int color) {
	if (color == BIT_LIGHT_OFF) {
		return reset(PORT_A, BIT_LIGHTS_ON);
	} else {
		return write(PORT_A, color);
	}
}
int HAL::getColorCode(Color col) {
	int newColor = 0x00;
	switch (col) {
	case YELLOW:
		newColor = 0x40;
		break;
	case GREEN:
		newColor = 0x20;
		break;
	case RED:
		newColor = 0x80;
		break;
	default:
		newColor = 0x00;
		break;
	}
	return newColor;
}

bool HAL::shine(Color col) {
	bool ret = false;
	switch (col) {
	case YELLOW:
		ret=shine(BIT_LIGHT_YELLOW);
		break;
	case GREEN:
		ret=shine(BIT_LIGHT_GREEN);
		break;
	case OFF:
		ret=shine(BIT_LIGHT_OFF);
		break;
	default:
		ret=shine(BIT_LIGHT_RED);
		break;
	}
	return ret;
}

bool HAL::attachISR(void * arg){
	struct sigevent * event = (struct sigevent*) arg;
	int id = InterruptAttach(INTERRUPT_VECTOR_NUMMER,ISR,&event,sizeof(event),0);
	if(id == -1)std::cout << "HAL: AttachISR failed" << std::endl;
	return id;
}


const struct sigevent * ISR(void *arg, int id){
	int iir;
	//std::cout << "HAL_ISR: hallo ISR" << std::endl;
	struct sigevent *event = (struct sigevent*) arg;
	iir = in8(PORT_IRQ_AND_RESET) & IIR_MASK;
	//std::cout << "HAL_ISR: hallo ISR" << std::endl;
	if(iir & 1) return (NULL);
	switch(iir){
	case INTERRUPT_PORT_A: portA = in8(PORT_A); return (event);break;
	case INTERRUPT_PORT_B: portB = in8(PORT_B); return (event);break;
	case INTERRUPT_PORT_C: portC = in8(PORT_C); return (event);break;
	default: return (NULL);break;
	}
	return (NULL);
}


bool HAL::activateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_PORT_A; break;
	case PORT_C: port = INTERRUPT_PORT_C; break;
	default: port = INTERRUPT_PORT_B; break; //portB
	}

	return reset(INTERRUPT_SET_ADRESS,port);// low active !
}

bool HAL::deactivateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_PORT_A; break;
	case PORT_C: port = INTERRUPT_PORT_C; break;
	default: port = INTERRUPT_PORT_B; break; //portB
	}
	return write(INTERRUPT_SET_ADRESS,port);// low active !
}

int HAL::getInterrupt(){
	int irq = read(PORT_IRQ_AND_RESET);
	irq = irq & IIR_MASK;
	return irq;
}

int HAL::getSetInterrupt(){
	return read(PORT_IRE);
}
