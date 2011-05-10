
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
#include "Communication.h"

#define SYNC_SIGNAL 0
#define POCKET_TOP 1
#define POCKET_BOTTOM 2
#define BAND2_FREE 3

#define DEBUG_SERIAL

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
class Serial : public thread::HAWThread, public Communication{
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
	int send(void* data, int lenByte);
protected:

	void handlePulsMessage();
	void handleNormalMessage();
	/**
	 * Reads from Com Port.
	 * \param data a void pointer, contains the data container to store incoming data.
	 * \param lenByte an integer, the lengths of the data in bytes.
	 * \return an integer, 0 for okay -1 for error, -2 for no data received.
	 */
	int receive(void*, int lenByte);
	/**
	 * Will start the thread to do his work (send/receive), depending on modus.
	 * \param data a void pointer, in this case it will be ignored..no use. Pass a NULL to start the thread.
	 */
	virtual void execute(void* data);
	virtual void shutdown();
	void clean();
private:

	/**
	*  Sets up the Communication to IC and waits for Messages from it.
	*/
	bool settingUpSerial();

	int ack;
	int msg;
	int ser;
	int comPort;
	int sender_receiver;
	int cnt;
	bool hasSettings;
};

#endif /* SERIAL_H_ */
