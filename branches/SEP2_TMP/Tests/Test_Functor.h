/*
 * Test_Functor.h
 *
 *  Created on: 12.05.2011
 *      Author: aax691
 */

#ifndef TEST_FUNCTOR_H_
#define TEST_FUNCTOR_H_

#include "Timer.h"
#include "Functor.h"
#include "../Controller/Sensor.h"
#include "../Thread/HAWThread.h"

class Test_Functor : public thread::HAWThread {
public:
	Test_Functor();
	~Test_Functor();
	virtual void execute(void*);
	virtual void shutdown();
	void test_function();
	void test_functor();
	void test_functor_triv();

private:
	Sensor sen;
};

#endif /* TEST_FUNCTOR_H_ */
