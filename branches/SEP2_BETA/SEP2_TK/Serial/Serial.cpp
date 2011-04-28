
/**
 * Interface for the Serial Connection
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * This will test the serial interface
 * To do a successful test:
 * -> one thread has to have modus 1 and the other modus 0.
 * Two threads with the same modus won't work.
 *
 */

#include "Serial.h"

Serial::Serial(){
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("ThreadCtl access failed\n");
		}
}

void Serial::init(int comPort, int modi, bool debug) {
	hasSettings = false;
	cnt = 0;
	struct termios termSettings;
	comPort = comPort;

	if (modi == 0 or modi == 1) { //send SYN, get ACK OR get SYN, send ACK
		sender_receiver = modi;
	} else {
		if (debug) {
			printf("thread-modus not in range, only 0 or 1");
		}
		//return -1;
	} //if

	switch (comPort) {
	case 1:
		ser = open("/dev/ser1", O_RDWR);
		break;
	case 2:
		ser = open("/dev/ser2", O_RDWR);
		break;
		//default: if (debug){ printf("com-port %i not in rage!\n",numComPort); } return -1;
	}//switch

	if (ser == -1) {
		if (debug) {
			printf("Error serial port %i init\n", comPort);
			fflush(stdout);
		}
		//return -1;
	} else {
		if (debug) {
			printf("serial port %i open\n", comPort);
			fflush(stdout);
		}
	}
	tcflush(ser, TCIOFLUSH );

	sleep(1);

	/* get options */
	tcgetattr(ser, &termSettings);

	/* set baudrate */
	cfsetispeed(&termSettings, B9600);
	cfsetospeed(&termSettings, B9600);
	if (debug) {
		printf("Input Baut Rate: %d\t Output Baut Rate: %d\n",
				termSettings.c_ispeed, termSettings.c_ospeed);
		fflush(stdout);
	}//if

	/* 8 data, 1 stop, no paity */
	termSettings.c_cflag &= ~CSIZE;
	termSettings.c_cflag &= ~CSTOPB;
	termSettings.c_cflag &= ~PARENB;
	termSettings.c_cflag |= CS8;
	termSettings.c_cflag |= CREAD;
	termSettings.c_cflag |= CLOCAL;

	tcsetattr(ser, TCSANOW, &termSettings);
	if (debug) {
		printf("c Flag: %d\n", termSettings.c_cflag);
		printf("fp zu com-port: %i\n", ser);
		fflush(stdout);
	}//if

	hasSettings = true;
}

Serial::~Serial() {
	close(ser);
}

void Serial::execute(void* data) {
	string msg_rec;

	if (hasSettings) {
		while (!isStopped()) {

			while (receive(msg_rec, SIZE_OF_WS) == -2)
					;
			if(debug){
				printf("----msg_rec--- %s\n", msg_rec);
			}
			if()

		}//while
	} else {
		printf("com-port %i not initiated\n");
	}//if
}

void Serial::shutdown() {
	if(-1 == close(ser)){
		perror("close Serial %i failed\n",numComPort);
	}else if(debug){
		cout << "close successful" << endl;
	}
}

int Serial::send(void* data, int lenBytes) {
	int n = (int) write(ser, data, lenBytes);
	if (n < 0) {
		printf("Write failed for com-port %i\n", comPort);
		return -1;
	} else {
		return 0;
	}//if

}

int Serial::receive(void* data, int lenBytes) {
	int n = readcond(ser, data, lenBytes, 10, 0, 10);
	if (n <= 0) {
		if (errno == EAGAIN || n==0) {
			//printf ("EAGAIN com-port %i\n", comPort );
			return -2; // assume that command generated no response
		} else {
			printf("receive failed for com-port %i, errno=%i\n", comPort, errno );
			return -1;
		}
	} else {
		return 0;
	}//if// return 0;
}

