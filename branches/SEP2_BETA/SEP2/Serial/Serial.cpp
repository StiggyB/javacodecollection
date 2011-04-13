#include "Serial.h"
#include "stdio.h"
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include "errno.h"



Serial::Serial(int numComPort, int choose, int debug) {
	hasSettings = 0;
	cnt = 0;

		struct termios termSettings;
	comPort = numComPort;

	if(choose==0 or choose==1){ //send SYN, get ACK OR get SYN, send ACK
		sender_receiver = choose;
	} else {
		if (debug){ printf("thread-modus not in range, only 0 or 1") };
		return -1;
	} //if

	switch(numComPort){
		case 1: ser = open("/dev/ser1",O_RDWR); break;
		case 2: ser = open("/dev/ser2",O_RDWR); break;
		default: if (debug){ printf("com-port %i not in rage!\n",numComPort); } return -1;
	}//switch

	if(ser == -1) {
		if(debug){ printf("Error serial port %i init\n",numComPort); fflush(stdout); }
		return -1;
	} else {
		if(debug){ printf("serial port %i open\n", numComPort); fflush(stdout); }
	}
	tcflush( ser, TCIOFLUSH );

	sleep(1);

	/* get options */
	tcgetattr(ser, &termSettings);

	/* set baudrate */
	cfsetispeed(&termSettings, B9600);
	cfsetospeed(&termSettings, B9600);
	if(debug){ printf("Input Baut Rate: %d\t Output Baut Rate: %d\n",termSettings.c_ispeed, termSettings.c_ospeed);
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
	if(debug){
		printf("c Flag: %d\n",termSettings.c_cflag);
		printf("fp zu com-port: %i\n",ser);
		fflush(stdout);
	}//if

	hasSettings = 1;
	return 0;
}

Serial::~Serial() {
	close(ser);
}

void Serial::execute(void* data) {
	char msg1[10];
	char msg2[10];
	char msg_rec[10];

	if(hasSettings){
		while( !isStopped() ){

			switch(sender_receiver){
			case 0:
				sprintf(msg1, "ACK%6d",cnt++);
				send(msg1,10); // send SYN, get ACK
				//printf("msg1=%s\n",msg1);
				//printf("SYN send\n");
				//printf("wait for ACK\n");
				while(receive(msg_rec,10)==-2);
				printf("%s\n",msg_rec);
				//printf("cnt = %i\n",cnt);
				fflush(stdout);
				sleep(1);
			break;

			case 1: //get SYN, send ACK
				//printf("----wait for SYN\n");
				while(receive(msg_rec,10)==-2);
				printf("----%s\n",msg_rec);
				sprintf(msg2, "SYN%6d",cnt++);
				//printf("msg2=%s\n",msg2);
				send(msg2,10);
				//printf("----ACK send\n");
				//printf("cnt = %i\n",cnt);
				fflush(stdout);
				sleep(1);
			break;
			}//switch
		}//while
	} else {
		printf("com-port %i not initiated\n");
	}//if
}

void Serial::shutdown(){

}

int Serial::init(int numComPort, int choose, int debug){
	struct termios termSettings;
	comPort = numComPort;

	if(choose==0 or choose==1){ //send SYN, get ACK OR get SYN, send ACK
		sender_receiver = choose;
	} else {
		if (debug){ printf("thread-modus not in range, only 0 or 1") };
		return -1;
	} //if

	switch(numComPort){
		case 1: ser = open("/dev/ser1",O_RDWR); break;
		case 2: ser = open("/dev/ser2",O_RDWR); break;
		default: if (debug){ printf("com-port %i not in rage!\n",numComPort); } return -1;
	}//switch

	if(ser == -1) {
		if(debug){ printf("Error serial port %i init\n",numComPort); fflush(stdout); }
		return -1;
	} else {
		if(debug){ printf("serial port %i open\n", numComPort); fflush(stdout); }
	}
	tcflush( ser, TCIOFLUSH );

	sleep(1);

	/* get options */
	tcgetattr(ser, &termSettings);

	/* set baudrate */
	cfsetispeed(&termSettings, B9600);
	cfsetospeed(&termSettings, B9600);
	if(debug){ printf("Input Baut Rate: %d\t Output Baut Rate: %d\n",termSettings.c_ispeed, termSettings.c_ospeed);
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
	if(debug){
		printf("c Flag: %d\n",termSettings.c_cflag);
		printf("fp zu com-port: %i\n",ser);
		fflush(stdout);
	}//if

	hasSettings = 1;
	return 0;
}

int Serial::send(void* data, int lenBytes){
	int n = (int)write(ser, data,lenBytes);
	if (n < 0){
		printf ("Write failed for com-port %i\n", comPort );
		return -1;
	} else {
		return 0;
	}//if

}

int Serial::receive(void* data, int lenBytes){
	int n = readcond(ser,data,lenBytes, 10, 0, 10);
	if (n < 0){
		if (errno == EAGAIN){
			//printf ("EAGAIN com-port %i\n", comPort );
			return -2; // assume that command generated no response
		}else{
		printf ("receive failed for com-port %i, errno=%i\n", comPort, errno );
			return -1;
		}
	} else {
		return 0;
	}//if// return 0;
}

