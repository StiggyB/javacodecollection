/**
 * Interface for the Hardware Abstraction Layer.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 *This will test the serial interface.
 *depend on the modi. To do a success test, one thread with modi 1 and
 *the other with modi 0. two threads witch the same modi wont work.
 *
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "Serial.h"
#include "../Thread/HAWThread.h"


class Serial : public thread::HAWThread{
public:
	/**
	 * Constructor with integrated initialization
	 * \param numComPort an integer, specifying the Com Port.
	 * \param modi an integer, 0 for send SYN, get ACK; 1 for get SYN, send ACK
	 */
	Serial(int numComPort, int modi, int debug);
	~Serial();

protected:
	/**
	 * writes on Com Port
	 * \param data a void pointer, contains the data to send
	 * \param data an integer, lengths in bytes of data
	 * \return an integer, 0 for okay, -1 for error.
	 */
	int send(void* data, int lenByte);
	/**
	 * Reads from com Port
	 * \param data a void pointer, contains the data container to store incomming data
	 * \return an integer, 0 for okay -1 for error, -2 for no data received
	 */
	int receive(void*, int lenByte);
	/**
	 * will start the thread to do his work (send/receive), depend on modi
	 * \param data a void pointer, in this case it will ignored..no use
	 */
	virtual void execute(void* data);
	virtual void shutdown();

private:
	int ser;
	int hasSettings;
	int comPort;
	int sender_receiver;
	int cnt;
};

#endif /* SERIAL_H_ */
