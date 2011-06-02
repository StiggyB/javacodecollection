/*
 * Handler.h
 *
 *  Created on: 02.06.2011
 *      Author: Tell
 */

#ifndef EXCEPTIONHANDLER_H_
#define EXCEPTIONHANDLER_H_

/**
 * Faults while normal running in the Festo System.
 * (No logging of fault sources - should be fast)
 */
enum Faults {
	WP_DISAPPEARED,
	WP_UNKOWN,
	SLIDE_FULL
};

class ExceptionHandler {// : public thread::HAWThread, public Communication {
public:


private:


};


#endif /* EXCEPTIONHANDLER_H_ */
