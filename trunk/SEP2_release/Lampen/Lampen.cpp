/*
 * Lampen.cpp
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#include "Lampen.h"

Lampen::Lampen() {
	if (ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "Lampen: Error for IO Control" << std::endl;
		//return EXIT_FAILURE;
	}
	h = HAL::getInstance();
}

Lampen::~Lampen() {
	h = NULL;
}

void Lampen::execute(void*) {
	prepare();
	test_HAL();
	lampen_M1();
	//test_HAL_CheckVal();
	//testIRQ();
}

void Lampen::prepare() {
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

void Lampen::shutdown() {
	cout << "Test beendet" << endl;
#ifdef SIMULATION
	IOaccess_close(); // Schließe die Verbindung zur Simulation
#endif

}

void Lampen::flash(int time, HAL::Color color) {

}

void Lampen::flash(int time, int duration, HAL::Color col) {

}

void Lampen::addLight(HAL::Color col) {
	(*h).addLight(col);
}

void Lampen::removeLight(HAL::Color col) {
	(*h).removeLight(col);
}
void Lampen::shine(HAL::Color col) {
	(*h).shine(col);
}

/*
void Lampen::test_HAL_Lampen_write_reset() {
	//write & reset Tests
	int i;
	i = (*h).reset(PORT_A, 0xFF);
	cout << "reset all " << i << endl;
	sleep(5);
	i = (*h).write(PORT_A, BIT_SWITCH);
	cout << "set switch " << i << endl;
	sleep(1);
	cout << "set R-Y-G " << endl;
	i = (*h).write(PORT_A, 0x80);
	cout << i;
	sleep(2);
	i = (*h).write(PORT_A, 0x40);
	cout << " " << i;
	sleep(2);
	i = (*h).write(PORT_A, 0x20);
	cout << " " << i << endl;
	sleep(2);

	cout << "reset R-Y-G " << endl;
	i = (*h).reset(PORT_A, 0x80);
	cout << " " << i;
	sleep(2);
	i = (*h).reset(PORT_A, 0x40);
	cout << " " << i;
	sleep(2);
	i = (*h).reset(PORT_A, 0x20);
	cout << " " << i;
	sleep(2);
}*/
/*
void Lampen::test_HAL_CheckVal() {
	//slow
	cout << "slow" << endl;
	(*h).write(PORT_A, BIT_ENGINE_SLOW);
	sleep(5);
	//right
	cout << "right" << endl;
	(*h).write(PORT_A, BIT_ENGINE_RIGHT);
	sleep(5);
	(*h).reset(PORT_A, BIT_ENGINE_RIGHT);
	//slow left
	cout << "slow left" << endl;
	(*h).write(PORT_A, BIT_ENGINE_LEFT);
	sleep(1);
	(*h).write(PORT_A, BIT_ENGINE_SLOW);
	sleep(5);
	//slow left to right change
	cout << "slow left to right change" << endl;
	(*h).write(PORT_A, BIT_ENGINE_RIGHT);
	sleep(5);
	//slow right to left change
	cout << "slow right to left change" << endl;
	(*h).write(PORT_A, BIT_ENGINE_LEFT);
	sleep(5);
	cout << "Engine STOP" << endl;
	(*h).write(PORT_A, BIT_ENGINE_STOP);
	sleep(5);
}*/
/*
void Lampen::test() {
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
*/
void Lampen::test_HAL() {
	int time = 3;
	bool t  = false;
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		shutdown();
	}
	//(*h).write(PORT_CNTRL,BIT_CNTRLS,false);
	out8(DIGITAL_CARD_CONTROL, 0x82);
	out8(PORT_A, 0);
	//test_HAL_Lampen_write_reset();
	sleep(1);
	out8(PORT_A, 0x80);
	sleep(2);
	out8(PORT_A, 0);
	(*h).resetAllOutPut();
	sleep(5);
	// Treibe die Ampel
	for (int count = 0; count < 1; count++) {

		cout << "PORTs testen" << endl;
		t = (*h).isInput(PORT_A);
		cout << "PORT_A is Input? " << t << endl;
		t = (*h).isInput(PORT_B);
		cout << "PORT_B is Input? " << t << endl;
		t = (*h).isInput(PORT_C);
		cout << "PORT_C is Intput? " << t << endl;
		t = (*h).isOutput(PORT_A);
		cout << "PORT_A is Output? " << t << endl;
		t = (*h).isOutput(PORT_B);
		cout << "PORT_B is Output? " << t << endl;
		t = (*h).isOutput(PORT_C);
		cout << "PORT_C is Output? " << t << endl;
		sleep(time);

		//HARDWARE TESTS

		cout << "Engine RIGHT" << endl;
		(*h).engineRight();
		sleep(time);

		t = (*h).engineStopped();
		cout << "Engine Stopped?" << t << endl;

		cout << "ENGINE LEFT" << endl;
		(*h).engineLeft();
		sleep(time);

		cout << "Engine RIGHT" << endl;
		(*h).engineStart(BIT_ENGINE_RIGHT);
		sleep(time);

		cout << "ENGINE LEFT" << endl;
		(*h).engineStart(BIT_ENGINE_LEFT);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*h).engineSlowSpeed();
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*h).engineNormalSpeed();
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*h).engineSpeed(true);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*h).engineSpeed(false);
		sleep(time);
		cout << "ENGINE SLOW RIGHT" << endl;
		(*h).engineSlowSpeed(BIT_ENGINE_S_R);
		sleep(time);

		cout << "ENGINE SLOW LEFT" << endl;
		(*h).engineSlowSpeed(BIT_ENGINE_S_L);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*h).engineSlowSpeed(BIT_ENGINE_SLOW);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*h).engineSpeed(false);
		sleep(time);

		cout << "+ENGINE STOP" << endl;
		(*h).engineStop();
		sleep(time);

		cout << "-ENGINE STOP" << endl;
		(*h).engineContinue();
		sleep(time);

		cout << "ENGINE S_L" << endl;
		(*h).engineSlowLeft();
		sleep(time);

		cout << "ENGINE S_R" << endl;
		(*h).engineSlowRight();
		sleep(time);

		cout << "ENGINE RESET" << endl;
		(*h).engineReset();
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*h).openSwitch();
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*h).closeSwitch();
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*h).setSwitchDirection(true);
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*h).setSwitchDirection(false);
		sleep(time);

		cout << "RESET" << endl;
		(*h).resetAllOutPut();
		sleep(time);


	}
}

void Lampen::lampen_M1() {
	int time = 3;
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
	out8(PORT_A, 0);
	//test_HAL_Lampen_write_reset();
	sleep(1);
	out8(PORT_A, 0x80);
	sleep(2);
	out8(PORT_A, 0);
	sleep(5);
	// Treibe die Ampel
	cout << "Farben starten: " << endl;
	for (int count = 0; count < 1; count++) {
		cout << "+rot" << endl;
		shine(HAL::RED);
		sleep(time);

		cout << "+gelb" << endl;
		shine(HAL::YELLOW);
		sleep(time);

		cout << "+gruen" << endl;
		shine(HAL::GREEN);
		sleep(time);
		//aus
		cout << "off" << endl;
		shine(HAL::OFF);
		sleep(time);
		// alle hinzuschalten
		cout << "+red" << endl;
		addLight(HAL::RED);
		sleep(time);

		cout << "+gelb" << endl;
		addLight(HAL::YELLOW);
		sleep(time);

		cout << "+gruen" << endl;
		addLight(HAL::GREEN);
		sleep(time);

		//lampen ausschalten
		cout << "-red" << endl;
		removeLight(HAL::RED);
		sleep(time);

		cout << "-gelb" << endl;
		removeLight(HAL::YELLOW);
		sleep(time);

		cout << "-gruen" << endl;
		removeLight(HAL::GREEN);
		sleep(time);

		//HARDWARE TESTS

		cout << "Engine RIGHT" << endl;
		(*h).write(PORT_A, BIT_ENGINE_RIGHT);
		sleep(time);

		cout << "ENGINE LEFT" << endl;
		(*h).write(PORT_A, BIT_ENGINE_LEFT);
		sleep(time);

		cout << "+ENGINE SLOW" << endl;
		(*h).write(PORT_A, BIT_ENGINE_SLOW);
		sleep(time);

		cout << "-ENGINE SLOW" << endl;
		(*h).reset(PORT_A, BIT_ENGINE_SLOW);
		sleep(time);

		cout << "+ENGINE STOP" << endl;
		(*h).write(PORT_A, BIT_ENGINE_STOP);
		sleep(time);

		cout << "-ENGINE STOP" << endl;
		(*h).reset(PORT_A, BIT_ENGINE_STOP);
		sleep(time);

		cout << "ENGINE S_L" << endl;
		(*h).write(PORT_A, BIT_ENGINE_S_L);
		sleep(time);

		cout << "ENGINE S_R" << endl;
		(*h).write(PORT_A, BIT_ENGINE_S_R);
		sleep(time);

		cout << "SWITCH ON" << endl;
		(*h).write(PORT_A, BIT_SWITCH);
		sleep(time);

		cout << "SWITCH OFF" << endl;
		(*h).reset(PORT_A, BIT_SWITCH);
		sleep(time);

		cout << "RESET" << endl;
		(*h).reset(PORT_A, 0xFF);
		sleep(time);
		(*h).resetAllOutPut();
	}
}
/*
void Lampen::testIRQ() {
	bool b = (*h).isOutput(PORT_B);
	cout << "Port B output?: " << b << endl;
	cout << "open Switch" << endl;
	(*h).write(PORT_B, BIT_SWITCH_OPEN);
	sleep(2);
	cout << "B: 1" << endl;
	(*h).write(PORT_B, 0x01);
	sleep(2);
	cout << "B: 2" << endl;
	(*h).write(PORT_B, 0x02);
	sleep(2);
	cout << "B: 3" << endl;
	(*h).write(PORT_B, 0x03);
	sleep(2);
	cout << "B: 4" << endl;
	(*h).write(PORT_B, 0x04);
	sleep(2);
	cout << "B: 5" << endl;
	(*h).write(PORT_B, 0x05);
	cout << "end irq test" << endl;
}
*/
