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

Serial::Serial() {
	//printf("Serial COnstructor!\n");
	ack = -1;
	printf("Serial COnstructor - ack = 0\n");
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	#ifdef TEST_SER
	receiver = TESTER;
	#else
	receiver = SENSOR;
	#endif
	mine = SERIAL;
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
		printf("com-port %i not in range!\n", numComPort);
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
	cfsetispeed(&termSettings, _TIOS_B9600);
	cfsetospeed(&termSettings, _TIOS_B9600);
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

	msg = -1;
	ack = -1;
	if (hasSettings) {

		if (settingUpCommunicatorDevice(receiver)) {
cout <<"SETTING UP SERIAL ERFOLGREICH------------------------"<<endl;
		while (!isStopped()) {

//			printf(
//					"Serial: waiting to receive something... :D com port: %i msg: %d\n",
//					comPort, msg);
			while (receive(&msg, sizeof(msg)) == -2) {
				//printf("recive nothing: %d port %d\n", msg,comPort);
			}//while

//			printf("MSG: %x port: %d\n", msg, comPort);

			printf("<<<<<----- Serial: %d received\n", msg);

			buildMessage(m, chid, coid, reactSerial, SENSOR, r_msg->pulse.value.sival_int);
//				m->m.ca = reactSerial;
			m->pulse.value.sival_int = msg;

			if (-1 == MsgSend(coid, m, sizeof(Message), r_msg,
					sizeof(Message))) {
				perror("Serial: failed to send Puls message to Sensor!");
			}

//			switch (msg) {
//			case -1:
//				break;
//
//				//sync message
//			case SYNC_SIGNAL:
//				printf("<<<<<----- Serial: SYNC_SIGNAL an PORT: %d\n", comPort);
//				break;
//
//
//			//message from Band 1 to Band 2
//			case POCKET:
//				printf("<<<<<----- Serial: POCKET an PORT: %d\n", comPort);
//				printList();
//				//sendPulses(SENSOR, 9, 50);
//				buildMessage(m, chid, coid, react, SENSOR, r_msg->pulse.value.sival_int);
//
//							m->m.ca = react;
//							m->pulse.value.sival_int = 50;
//
//				if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
//							perror(
//									"InterruptController: failed to send Puls message to Sensor!");
//						}
//				printf("<<<<<----- Serial: POCKET an PORT: %d done\n", comPort);
//
//				break;
//			case NO_POCKET:
//				printf("<<<<<----- Serial: NO_POCKET an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//			case REQUEST_FREE:
//				printf("<<<<<----- Serial: REQUEST an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//
//
//
//
//			//BUTTONS
//			case E_STOP_PUSHED:
//				printf("<<<<<----- Serial: E_STOP_PUSHED an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//			case E_STOP_PULLED:
//				printf("<<<<<----- Serial: E_STOP_PULLED an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//			case STOP_BUTTON:
//				printf("<<<<<----- Serial: STOP an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//			case START_BUTTON:
//				printf("<<<<<----- Serial: START an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//			case RESET_BUTTON:
//				printf("<<<<<----- Serial: RESET an PORT: %d\n", comPort);
//				sendPulses(receiver, comPort, msg);
//				break;
//
//
//
//				// init message
//			case INIT_SERIAL:
//				printf("<<<<<----- You want to be my DADDY??? -----> OK\n");
//				break;
//			case ACK_INIT_SERIAL:
//				printf("<<<<<----- Serial: ACK_INIT_SERIAL an PORT: %d\n", comPort);
//				break;
//			default:
//				printf("ERROR: unknown info com %d msg: %d\n", comPort, msg);
//				break;
//			}//switch

			msg = -1;
		}//while
		}else{
			perror("Serial: Setting Up failed!");
		}
	} else {
		perror("Serial: com-port %i not initiated\n");
	}//if


}

void Serial::shutdown() {
	close(ser);
}

int Serial::send(int data, int lenBytes) {

	unsigned int *p = (unsigned int*) (&data);
	int n = (int) write(ser, &data, lenBytes);
	printf("----->>>>>send: port %i DATA: %d \n", comPort,*p) ;


	if (n < 0) {
		printf("Write failed for com-port %i\n", comPort);
		return -1;
	} else {
		return 0;
	}//if
	cout << "hello! :P" << endl;
	return 0;
}

int Serial::receive(void* data, int lenBytes) {
	//printf("Want to receive..\n");
	int n = readcond(ser, data, lenBytes, 0, 0, 10);
	//printf("n=%i on Com %d",n, comPort);

	if (n <= 0) {
		if (errno == EAGAIN || n == 0) {
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

void Serial::handleNormalMessage(){
	if(!handleConnectionMessage()){
		cout << "Test_Serial: can't handle Message"<<endl;
	}
}

void Serial::handlePulsMessage(){
	std::cout << "Serial: received a Puls, but doesn't know what to do with it" << std::endl;
}
