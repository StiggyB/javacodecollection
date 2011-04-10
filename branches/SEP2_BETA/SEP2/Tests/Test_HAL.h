/*
 * Test_HAL.h
 *
 *  Created on: 10.04.2011
 *      Author: MQR
 */

#ifndef TEST_HAL_H_
#define TEST_HAL_H_

#include "../Thread/HAWThread.h"
#include "../Controller/CoreController.h"

class Test_HAL : public thread::HAWThread {
public:
	Test_HAL();
	virtual ~Test_HAL();
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* TEST_HAL_H_ */
