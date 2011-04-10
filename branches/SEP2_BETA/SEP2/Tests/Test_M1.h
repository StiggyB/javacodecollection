/*
 * Test_M1.h
 *
 *  Created on: 10.04.2011
 *      Author: MQR
 */

#ifndef TEST_M1_H_
#define TEST_M1_H_

#include "../Thread/HAWThread.h"
#include "../Controller/CoreController.h"

class Test_M1 : public thread::HAWThread {
public:
	Test_M1();
	virtual ~Test_M1();
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* TEST_M1_H_ */
