/*
 * Test_IRQ.h
 *
 *  Created on: 12.04.2011
 *      Author: Administrator
 */

#ifndef TEST_IRQ_H_
#define TEST_IRQ_H_

#include "../Thread/HAWThread.h"
#include "../Controller/CoreController.h"

class Test_IRQ : public thread::HAWThread{
public:
	Test_IRQ();
	virtual ~Test_IRQ();
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* TEST_IRQ_H_ */
