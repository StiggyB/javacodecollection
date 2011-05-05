
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
 * Implements Singleton-Pattern.
 *
 */

#include "HALCore.h"
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
 * instance of HALCore
 */
HALCore* HALCore::pInstance = NULL;
/**
 * mutex to ensure that HALCore stays a singleton
 */
Mutex HALCore::singleton;
Mutex HALCore::mutEx;


HALCore* HALCore::getInstance(){
	if( !pInstance){
		singleton.lock();
		if(!pInstance){
			pInstance = new HALCore;
		}
		singleton.unlock();
	}
	return pInstance;
}

HALCore::HALCore() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	controlBits = BIT_CNTRLS;
	out8(PORT_CNTRL,BIT_CNTRLS);
	out8(INTERRUPT_SET_ADRESS_D,0xFF);
	portA = read(PORT_A);
	portB = read(PORT_B);
	portC = read(PORT_C);
	portIRE = read(PORT_IRE);
	portIRQ = read(PORT_IRQ);
	//out8(PORT_C,0x0F);
	setFPArray();
#ifdef CONDOR
	condvar.setMutex(&mut);
	//mut;
	requested=false;
#endif
#ifdef SEMAP
	sem.init(1);
#endif
}

HALCore::~HALCore() {
	mutEx.~Mutex();
}

void HALCore::deleteInstance(){
	if( pInstance != NULL ){
		singleton.lock();
		if( pInstance != NULL ){
			delete pInstance;
			pInstance = NULL;
		}
		singleton.unlock();
	}
}

void HALCore::execute(void*) {
	list<Functions *>::iterator it = lst.begin();
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	//addLED(LEDS_ON);
	while (!isStopped()) {
#ifdef SEMAP
		std::cout << "HC waiting..." <<std::endl;
		sem.wait();
		if ((*it) != NULL) {
			std::cout << "HC: do something from queue! " << (*(*it)).func <<std::endl;
			(*this.*((*(*it)).func))((*(*it)).v);
		}
		free((*it));
		lst.erase(it);
		/*if(it != lst.end())*/ it++;
		//else it = lst.begin();
#endif
#ifdef CONDOR
		if(!lst.empty()){
			if((*it) != NULL){
				(*this.*((*(*it)).func))((*(*it)).v);
			}
			free((*it));
			lst.erase(it);
			it++;
		}else{
			changedMutex.lock();
			if(!requested){
				changedMutex.unlock();
				mut.lock();
				cout << "waiting" << endl;
				condvar.wait();
				mut.unlock();
				changedMutex.lock();
			}
			requested = false;
			changedMutex.unlock();
		}
#endif


	}
}

void HALCore::shutdown() {

}

int HALCore::setPortToInput(int bits){
	controlBits = controlBits | bits;
	out8(PORT_CNTRL,controlBits);
	return 1;
}

int HALCore::setPortToOutput(int bits){
	controlBits = controlBits  & (~bits);
	out8(PORT_CNTRL, controlBits);
	return 1;
}

bool HALCore::isOutput(int dir){
	return !isInput(dir);
}

bool HALCore::isInput(int dir){
	switch(dir){
	case PORT_A:dir = BIT_PORT_A; break;
	case PORT_B:dir = BIT_PORT_B; break;
	case PORT_C:dir = BIT_PORT_C; break;
	default: dir = 0x00; break;
	}
	return (controlBits & dir);
}

int HALCore::write(int dir, int value, bool set){
	//int val = getBitsToAdress(dir);
	value = checkVal(dir,value, set);
	int volatile *port = 0;
	switch(dir){
		case PORT_B: port = &portB; /* val = portB & value;*/ break;
		case PORT_C: port = &portC; /* val = portC & value;*/ break;
		case PORT_CNTRL: port = &controlBits;/* val = controlBits & value;*/ break;
		case INTERRUPT_SET_ADRESS_D: port = &portIRE;/* val = portIRE & value;*/ break;
		case INTERRUPT_RESET_ADRESS_D: port = &portIRQ;/* val = portIRQ & value;*/ break;
		default: port = &portA; portA = read(PORT_A);/* val = portA & value;*/ break; //PORT_A
	}
	//val = value;
	int newVal = 0;
	/*for (int i = 0; i < 8; i++) {
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
	*/ if(set) newVal = (value | (*port)) & 0xFF;
	 else newVal = ((*port) & (~value)) & 0xFF;
	*port = newVal;
	//std::cout << "RealWrite: " << std::hex << newVal << " on Adr.: "  << std::hex << dir << std::endl;
	out8(dir,newVal);
	return newVal;
}

int HALCore::read(int dir){
	return in8(dir);
}

int HALCore::getValueFromAdress(int dir){
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

int HALCore::getBitsToAdress(int dir){
	int bits = 0x00;
	switch (dir) {
		case PORT_A: bits = BIT_PORT_A; break;
		case PORT_B: bits = BIT_PORT_B; break;
		case PORT_C: bits = BIT_PORT_C; break;
		default: bits = 0x00; break;
	}
	return bits;
}

int HALCore::checkVal(int dir, int value,bool set) {
	if (dir == PORT_A && set) {
		if ((value == BIT_ENGINE_RIGHT || value == BIT_ENGINE_S_R) && (portA & BIT_ENGINE_LEFT)) {
			reset(PORT_A,BIT_ENGINE_LEFT);
		} else if ((value == BIT_ENGINE_LEFT || value == BIT_ENGINE_S_L) && (portA & BIT_ENGINE_RIGHT)) {
			reset(PORT_A,BIT_ENGINE_RIGHT);
		}
	}
	return value;
}

int HALCore::getColorCode(Color col) {
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

int HALCore::getLEDCode(LEDS led) {
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

const struct sigevent * ISR(void *arg, int id) {
	int val;
	short iir;
	struct sigevent *event = (struct sigevent*) arg;
	iir = in8(PORT_IRQ_AND_RESET) & IIR_MASK_D;
	switch(iir){
	case INTERRUPT_D_PORT_A: val = in8(PORT_A);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un2.__st.__sigev_priority,INTERRUPT_D_PORT_A,val);
	return (event);break;
	case INTERRUPT_D_PORT_B: val = in8(PORT_B);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un2.__st.__sigev_priority,INTERRUPT_D_PORT_B,val);
	return (event);break;
	case INTERRUPT_D_PORT_C_HIGH: val = in8(PORT_C);
	SIGEV_PULSE_INIT(event,(*event).__sigev_un1.__sigev_coid,(*event).__sigev_un2.__st.__sigev_priority,INTERRUPT_D_PORT_C_HIGH,val);
	return (event);break;
	default: return (NULL);break;
	}
	return (NULL);
}

int HALCore::getInterrupt(){
	int irq = read(PORT_IRQ_AND_RESET);
	irq = irq & IIR_MASK_D;
	return irq;
}

int HALCore::getSetInterrupt(){
	return read(PORT_IRE);
}


//TODO implement
void HALCore::stopProcess(){

}

void HALCore::emergencyStop(){
	engineStop();
	closeSwitch();
	engineReset();
	shine(RED);
	shineLED(LEDS_OFF);
	emstopped = true;
	stopped = true;
}

void HALCore::stopMachine(){
	engineStop();
	closeSwitch();
	shine(RED);
	shineLED(LEDS_OFF);
	stopped = true;
}

void HALCore::restart() {
	if (!emstopped) {
		stopped = false;
		cout << "CC: restart ;)" << endl;
		engineContinue();
		shine(GREEN);
	}
}

void HALCore::resetAll() {
	stopped = false;
	emstopped = false;
	cout << "CC: resetAll ;)" << endl;
	closeSwitch();
	engineReset();
	shine(GREEN);
	shineLED(LEDS_OFF);
}

void HALCore::wakeup(){
	//std::cout << "HC has to wakeup!" <<std::endl;
#ifdef CONDOR
	changedMutex.lock();
	requested = true;
	changedMutex.unlock();
	condvar.signal();
#endif
#ifdef SEMAP
	sem.post();
#endif
}

void HALCore::setFPArray(){
	funcArray[0]= &HALCore::write;
	funcArray[1]= &HALCore::reset;
}

HALCore::Functions * HALCore::buildFunctions(FP f, int val1, int val2){
	return buildFunctions(f, val1, val2, true);
}

HALCore::Functions * HALCore::buildFunctions(FP f, bool val3){
	return buildFunctions(f, 0, 0, val3);
}

HALCore::Functions * HALCore::buildFunctions(FP f, int val1){
	return buildFunctions(f, val1, 0, true);
}

HALCore::Functions * HALCore::buildFunctions(FP f, int val1, int val2, bool val3){
	Functions *ptrMyF = (Functions *) malloc(sizeof(Functions));
	VAL *va = (VAL*) malloc(sizeof(VAL));

	if(ptrMyF != NULL && va != NULL){
		ptrMyF->func=f;
		ptrMyF->v = va;
		va->value1 = val1;
		va->value2 = val2;
		va->value3 = val3;
		//std::cout << "Function Build: " << hex <<(func) << " " << hex << (p->v) << std::endl;
	}
	return ptrMyF;
}

void HALCore::write(void *ptr){
	VAL* v =  (VAL *) ptr;
	//std::cout << "Write: " << ptr << " "  << std::hex << v->value1  << " " << std::hex << v->value2 << " "  << std::hex << v->value3 << std::endl;
	write(v->value1, v->value2, v->value3);
}
void HALCore::reset(void *ptr){
	VAL* v =  (VAL *) ptr;
	//std::cout << "Reset: " << ptr<< " "  << std::hex << v->value1  << " " << std::hex << v->value2 << " "  << std::hex << v->value3 << std::endl;
	write(v->value1, v->value2, v->value3);
}

void HALCore::resetPortsDirection(){
	out8(PORT_CNTRL,BIT_CNTRLS);
}

void HALCore::setPortsTo(int cb){
	out8(PORT_CNTRL,cb);
}

void HALCore::write(int dir, int value){
	Functions * p = buildFunctions(funcArray[WRITE], dir, value, true);
	//
	lst.insert(lst.end(),p);
	wakeup();
}

void HALCore::reset(int dir, int value){
	Functions * p = buildFunctions(funcArray[RESET], dir, value, false);
	//std::cout << "Function Build: " << hex <<(p->func) << " " << hex << (p->v) << std::endl;
	lst.insert(lst.end(),p);
	wakeup();
}

void HALCore::engineStart(int direction) {
	if (!engineStopped()) {
		if (direction == BIT_ENGINE_LEFT) {
			reset(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_LEFT);
		} else if (direction == BIT_ENGINE_RIGHT) {
			reset(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_RIGHT);
		}
	}
}
void HALCore::openSwitch(){
	setSwitchDirection(BIT_SET);
}
void HALCore::closeSwitch(){
	setSwitchDirection(BIT_DELETE);
}
void HALCore::setSwitchDirection(bool dir){
	if(dir){
		write(PORT_A,BIT_SWITCH);
	}else{
		reset(PORT_A,BIT_SWITCH);
	}
}
void HALCore::engineReset(){
	int bit = BIT_ENGINE_RIGHT | BIT_ENGINE_LEFT | BIT_ENGINE_SLOW | BIT_ENGINE_STOP | BIT_SWITCH;
	reset(PORT_A,bit);
}
void HALCore::engineStop(){
	write(PORT_A,BIT_ENGINE_STOP);
}
void HALCore::engineContinue(){
	reset(PORT_A,BIT_ENGINE_STOP);
}
void HALCore::engineRight(){
	engineStart(BIT_ENGINE_RIGHT);
}
void HALCore::engineLeft(){
	engineStart(BIT_ENGINE_LEFT);
}
void HALCore::engineSlowSpeed(){
	if(!engineStopped()){
		write(PORT_A, BIT_ENGINE_SLOW);
	}
}
void HALCore::engineNormalSpeed(){
	if(!engineStopped()){
		reset(PORT_A, BIT_ENGINE_SLOW);
	}
}

bool HALCore::engineStopped(){
	return (portA & BIT_ENGINE_STOP);
}

void HALCore::engineSlowSpeed(int dir) {
	if(!engineStopped()){
		if (dir == BIT_ENGINE_LEFT || dir == BIT_ENGINE_S_L) {
			reset(PORT_A, BIT_ENGINE_RIGHT);
			write(PORT_A, BIT_ENGINE_LEFT | BIT_ENGINE_SLOW);
		} else if (dir == BIT_ENGINE_RIGHT || dir == BIT_ENGINE_S_R) {
			reset(PORT_A, BIT_ENGINE_LEFT);
			write(PORT_A, BIT_ENGINE_RIGHT | BIT_ENGINE_SLOW);
		}else{
			write(PORT_A, BIT_ENGINE_SLOW);
		}
	}
}

void HALCore::engineSpeed(bool slow) {
	if(!engineStopped()){
		if (slow) {
			write(PORT_A, BIT_ENGINE_SLOW);
		} else{
			reset(PORT_A, BIT_ENGINE_SLOW);
		}
	}
}

void HALCore::engineSlowLeft(){
	engineSlowSpeed(BIT_ENGINE_LEFT);
}
void HALCore::engineSlowRight(){
	engineSlowSpeed(BIT_ENGINE_RIGHT);
}

void HALCore::resetAllOutPut(){
	reset(PORT_A,0xFF);
}

void HALCore::addLight(Color col) {
	int old = getValueFromAdress(PORT_A);
	old = old | getColorCode(col);
	write(PORT_A, old);
}

void HALCore::removeLight(Color col) {
	int old = getColorCode(col);
	reset(PORT_A, old);
}

void HALCore::shine(Color col) {
	int val = getColorCode(col);
	shine(val);
}

void HALCore::shine(int color) {
	if (color == BIT_LIGHT_OFF) {
		reset(PORT_A, BIT_LIGHTS_ON);
	} else {
		reset(PORT_A, BIT_LIGHTS_ON);
		write(PORT_A, color);
	}
}

void HALCore::removeLED(LEDS led){
	int old = getLEDCode(led);
	reset(PORT_C, old);
}

void HALCore::addLED(LEDS led){
	int old = getValueFromAdress(PORT_C);
	old = old | getLEDCode(led);
	write(PORT_C, old);
}

void HALCore::shineLED(LEDS led){
	int val = getLEDCode(led);
	shineLED(val);
}

void HALCore::shineLED(int led) {
	if (led == 0) {
		reset(PORT_C, BIT_LEDS_ON);
	} else {
		reset(PORT_C, BIT_LIGHTS_ON);
		write(PORT_C, led);
	}
}

void HALCore::activateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_D_PORT_A; break;
	case PORT_C: port = INTERRUPT_D_PORT_C; break;
	default: port = INTERRUPT_D_PORT_B; break; //portB
	}
	reset(INTERRUPT_SET_ADRESS_D,port);// low active !
}

void HALCore::deactivateInterrupt(int port){
	switch(port){
	case PORT_A: port = INTERRUPT_D_PORT_A; break;
	case PORT_C: port = INTERRUPT_D_PORT_C; break;
	default: port = INTERRUPT_D_PORT_B; break; //portB
	}
	write(INTERRUPT_SET_ADRESS_D,port);// low active !
}

