/**
 * Testing Class for Serial
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Prepares some Testing stuff for the Interrupts.
 *
 * Inherits: thread::HAWThread
 */
#include "Test_Serial.h"

Test_Serial::Test_Serial() {

	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}



}


Test_Serial::~Test_Serial() {

}

void Test_Serial::execute(void*){

	int cnt = 0;

	switch(numComPort){
		case 1:
			send("hello",6);
			while (receive(msg_rec, SIZE_OF_WS) == -2)
								;
			printf("----msg_rec--- %s\n", msg_rec);
			send("this is a serial test",22);

			break;
		case 2: break;
	}


}

void Test_Serial::shutdown(){
	if(-1 == close(ser)){
		perror("close Serial %i failed\n",numComPort);
	}else if(debug){
		cout << "close successful" << endl;
	}
	cout << "end of SERIAL-Tests" << endl;
}
