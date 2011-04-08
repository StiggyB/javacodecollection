/*
 * Sensor.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef SENSOR_H_
#define SENSOR_H_


#include "../HAL/HAL.h"
#include "../Thread/HAWThread.h"

extern volatile struct sigevent event;
extern const struct sigevent *eventptr;

class Sensor : public thread::HAWThread {
public:
	Sensor();
	virtual ~Sensor();
private:
	int interruptId, chid, coid;
	struct _pulse pulse;
	void handlePulseMessages();
	void activateInterrupts();
	void connectToHAL();
	HAL *h;
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* SENSOR_H_ */
