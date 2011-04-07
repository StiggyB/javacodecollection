/*
 * Lampen.cpp
 *
 *  Created on: 30.03.2011
 *      Author: Administrator
 */

#include "Lampen.h"

Lampen::Lampen() {
	// TODO Auto-generated constructor stub
	h = HAL();
}

Lampen::~Lampen() {
	// TODO Auto-generated destructor stub
}

/*void Lampen::start(){
	thread::HAWThread::start();
}*/

void Lampen::execute(void*){
	#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen." << endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
	#endif

	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		shutdown();
	}
	out8(DIGITAL_CARD_CONTROL, 0x82);
	sleep(1);
	// Treibe die Ampel


	for (int count = 0; count < 20; count ++) {
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
		h.write(PORT_A, BIT_ENGINE_RIGHT);
		sleep(1);

		cout << "ENGINE LEFT" << endl;
		h.write(PORT_A, BIT_ENGINE_LEFT);
		sleep(1);

		cout << "ENGINE SLOW" << endl;
		h.write(PORT_A, BIT_ENGINE_SLOW);
		sleep(1);

		cout << "ENIGNE STOP" << endl;
		h.write(PORT_A, BIT_ENGINE_STOP);
		sleep(1);

		cout << "ENGINE S_L" << endl;
		h.write(PORT_A, BIT_ENGINE_S_L);
		sleep(1);

		cout << "ENGINE S_R" << endl;
		h.write(PORT_A, BIT_ENGINE_S_R);
		sleep(1);

		cout << "SWITCH" << endl;
		h.write(PORT_A, BIT_SWITCH);
		sleep(1);

	}


	cout << "Test beendet" << endl;
	#ifdef SIMULATION
		IOaccess_close(); // Schließe die Verbindung zur Simulation
	#endif

}

void Lampen::test_HAL(){
	cout << hex << h.controlBits<<endl;
	h.setPortToInput(PORT_A);
	h.setPortToOutput(PORT_A);
	int i = h.read(PORT_A);
	cout << hex << i <<endl;
	h.write(PORT_A,0x20);

	addLight(YELLOW);
	addLight(RED);

	removeLight(GREEN);
}

void Lampen::shutdown(){

}

//TODO
void Lampen::flash(int time,Color color){

}

//TODO
void Lampen::flash(int time,int duration,Color col){

}

void Lampen::shine(int color){
	out8(D_IOBASE, color);
}

void Lampen::shine(Color col){
	switch(col){
		case YELLOW:shine(BIT_LIGHT_YELLOW);break;
		case GREEN:shine(BIT_LIGHT_GREEN);break;
		case OFF:shine(BIT_LIGHT_OFF);break;
		default:shine(BIT_LIGHT_RED);break;
	}
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
	int old = h.read(PORT_A);
	old = old | getColorCode(col);
	h.write(PORT_A,old);
}

void Lampen::removeLight(Color col){
	int old = h.read(PORT_A);
	old = old & (~getColorCode(col));
	h.write(PORT_A,old);
}


