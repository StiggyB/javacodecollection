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
	timer = Timer::getInstance();
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
	struct termios termSettings;
	comPort = numComPort;

	getAck = false;
	isSync = true;



	check_ack = FunctorMaker<Serial, void>::makeFunctor(this, &Serial::checkAck);
	check_init_ack = FunctorMaker<Serial, void>::makeFunctor(this, &Serial::checkInit);
	sync_error = FunctorMaker<Serial, void>::makeFunctor(this, &Serial::syncError);
	sync_send = FunctorMaker<Serial, void>::makeFunctor(this, &Serial::syncSend);

	timer->addUnstoppableFunction((CallInterface<CallBackThrower, void>*)check_ack);
	timer->addUnstoppableFunction((CallInterface<CallBackThrower, void>*)check_init_ack);
	timer->addUnstoppableFunction((CallInterface<CallBackThrower, void>*)sync_error);
	timer->addUnstoppableFunction((CallInterface<CallBackThrower, void>*)sync_send);

	sync_TID = timer->getnextid();
	checkAck_TID = timer->getnextid();
	sync_send_TID = timer->getnextid();


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


	send(INIT_SERIAL, sizeof(INIT_SERIAL));

	int id = timer->getnextid();
	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)check_init_ack, 1000, id);
	while (receive(&msg, sizeof(msg)) == -2);
	timer->deleteTimer(id);
	cout << "Serial: INIT successful!" << endl;

	hasSettings = true;

}

Serial::~Serial() {
	close(ser);
}

void Serial::execute(void* data) {
	msg = -1;

	if (hasSettings) {
		if (settingUpCommunicatorDevice(receiver)) {
			cout << "SETTING UP SERIAL ERFOLGREICH------------------------"
					<< endl;
			//#ifndef TEST_SER
				syncRestart();
			//#endif
			while (!isStopped()) {

				while (receive(&msg, sizeof(msg)) == -2);

				if(msg == SYNC){
					syncReceive();
			#ifdef TEST_SER
				}else{
			#else
				}else if(msg != ACK){
			#endif
					buildMessage(m, chid, coid, reactSerial, receiver,
							r_msg->pulse.value.sival_int);
					m->pulse.value.sival_int = msg;

					if (-1 == MsgSend(coid, m, sizeof(Message), r_msg,
							sizeof(Message))) {
						perror("Serial: failed to send Puls message to Sensor!");
					}
					/*
					if(!sendPulses(receiver, msg, msg)){
						perror("Serial: failed to send Puls message to Sensor!");
					}*/
				}

				msg = -1;
			}//while
		} else {
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
	if(data != SYNC && data != ACK){
		printf("----->>>>>send: port %i DATA: %d \n", comPort, *p);
	}

	locker.unlock();
	if (n < 0) {
		printf("Write failed for com-port %i\n", comPort);
		return -1;
	}else{
		if(hasSettings){
			//timer->addTimerFunction((CallInterface<CallBackThrower, void>*)check_ack, 250);
		}
	}
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
		if (*data == ACK) {
			getAck = true;
		}else{
			if(*data != SYNC){
				printf("<<<<<----- Serial: %d received\n", *data);
			}else
				if(hasSettings){
					//if serial is not synchronized and get an ack send start to restart line
					if(!isSync){
						buildMessage(m, chid, coid, reactSerial, receiver,
								r_msg->pulse.value.sival_int);
						m->pulse.value.sival_int = START_BUTTON;

						if (-1 == MsgSend(coid, m, sizeof(Message), r_msg,
								sizeof(Message))) {
							perror("Serial: failed to send Puls message to Sensor!");
						}

					}
				}
			send(ACK, sizeof(ACK));
		}
		return 0;
	}
}


void Serial::checkAck(){
	if(getAck){
		cout << "checkAck == false" << endl;
		getAck = false;
	}else{
		cout << "Serial: TIMEOUT. no ACK received" << endl;
	}
}


void Serial::syncError(){
	if(isSync){
		cout << "Serial: ERROR - did not get a SYNC message" << endl;
		buildMessage(m, chid, coid, reactSerial, receiver,
				r_msg->pulse.value.sival_int);
		m->pulse.value.sival_int = STOP_BUTTON;

		if (-1 == MsgSend(coid, m, sizeof(Message), r_msg,
				sizeof(Message))) {
			perror("Serial: failed to send Puls message to Sensor!");
		}
	}
	isSync = false;
	syncRestart();
}

void Serial::syncRestart(){
	if(!isSync){
		send(SYNC, sizeof(SYNC));
		timer->addTimerFunction((CallInterface<CallBackThrower, void>*)sync_error, T_SYNC_ERROR, sync_TID);
	}
}


void Serial::syncSend(){
	send(SYNC, sizeof(SYNC));
	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)sync_error, T_SYNC_ERROR, sync_TID);
}

void Serial::syncReceive(){
	if(!isSync){
		cout << "Serial: get a SYNC message" << endl;
	}
	isSync = true;
	timer->deleteTimer(syncId);
	timer->addTimerFunction((CallInterface<CallBackThrower, void>*)sync_send, T_SYNC_SEND, sync_send_TID);
}


void Serial::checkInit(){
	if(!hasSettings){
		if(getAck){
			cout << "checkInit == false" << endl;
			getAck = false;
		}else{
			cout << "Serial: INIT TIMEOUT. no ACK received." << endl;
			send(INIT_SERIAL, sizeof(INIT_SERIAL));
			timer->addTimerFunction((CallInterface<CallBackThrower, void>*)check_init_ack, 1000, sync_send_TID);
		}
	}
}


void Serial::handleNormalMessage() {
	if (!handleConnectionMessage()) {
		cout << "Test_Serial: can't handle Message" << endl;
	}
}

void Serial::handlePulsMessage() {
	std::cout << "Serial: received a Puls, but doesn't know what to do with it"
			<< std::endl;
}
