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


class Serial : public thread::HAWThread{
public:
	Serial(int numComPort, int choose, int debug);
	~Serial();
	int init(int numComPort, int choose, int debug );
	int send(void*, int lenByte);
	int receive(void*, int lenByte);

protected:
	virtual void execute(void*);
	virtual void shutdown();

private:
	int ser;
	int hasSettings;
	int comPort;
	int sender_receiver;
	int cnt;
};

#endif /* SERIAL_H_ */
