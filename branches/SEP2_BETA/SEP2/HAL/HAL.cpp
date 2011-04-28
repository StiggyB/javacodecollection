
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
	setPortToInput(BIT_CNTRLS);
	out8(PORT_CNTRL,BIT_CNTRLS);
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


bool HAL::isInput2(int dir){
	return !isOutput2(dir);
}

bool HAL::isOutput2(int dir){
	switch(dir){
	case PORT_A:dir = BIT_PORT_A;break;
	case PORT_B:dir = BIT_PORT_B;break;
	case PORT_C:dir = BIT_PORT_C;break;
	default:break;
	}
	return (controlBits & dir);
}

bool HAL::isOutput(int dir){
	return !isInput(dir);
}

bool HAL::isInput(int dir){
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
		std::cout << "setting to output :D cb: " << controlBits << " val: " <<std::hex << val << " dir: "<< dir <<std::endl;
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
	//int cb = controlBits;
	//bool reset = !isInput(dir);
	//int bits = getBitsToAdress(dir);
	//if(reset){
	//	std::cout << "HAL: needed to set to input" << std::endl;
	//	setPortToInput(bits); }
	//int l = in8(dir);
	//if(reset){ setPortToInput(bits); }
	//setPortsTo(cb);
	//return l;
	return in8(dir);
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

bool HAL::shine(Color col) {
	int val = getColorCode(col);
	return shineLED(val);
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

int HAL::getLEDCode(LEDS led) {
	int val = 0;
	switch (led) {
	case START_LED:
		val = BIT_LED_START;
		break;
	case RESET_LED:
		val = BIT_LED_RESET;
		break;
	case Q1_LED:
		val = BIT_LED_Q1;
		break;
	case Q2_LED:
		val = BIT_LED_Q2;
		break;
	case LEDS_ON:
		val = BIT_LEDS_ON;
		break;
	default: // Q1_LED
		val = 0x00;
		break;
	}
	return val;
}

bool HAL::removeLED(LEDS led){
	int old = getLEDCode(led);
	return reset(PORT_C, old);
}
bool HAL::addLED(LEDS led){
	int old = getValueFromAdress(PORT_C);
	old = old | getLEDCode(led);
	return write(PORT_C, old);
}

bool HAL::shineLED(LEDS led){
	int val = getLEDCode(led);
	return shineLED(val);
}

bool HAL::shineLED(int led) {
	if (led == 0) {
		return reset(PORT_C, BIT_LEDS_ON);
	} else {
		bool r = reset(PORT_C, BIT_LIGHTS_ON);
		bool w = write(PORT_C, led);
		return (r && w);
	}
}

const struct sigevent * ISR(void *arg, int id) {
	//static short peter = 0;
	//static short otto = 0;
	int val;
	short iir;
	struct sigevent *event = (struct sigevent*) arg;
	iir = in8(PORT_IRQ_AND_RESET) & IIR_MASK_D;
	//if(iir & 1) return (NULL);
	//out8(PORT_A,iir);
	/*
	(*event).sigev_notify = SIGEV_PULSE;
	(*event).sigev_code = 7;
	(*event).__sigev_un2.__st.__sigev_code = 7;
	(*event).sigev_value.sival_int = iir;
	*///SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,SIGEV_PULSE_PRIO_INHERIT,otto++,peter++);
	//return (event);//break;
	//*

	switch(iir){
	case INTERRUPT_D_PORT_A: val = in8(PORT_A);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un2.__st.__sigev_priority,INTERRUPT_D_PORT_A,val);
	return (event);break;
	case INTERRUPT_D_PORT_B: val = in8(PORT_B);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un2.__st.__sigev_priority,INTERRUPT_D_PORT_B,val);// ;
	return (event);break;
	case INTERRUPT_D_PORT_C: val = in8(PORT_C);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un2.__st.__sigev_priority,INTERRUPT_D_PORT_C_HIGH,val);
	return (event);break;
	default: return (NULL);break;
	}
	return (NULL);//*/
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

bool HAL::setValueOfPort(int port,int val){
	bool ret = true;
	switch(port){
	case PORT_A: portA = val; break;
	case PORT_C: portC = val; break;
	case PORT_B: portB = val; break;
	default: ret = false; break;
	}
	return ret;
}
