
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
	printf("Serial COnstructor!\n");
	ack = -1;
	printf("Serial COnstructor - ack = 0\n");
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("ThreadCtl access failed\n");
		}
}

void Serial::init(int numComPort, bool debug) {
	printf("init Serial\n");
	hasSettings = false;
	cnt = 0;
	struct termios termSettings;
	comPort = numComPort;



	switch (numComPort) {
	case 1:
		ser = open("/dev/ser1", O_RDWR );
		break;
	case 2:
		ser = open("/dev/ser2", O_RDWR );
		break;
		default:
			#ifdef DEBUG_SERIAL
				printf("com-port %i not in range!\n",numComPort);
			#endif
			break;
	}//switch

#ifdef DEBUG_SERIAL
	if (ser == -1) {
		printf("Error serial port %i init\n", numComPort);
		fflush(stdout);
	} else {
		printf("serial port %i open\n", numComPort);
		fflush(stdout);
	}
#endif

	tcflush(ser, TCIOFLUSH );

	sleep(1);

	/* get options */
	tcgetattr(ser, &termSettings);

	/* set baudrate */
	cfsetispeed(&termSettings, B115200);
	cfsetospeed(&termSettings, B115200);
#ifdef DEBUG_SERIAL
		printf("Input Baut Rate: %d\t Output Baut Rate: %d\n",
				termSettings.c_ispeed, termSettings.c_ospeed);
		fflush(stdout);
#endif

	/* 8 data, 1 stop, no paity */
	termSettings.c_cflag &= ~CSIZE;
	termSettings.c_cflag &= ~CSTOPB;
	termSettings.c_cflag &= ~PARENB;
	termSettings.c_cflag |= CS8;
	termSettings.c_cflag |= CREAD;
	termSettings.c_cflag |= CLOCAL;

	tcsetattr(ser, TCSANOW, &termSettings);
#ifdef DEBUG_SERIAL
		printf("c Flag: %d\n", termSettings.c_cflag);
		printf("fp zu com-port: %i\n", ser);
		fflush(stdout);
#endif

	hasSettings = true;

}

Serial::~Serial() {
	close(ser);
}


void Serial::execute(void* data) {



	if (settingUpSerial()) {

		int msg = -1;

		if (hasSettings) {
			if(comPort == 1){/*TODO : muss noch auf BAND1 geändert werden*/
				msg = 1337;

				while(ack != 42){
					send(&msg, sizeof(msg));
					receive(&ack, sizeof(ack));
					if(ack == 1337)printf("ERROR: 2 DADDY's???\n");
					sleep(1);
				}//while

				#ifdef DEBUG_SERIAL
				printf("DEBUG: Daddy wurde gefunden\n");
				#endif

				msg = -1;
				ack = -1;
			}//if



			while (!isStopped()) {

				while( receive(&msg, sizeof(msg)) == -2){
					//send (&tmp,1);
				}//while

				switch(msg){
					case -1 : break;
					//sync message
					case SYNC_SIGNAL: printf("get message SYNC_SIGNAL com %d \n",comPort);
							ack = 10; send(&ack,sizeof(ack));
							break;
					//message from Band 1 to Band 2
					case POCKET_TOP: printf("get message POCKET_TOP com %d\n",comPort);
							if(sendPulses(ANLAGENSTEUERUNG, comPort, msg)){
								ack = 11; send(&ack,sizeof(ack));
							}
							break;
					case POCKET_BOTTOM: printf("get message POCKET_BOTTOM com %d \n", comPort);
							if(sendPulses(ANLAGENSTEUERUNG, comPort, msg)){
								ack = 12; send(&ack,sizeof(ack));
							}
							break;
					case BAND2_FREE: printf("get message BAND2_FREE com %d \n",comPort);
							if(sendPulses(ANLAGENSTEUERUNG, comPort, msg)){
								ack = 13; send(&ack,sizeof(ack));
							}
							break;
					// message ack
					case 10: printf("ack message POCKET_TOP com %d\n",comPort); ack = 0;
							 break;
					case 11: printf("ack message POCKET_BOTTOM com %d\n",comPort); ack = 1;
							 break;
					case 12: printf("ack message BAND2_FREE com %d\n",comPort); ack = 2;
							 break;
					case 13: printf("ack message SYNC_SIGNAL com %d\n",comPort); ack = 3;
							 break;
					// init message
					case 1337: printf("You want to be my DADDY??? -----> OK\n");
							   ack = 42; send(&ack, sizeof(ack));
							   break;
					default: printf("ERROR: unknown info com %d msg: %d\n", comPort, msg);
							 break;
				}//switch

				msg = -1;
			}//while
		} else {
			printf("com-port %i not initiated\n");
		}//if

	}else{
			perror("Serial: Setting Up failed!");
	}//if
}

void Serial::shutdown() {
	close(ser);
}

int Serial::send(void* data, int lenBytes) {
	int cnt = 0;
	int *p = (int*)(data);
	int n = (int) write(ser, data, lenBytes);
	if(n >= 0 ||*p < 10){
		while(ack != *p && cnt <= 10){
			delay(100);//delay in ms
			cnt++;
		}
	}
	#ifdef DEBUG_SERIAL
		printf("Serial::send: ack_done: %i data: %i port %i\n",ack,*p,comPort);
	#endif
	ack = -1;
	if (n < 0 || cnt >= 10) {
		printf("Write failed for com-port %i\n", comPort);
		return -1;
	} else {
		return 0;
	}//if

}

int Serial::receive(void* data, int lenBytes) {
	//printf("Want to receive..\n");
	int n = readcond(ser, data, lenBytes, 1,0,10);
	//printf("n=%i on Com %d",n, comPort);

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

bool Serial::settingUpSerial(){

	if (prepareCommunication(SERIAL)) {
		if (!requestChannelIDForObject(ANLAGENSTEUERUNG)) {
			perror("SERIAL: request failed");
			unregisterChannel(SERIAL);
			return false;
		}

		if (!allocMessages()) {
			clean();
			return false;
		}
		if(!connectWithCommunicator(0,ANLAGENSTEUERUNG,SERIAL)){
			clean();
			return false;
		}
	}
	return true;
}

void Serial::clean(){
	unregisterChannel(SERIAL);
	cleanUp(0, m, r_msg);
	destroyChannel(chid);
}


void Serial::handlePulsMessage(){std::cout << "Sensor: received a Puls, but doesn't know what to do with it" << std::endl;}
void Serial::handleNormalMessage(){std::cout << "Sensor: received a Puls, but doesn't know what to do with it" << std::endl;}
