
/**
 * Hardware Abstraction Layer for Aktorik and Sensorik.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 2: HAL Aktorik
 * Milestone 3: HAL Sensorik
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * in- and output from and to the Festo Transfersystem and
 * with Interrupts using Pulse Messages.
 *
 * Inherits: IHAL.h
 */

//TODO inherit Singleton

//TODO HAL -> port variables threadsafe while in ISR? would say sure!

/*
 * TODO Code Pruefung HAL:
	- Funktion: int HAL::write(int dir, int value, bool set)
  	  ist unübersichtlich und unleserlich
  	  Verbesserungsvorschlag: Extract Method für switch-case und evt. mehr.
  	  Steht nach wie vor zur Disskussion!
  	  --> Noch diskutieren (Jan)
  	- Zerstoerung der instance der HAL steht noch aus.
  	  Stichwort: Meyers Singleton bzw. Phoenix Singleton (Meeting Do 14.04 8:15Uhr - Besprochen) -> DONE!
*/

#include "HAL.h"
/**
 * Interrupt Service Routine
 */
const struct sigevent * ISR(void *arg, int id);
/**
 * copy of port A
 */
volatile int portA;
/**
 * copy of port B
 */
volatile int portB;
/**
 * copy of port C
 */
volatile int portC;
/**
 * copy of port IRE
 */
volatile int portIRE;
/**
 * copy of port IRQ
 */
volatile int portIRQ;
/**
 * copy of ControlBits
 */
volatile int controlBits;
/**
 * instance of HAL
 */
HAL* HAL::instance = NULL; //0 rein
/**
 * mutex to ensure that HAL stays a singleton
 */
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
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
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

void HAL::deleteInstance(){
	if( instance != NULL ){
		mutEx.lock();
		if( instance != NULL ){
			delete instance;
			instance = NULL;
		}
		mutEx.unlock();
	}
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
		case INTERRUPT_SET_ADRESS_D: port = &portIRE;/* val = portIRE & value;*/ break;
		case INTERRUPT_RESET_ADRESS_D: port = &portIRQ;/* val = portIRQ & value;*/ break;
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

int HAL::getValueFromAdress(int dir){
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
	bool r = false;
	if (!engineStopped()) {
		if (direction == BIT_ENGINE_LEFT) {
			ret = reset(PORT_A,BIT_ENGINE_RIGHT);
			r = write(PORT_A,BIT_ENGINE_LEFT);
			ret = ret && r;
		} else if (direction == BIT_ENGINE_RIGHT) {
			ret = reset(PORT_A,BIT_ENGINE_LEFT);
			r = write(PORT_A,BIT_ENGINE_RIGHT);
			ret = ret && r;
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
	bool r = reset(PORT_A,BIT_ENGINE_LEFT);
	ret = ret && r;
	r = reset(PORT_A,BIT_ENGINE_SLOW);
	ret = ret && r;
	r = reset(PORT_A,BIT_ENGINE_STOP);
	ret = ret && r;
	r = closeSwitch();
	return (ret && r);
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
		if (dir == BIT_ENGINE_LEFT || dir == BIT_ENGINE_S_L) {
			reset(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_SLOW);
		} else if (dir == BIT_ENGINE_RIGHT || dir == BIT_ENGINE_S_R) {
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
	int old = getValueFromAdress(PORT_A);
	old = old | getColorCode(col);
	return write(PORT_A, old);
}

bool HAL::removeLight(Color col) {
	int old = getColorCode(col);
	return reset(PORT_A, old);
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

bool HAL::shine(int color) {
	if (color == BIT_LIGHT_OFF) {
		return reset(PORT_A, BIT_LIGHTS_ON);
	} else {
		bool r = reset(PORT_A, BIT_LIGHTS_ON);
		bool w = write(PORT_A, color);
		return (r && w);
	}
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

const struct sigevent * ISR(void *arg, int id){
	int iir;
	struct sigevent *event = (struct sigevent*) arg;
	iir = in8(PORT_IRQ_AND_RESET) & IIR_MASK_D;
	if(iir & 1) return (NULL);
	switch(iir){
	case INTERRUPT_D_PORT_A: portA = in8(PORT_A);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un1.__sigev_id,INTERRUPT_D_PORT_A,0);
	return (event);break;
	case INTERRUPT_D_PORT_B: portB = in8(PORT_B);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un1.__sigev_id,INTERRUPT_D_PORT_B,0);
	return (event);break;
	case INTERRUPT_D_PORT_C: portC = in8(PORT_C);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un1.__sigev_id,INTERRUPT_D_PORT_C,0);
	return (event);break;
	default: return (NULL);break;
	}
	return (NULL);
}

bool HAL::activateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_D_PORT_A; break;
	case PORT_C: port = INTERRUPT_D_PORT_C; break;
	default: port = INTERRUPT_D_PORT_B; break; //portB
	}

	return reset(INTERRUPT_SET_ADRESS_D,port);// low active !
}

bool HAL::deactivateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_D_PORT_A; break;
	case PORT_C: port = INTERRUPT_D_PORT_C; break;
	default: port = INTERRUPT_D_PORT_B; break; //portB
	}
	return write(INTERRUPT_SET_ADRESS_D,port);// low active !
}

int HAL::getInterrupt(){
	int irq = read(PORT_IRQ_AND_RESET);
	irq = irq & IIR_MASK_D;
	return irq;
}

int HAL::getSetInterrupt(){
	return read(PORT_IRE);
}

float HAL::getHeight(){
	float val = 0;
	out8(HEIGHT_MEASURE,HEIGHT_START_CODE);
	int i = in8(HEIGHT_MEASURE);
	val = convertHeight(i);
	return val;
}
/*
 * This method converts the fix point value from the hight measure
 */
float HAL::convertHeight(int input){
	float output = 0.0;
	short zweierk = (~input+1);
	char t = 0;
	int i = 0;
	t = (input>>6); //nur die ganzzahl nehmen
	for(i=0;i<6;i++){//Nachkommaanteil setzen
		if( ( (((t<0)?zweierk:input) & (1<<i)) >> i ) == 1 ){//wenn Nachkommastelle gesetzt ist
			switch(i){
			case 0: output += 0.0625; break;
			case 1: output += 0.125; break;
			case 2: output += 0.25; break;
			case 3: output += 0.5; break;
			}//switch
		}//if
	}//for
	if( t<0 ){//falls Erg. negativ ist
		output = (-1)*output;
		if((output != 0)){//falls Nachkommaanteil
			t = t + 1;
		}//if
		output = output + t;

	}//if
	else{//positives Erg.
		output = output + t;
	}//else
	return output;
}//convertTemp
