#ifndef SENSOR_H_
#define SENSOR_H_

#include <unistd.h>
#include <stdio.h>
#include "Thread_HAWThread.h"
#include "HAL.h"

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
/*
 * sensor muss sich bei der HAL anmelden und hallo sagen -> channel createn und event hinzufügen... :D
 */

#endif /* SENSOR_H_ */
