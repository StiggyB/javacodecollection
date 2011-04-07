/*
 * HAL.cpp
 *
 *  Created on: 31.03.2011
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
	mutEx.lock();
	if( instance == NULL){
		instance = new HAL();
	}
	mutEx.unlock();
	return instance;
}

HAL::HAL() {
	// TODO Auto-generated constructor stub
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
	return (controlBits & dir);
}

void HAL::resetPortsDirection(){
	out8(PORT_CNTRL,BIT_CNTRLS);
}

void HAL::setPortsTo(int cb){
	out8(PORT_CNTRL,cb);
}

int HAL::write(int dir, int value, bool set){
	bool reset = false;
	if((controlBits & dir) != 1){
		setPortToOutput(dir);
		reset = true;
	}
	value = checkVal(dir,value, set);
	int val = 0;
	int volatile *port = 0;
	switch(dir){
		case PORT_B: port = &portB; val = portB & value; break;
		case PORT_C: port = &portC; val = portC & value; break;
		case PORT_CNTRL: port = &controlBits; val = controlBits & value; break;
		case INTERRUPT_SET_ADRESS: port = &portIRE; val = portIRE & value; break;
		case INTERRUPT_RESET_ADRESS: port = &portIRQ; val = portIRQ & value; break;
		default: port = &portA; val = portA & value; break; //PORT_A
	}
	int newVal = 0;
	for (int i = 0; i < 8; i++) {
		int tmp = ((value & (1 << i)) >> i);
		int zahl = (((*port) & (1 << i)) >> i);
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
		newVal = newVal | (tmp << i);
	}
	*port = newVal;
	out8(dir,*port);
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
		if (value == BIT_ENGINE_RIGHT && (portA & BIT_ENGINE_LEFT)) {
			reset(PORT_A,BIT_ENGINE_LEFT);
		} else if (value == BIT_ENGINE_LEFT && (portA & BIT_ENGINE_RIGHT)) {
			reset(PORT_A,BIT_ENGINE_RIGHT);
		}
	}
	return value;
}

void HAL::engineStart(int direction) {
	if (!engineStopped()) {
		if (BIT_ENGINE_LEFT) {
			reset(PORT_A,BIT_ENGINE_RIGHT);
			write(PORT_A,BIT_ENGINE_LEFT);
		} else if (BIT_ENGINE_RIGHT) {
			reset(PORT_A,BIT_ENGINE_LEFT);
			write(PORT_A,BIT_ENGINE_RIGHT);
		}

	}
}
void HAL::openSwitch(){
	setSwitchDirection(BIT_SET);
}
void HAL::closeSwitch(){
	setSwitchDirection(BIT_DELETE);
}
void HAL::setSwitchDirection(bool dir){
	if(dir){
		write(PORT_A,BIT_SWITCH);
	}else{
		reset(PORT_A,BIT_SWITCH);
	}
}
void HAL::engineReset(){
	reset(PORT_A,BIT_ENGINE_RIGHT);
	reset(PORT_A,BIT_ENGINE_LEFT);
	reset(PORT_A,BIT_ENGINE_SLOW);
}
void HAL::engineStop(){
	write(PORT_A,BIT_ENGINE_STOP);
}
void HAL::engineRight(){
	engineStart(BIT_ENGINE_RIGHT);
}
void HAL::engineLeft(){
	engineStart(BIT_ENGINE_LEFT);
}
void HAL::engineSlow(){
	if(!engineStopped()){
		write(PORT_A, BIT_ENGINE_SLOW);
	}
}

bool HAL::engineStopped(){
	return (portA & BIT_ENGINE_STOP);
}

void HAL::engineSlow(int dir) {
	if(!engineStopped()){
		if (BIT_ENGINE_LEFT) {
			reset(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_SLOW);
		} else if (BIT_ENGINE_RIGHT) {
			reset(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_SLOW);
		}
	}
}

void HAL::engineSlowLeft(){
	engineSlow(BIT_ENGINE_LEFT);
}
void HAL::engineSlowRight(){
	engineSlow(BIT_ENGINE_RIGHT);
}

void HAL::attachISR(void * arg){
	struct sigevent * event = (struct sigevent*) arg;
	int id = InterruptAttach(HW_SERIAL_IRQ,ISR,&event,sizeof(event),0);
}


const struct sigevent * ISR(void *arg, int id){
	int iir;
	struct sigevent *event = (struct sigevent*) arg;
	iir = in8(PORT_IRQ_AND_RESET) & IIR_MASK;
	printf("hallo ISR");
	if(iir & 1) return (NULL);
	switch(iir){
	case INTERRUPT_PORT_A: portA = in8(PORT_A); return (event);break;
	case INTERRUPT_PORT_B: portB = in8(PORT_B); return (event);break;
	case INTERRUPT_PORT_C: portC = in8(PORT_C); return (event);break;
	default: return (NULL);break;
	}
	return (NULL);
}


void HAL::activateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_PORT_A; break;
	case PORT_C: port = INTERRUPT_PORT_C; break;
	default: port = INTERRUPT_PORT_B; break; //portB
	}
	write(INTERRUPT_SET_ADRESS,port,false); // low active !
}

void HAL::deactivateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_PORT_A; break;
	case PORT_C: port = INTERRUPT_PORT_C; break;
	default: port = INTERRUPT_PORT_B; break; //portB
	}
	write(INTERRUPT_SET_ADRESS,port,true); // low active !
}

int HAL::getInterrupt(){
	int irq = read(PORT_IRQ_AND_RESET);
	irq = irq & IIR_MASK;
	return irq;
}

