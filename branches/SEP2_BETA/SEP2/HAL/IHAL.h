/*
 * IHAL.h
 *
 *  Created on: 09.04.2011
 *      Author: MQR
 */

#ifndef IHAL_H_
#define IHAL_H_

//Farben Enum
enum Color {
	RED, GREEN, YELLOW, OFF
};

class IHAL {
public:
	virtual int read(int dir)=0;
	virtual bool isInput(int dir)=0;
	virtual bool isOutput(int dir)=0;
	virtual int write(int dir, int value)=0;
	virtual int reset(int dir, int value)=0;

	virtual bool engineStart(int direction)=0;
	virtual bool openSwitch()=0;
	virtual bool closeSwitch()=0;
	virtual bool setSwitchDirection(bool dir)=0;
	virtual bool engineReset()=0;
	virtual bool engineStop()=0;
	virtual bool engineContinue()=0;
	virtual bool engineRight()=0;
	virtual bool engineLeft()=0;
	virtual bool engineSlowSpeed()=0;
	virtual bool engineNormalSpeed()=0;
	virtual bool engineStopped()=0;
	virtual bool engineSlowSpeed(int dir)=0;
	virtual bool engineSpeed(bool slow)=0;
	virtual bool engineSlowLeft()=0;
	virtual bool engineSlowRight()=0;
	virtual bool attachISR(void * arg)=0;
	virtual int getSetInterrupt()=0;
	virtual int getInterrupt()=0;
	virtual bool resetAllOutPut()=0;
	virtual bool removeLight(Color col)=0;
	virtual bool addLight(Color col)=0;
	virtual bool shine(Color col)=0;

	IHAL();
	virtual ~IHAL();
};

#endif /* IHAL_H_ */
