/*
 * Handler.h
 *
 *  Created on: 02.06.2011
 *      Author: Tell
 */

#ifndef EXCEPTIONHANDLER_H_
#define EXCEPTIONHANDLER_H_


#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "../Serial/Serial.h"
#include "Communication.h"

/**
 * Faults while normal running in the Festo System.
 */
enum ExceptionType {
	WP_DISAPPEARED_B1,
	WP_UNKOWN_B1,
	WP_DISAPPEARED_B3,
	WP_UNKOWN_B3,
	WP_DISAPPEARED_B7,
	WP_UNKOWN_B7,
	SLIDE_FULL_B6
	/*...*/
};

class ExceptionHandler : public thread::HAWThread, public Communication {
public:
	ExceptionHandler();
	~ExceptionHandler();
	void handleException(ExceptionType exception);
	void logException();
protected:
    virtual void execute(void*);
    virtual void shutdown();
    virtual void handlePulsMessage();
    virtual void handleNormalMessage();

private:
    HALCore* h;
    Lampen* l;


};


#endif /* EXCEPTIONHANDLER_H_ */
