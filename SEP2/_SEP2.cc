#include <cstdlib>
#include <iostream>
#include "HAL.h"
#include "Sensor.h"
#include "Lampen.h"

void test_HAL_write();

int main(int argc, char *argv[]) {
	cout << "Welcome to the QNX Momentics IDE" << endl;
	HAL::getInstance();
	Lampen l;
	l.start(NULL);
	Sensor s;
	s.start(NULL);
	l.join();
	s.join();
	l.stop();
	s.stop();
	cout << "Versuch wird beendet" << endl;
	return EXIT_SUCCESS;
}

void test_HAL_write() {
	/*
	 * ep	s l
	 * 00 0 0 0
	 * 01 1 0 0
	 * 10 1 1 0
	 * 11 0 0 1
	 *E = eingabe
	 *P = vorhanden
	 *S = setzen
	 *L = löschen
	 */

	int portA = 0x01;
	int val = 0;
	int *port = 0;
	int value = 0x90;
	bool set = true;
	port = &portA;
	val = portA & value;
	int newVal = 0;
	//bitweise maskieren
	for (int i = 0; i < 8; i++) {
		int tmp = ((value & (1 << i)) >> i);
		cout << "\ntemp: " << tmp << endl;
		int zahl = (((*port) & (1 << i)) >> i);
		cout << "zahl: " << zahl << endl;
		if (tmp != 0) {
			if (set) {
				if(tmp == 1 && zahl == 0){
					tmp = 1;
					cout << tmp << " - " << zahl << endl;
				}
			} else {
				tmp = 0;
				cout << tmp << " - " << zahl << endl;
			}
		}else{
			tmp = zahl;
		}
		newVal = newVal | (tmp << i);
		cout << "newVal: "<<hex << newVal << endl;
	}

}
