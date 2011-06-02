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
 * (No logging of fault sources - should be fast)
 */
enum ExceptionType {
	WP_DISAPPEARED,
	WP_UNKOWN,
	SLIDE_FULL
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
