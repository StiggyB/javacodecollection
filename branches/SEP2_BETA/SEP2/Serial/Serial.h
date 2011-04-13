/*
 * Serial.h
 *
 *  Created on: 12.04.2011
 *      Author: user
 */


#ifndef SERIAL_H_
#define SERIAL_H_

#include "Serial.h"
#include "HAWThread.h"

#define SER1 "/dev/ser1"
#define SER2 "/dev/ser2"


class Serial : public thread::HAWThread{
public:
	Serial(int numComPort, int choose, int debug);
	~Serial();
	int init(int numComPort, int choose, int debug );
	int send(void*, int lenByte);
	int receive(void*, int lenByte);
	int ser;
	int hasSettings;
	int comPort;
	int sender_receiver;
	int cnt;

protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* SERIAL_H_ */
