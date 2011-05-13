/*
 * Error_State_Lamp.h
 *
 *  Created on: 12.05.2011
 *      Author: user
 */

#ifndef ERROR_STATE_LAMP_H_
#define ERROR_STATE_LAMP_H_

#include "../Thread/HAWThread.h"
#include "../Controller/Communication.h"
#include "../Controller/CoreController.h"

class Error_State_Lamp  : public thread::HAWThread {
public:
	Error_State_Lamp();
	virtual ~Error_State_Lamp();
	virtual void execute(void* data);
	virtual void shutdown();
	void fast_blink();
	void slow_blink();
private:
	CoreController *cc;
	volatile int time;
};

#endif /* ERROR_STATE_LAMP_H_ */
