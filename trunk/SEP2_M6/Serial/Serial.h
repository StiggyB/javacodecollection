
#ifndef SERIAL_H_
#define SERIAL_H_


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include "../Thread/HAWThread.h"
#include "../Thread/Singleton_T.h"
#include "../Controller/Communication.h"
#include "../Tests/test.h"
#include "../Thread/Mutex.h"
#include "../Functor/Callinterface.h"
#include "../Functor/CallBackThrower.h"
#include "../Timer/Timer.h"



enum msgType {
	ACK,
	INIT_SERIAL,
					/* Machine Info */
	REQUEST_FREE,
	REQUEST_FREE_ACK,
	MACHINE2_FREE,
	MACHINE2_FREE_ACK,
					/* Puck Info */
	PUCK_ARRIVED,
	POCKET,
	ACK_POCKET,
	NO_POCKET,
	ACK_NO_POCKET,
	/* Port C */
	E_STOP_PUSHED,
	E_STOP_PULLED,
	STOP_BUTTON,
	START_BUTTON,
	RESET_BUTTON,
					/* Serial communication */
	SYNC,
	SYNC_SIGNAL,
	ACK_SYNC_SIGNAL,
	ACK_INIT_SERIAL,
					/* Error state for both machines */
	ERROR_OCCURED,
	ERROR_SOLVED
};


#define DEBUG_SERIAL

#define T_SYNC_ERROR 2000
#define T_SYNC_SEND 1000

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
class Serial : public thread::HAWThread, public Communication,public Singleton_T<Serial>{
	friend class Singleton_T<Serial>;
public:
	/**
	 * Constructor with integrated initialization.
	 * \param numComPort an integer, specifying the Com Port.
	 * \param debug a bool, indicates debugging mode.
	 */
	//Serial(int numComPort, bool debug);
	Serial();
	~Serial();
	void init(int numComPort, bool debug);
	/**
	 * Writes on Com Port.
	 * \param data a void pointer, contains the data which will be send.
	 * \param lenByte an integer, the lengths of the data in bytes.
	 * \return an integer, 0 for okay, -1 for error.
	 */
	int send(int data, int lenByte);

protected:

	void handlePulsMessage();
	void handleNormalMessage();
	/**
	 * Reads from Com Port.
	 * \param data a void pointer, contains the data container to store incoming data.
	 * \param lenByte an integer, the lengths of the data in bytes.
	 * \return an integer, 0 for okay -1 for error, -2 for no data received.
	 */
	int receive(unsigned int* data, int lenByte);
	/**
	 * Will start the thread to do his work (send/receive), depending on modus.
	 * \param data a void pointer, in this case it will be ignored..no use. Pass a NULL to start the thread.
	 */
	virtual void execute(void* data);
	virtual void shutdown();
	void clean();
private:
	CallInterface<Serial, void>* check_ack;
	CallInterface<Serial, void>* check_init_ack;
	CallInterface<Serial, void>* sync_send;
	CallInterface<Serial, void>* sync_error;
	Timer* timer;
	void checkAck();
	void checkInit();
	void syncError();
	void syncSend();
	void syncReceive();
	void syncRestart();
	int sync_TID;
	int checkAck_TID;
	int sync_send_TID;
	bool getSync;
	bool getAck;
	unsigned int ack;
	unsigned int msg;
	int ser;
	int comPort;
	int sender_receiver;
	int cnt;
	bool hasSettings;
	CommunicatorType receiver;
	Mutex locker;
};

#endif /* SERIAL_H_ */
