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
 *
 *
 */

#include "Serial.h"

Serial::Serial() {
	ack = -1;
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

			while (receive(&msg, sizeof(msg)) == -2);
			printf("<<<<<----- Serial: %d received\n", msg);

			buildMessage(m, chid, coid, reactSerial, SENSOR, r_msg->pulse.value.sival_int);
			m->pulse.value.sival_int = msg;

			if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
				perror("Serial: failed to send Puls message to Sensor!");
			}

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
	locker.lock();
	unsigned int *p = (unsigned int*) (&data);
	int n = (int) write(ser, &data, lenBytes);
	printf("----->>>>>send: port %i DATA: %d \n", comPort,*p) ;


	if (n < 0) {
		printf("Write failed for com-port %i\n", comPort);
		return -1;
	} else {
		return 0;
	}//if
	locker.unlock();
	return 0;
}

int Serial::receive(unsigned int* data, int lenBytes) {
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
	}
}

void Serial::handleNormalMessage(){
	if(!handleConnectionMessage()){
		cout << "Test_Serial: can't handle Message"<<endl;
	}
}

void Serial::handlePulsMessage(){
	std::cout << "Serial: received a Puls, but doesn't know what to do with it" << std::endl;
}