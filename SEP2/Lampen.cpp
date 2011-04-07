/*
 * Lampen.cpp
 *
 *  Created on: 30.03.2011
 *      Author: Administrator
 */

#include "Lampen.h"

Lampen::Lampen() {
	h = HAL::getInstance();
}

Lampen::~Lampen() {
	h = NULL;
}

void Lampen::execute(void*){
	prepare();
	//lampen_M1();
	test_HAL_CheckVal();
	testIRQ();
}

void Lampen::prepare(){
#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen."
			<< endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		shutdown();
	}
	//(*h).write(PORT_CNTRL,BIT_CNTRLS,false);
	out8(DIGITAL_CARD_CONTROL, 0x82);

}

void Lampen::shutdown(){
	cout << "Test beendet" << endl;
#ifdef SIMULATION
	IOaccess_close(); // Schließe die Verbindung zur Simulation
#endif

}

//TODO
void Lampen::flash(int time,Color color){

}

//TODO
void Lampen::flash(int time,int duration,Color col){

}

void Lampen::shine(int color){
	(*h).write(PORT_A, color,false);
}

void Lampen::shine(Color col){
	switch(col){
		case YELLOW:shine(BIT_LIGHT_YELLOW);break;
		case GREEN:shine(BIT_LIGHT_GREEN);break;
		case OFF:shine(BIT_LIGHT_OFF);break;
		default:shine(BIT_LIGHT_RED);break;
	}
}

int Lampen::getColorCode(Color col){
	int newColor = 0x00;
	switch (col) {
		case YELLOW: newColor = 0x40; break;
		case GREEN: newColor = 0x20; break;
		case RED: newColor = 0x80; break;
		default: newColor = 0x00; break;
	}
	return newColor;
}

void Lampen::addLight(Color col){
	int old = (*h).read(PORT_A);
	old = old | getColorCode(col);
	(*h).write(PORT_A,old,false);
}

void Lampen::removeLight(Color col){
	int old = (*h).read(PORT_A);
	old = old & (~getColorCode(col));
	(*h).write(PORT_A,old,false);
}

void Lampen::test_HAL_Lampen_write_reset(){
	//write & reset Tests
	int i;
	i=(*h).reset(PORT_A,0xFF);
	cout<<"reset all "<< i <<endl;
	sleep(5);
	i=(*h).write(PORT_A,BIT_SWITCH);
	cout << "set switch "<< i << endl;
	sleep(1);
	cout << "set R-Y-G " << endl;
	i = (*h).write(PORT_A,0x80);
	cout << i;
	sleep(2);
	i = (*h).write(PORT_A,0x40);
	cout << " "<< i;
	sleep(2);
	i = (*h).write(PORT_A,0x20);
	cout << " "<< i<<endl;
	sleep(2);

	cout << "reset R-Y-G " << endl;
	i = (*h).reset(PORT_A,0x80);
	cout << " "<< i;
	sleep(2);
	i = (*h).reset(PORT_A,0x40);
	cout << " "<< i;sleep(2);
	i = (*h).reset(PORT_A,0x20);
	cout << " "<< i;sleep(2);
}

void Lampen::test_HAL_CheckVal(){
	//slow
	cout << "slow"<<endl;
	(*h).write(PORT_A, BIT_ENGINE_SLOW);
	sleep(5);
	//right
	cout << "right"<<endl;
	(*h).write(PORT_A, BIT_ENGINE_RIGHT);
	sleep(5);
	(*h).reset(PORT_A,BIT_ENGINE_RIGHT);
	//slow left
	cout << "slow left"<<endl;
	(*h).write(PORT_A, BIT_ENGINE_LEFT);
	sleep(1);
	(*h).write(PORT_A, BIT_ENGINE_SLOW);
	sleep(5);
	//slow left to right change
	cout << "slow left to right change"<<endl;
	(*h).write(PORT_A,BIT_ENGINE_RIGHT);
	sleep(5);
	//slow right to left change
	cout << "slow right to left change"<<endl;
	(*h).write(PORT_A, BIT_ENGINE_LEFT);
	sleep(5);
	cout << "Engine STOP"<<endl;
	(*h).write(PORT_A, BIT_ENGINE_STOP);
	sleep(5);
}


void Lampen::test(){
	cout << "rot" << endl;
	shine(RED);
	//out8(D_IOBASE, 0x80);//rot
	sleep(1);
	out8(D_IOBASE, 0x80);
	sleep(1);
	// control auslesen und setzen
	int set = in8(D_IOBASE + 0x03);
	//cout << (out8(D_IOBASE + 0x03, set | 0x18));
	// Port A lesen
	int in1 = in8(D_IOBASE);
	cout << "in: 0x" << hex << in1 << endl;
	in1 = in1 | 0x20;
	cout << "in: 0x" << hex << in1 << endl;
	out8(D_IOBASE, in1);
	//shine(in1 | 0x20);
	sleep(1);

	int in = in8(D_IOBASE);
	sleep(1);
	cout << D_IOBASE << ": 0x" << hex << in << endl;

	in = in8(D_IOBASE + 0x01);
	sleep(1);
	cout << D_IOBASE + 0x01 << ": 0x" << hex << in << endl;

	in = in8(D_IOBASE + 0x02);
	sleep(1);
	cout << D_IOBASE + 0x02 << ": 0x" << hex << in << endl;

	in = in8(D_IOBASE + 0x01);
	sleep(1);
	cout << D_IOBASE + 0x01 << ": 0x" << hex << in << endl;

	in = in8(D_IOBASE);
	sleep(1);
	cout << D_IOBASE << ": 0x" << hex << in << endl;

	in = in8(D_IOBASE + 0x03);
	sleep(1);
	cout << D_IOBASE + 0x03 << ": 0x" << hex << in << endl;

	out8(D_IOBASE + 0x03, set);
}

void Lampen::test_HAL(){
	(*h).setPortToInput(PORT_A);
	(*h).setPortToOutput(PORT_A);
	int i = (*h).read(PORT_A);
	cout << hex << i <<endl;
	(*h).write(PORT_A,0x20,false);

	addLight(YELLOW);
	addLight(RED);

	removeLight(GREEN);
}

void Lampen::lampen_M1(){

#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen."
			<< endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		shutdown();
	}
	//(*h).write(PORT_CNTRL,BIT_CNTRLS,false);
	out8(DIGITAL_CARD_CONTROL, 0x82);

	test_HAL_Lampen_write_reset();

	sleep(5);
	// Treibe die Ampel
	cout << "Farben starten: " << endl;
	for (int count = 0; count < 5; count++) {
		cout << "rot" << endl;
		shine(RED);
		sleep(1);

		cout << "gelb" << endl;
		shine(YELLOW);
		sleep(1);

		cout << "gruen" << endl;
		shine(GREEN);
		sleep(1);
		//aus
		cout << "off" << endl;
		shine(OFF);
		sleep(1);
		// alle hinzuschalten
		cout << "red" << endl;
		addLight(RED);
		sleep(1);

		cout << "gelb" << endl;
		addLight(YELLOW);
		sleep(1);

		cout << "gruen" << endl;
		addLight(GREEN);
		sleep(1);

		//lampen ausschalten
		cout << "red" << endl;
		removeLight(RED);
		sleep(1);

		cout << "gelb" << endl;
		removeLight(YELLOW);
		sleep(1);

		cout << "gruen" << endl;
		removeLight(GREEN);
		sleep(1);

		//HARDWARE TESTS

		cout << "Engine RIGHT" << endl;
		(*h).write(PORT_A, BIT_ENGINE_RIGHT, false);
		sleep(1);

		cout << "ENGINE LEFT" << endl;
		(*h).write(PORT_A, BIT_ENGINE_LEFT, false);
		sleep(1);

		cout << "ENGINE SLOW" << endl;
		(*h).write(PORT_A, BIT_ENGINE_SLOW, false);
		sleep(1);

		cout << "ENIGNE STOP" << endl;
		(*h).write(PORT_A, BIT_ENGINE_STOP, false);
		sleep(1);

		cout << "ENGINE S_L" << endl;
		(*h).write(PORT_A, BIT_ENGINE_S_L, false);
		sleep(1);

		cout << "ENGINE S_R" << endl;
		(*h).write(PORT_A, BIT_ENGINE_S_R);
		sleep(1);

		cout << "SWITCH" << endl;
		(*h).write(PORT_A, BIT_SWITCH);
		sleep(1);

	}
	//*/

}

void Lampen::testIRQ(){
	cout << "" << endl;
	(*h).write(PORT_B,BIT_SWITCH_OPEN);
	sleep(2);

	(*h).write(PORT_B,0x01);
	sleep(2);
	(*h).write(PORT_B,0x02);
	sleep(2);
	(*h).write(PORT_B,0x03);
	sleep(2);
	(*h).write(PORT_B,0x04);
	sleep(2);
	(*h).write(PORT_B,0x05);
}
