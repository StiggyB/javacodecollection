/*
 * Test_Lights.h
 *
 *  Created on: 17.05.2011
 *      Author: aax691
 */

#ifndef TEST_LIGHTS_H_
#define TEST_LIGHTS_H_

#include "../Thread/HAWThread.h"
#include "../HAL/Lampen.h"
#include "../HAL/HALCore.h"

class Test_Lights : public thread::HAWThread{
public:
	Test_Lights();
	virtual ~Test_Lights();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	HALCore *h;
	Lampen *l;
};

#endif /* TEST_LIGHTS_H_ */
