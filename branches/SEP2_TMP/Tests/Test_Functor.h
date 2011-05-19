/*
 * Test_Functor.h
 *
 *  Created on: 12.05.2011
 *      Author: aax691
 */

#ifndef TEST_FUNCTOR_H_
#define TEST_FUNCTOR_H_

#include <iostream>
#include <stdio.h>
#include <string>

#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "../Functor/CallInterface.h"
#include "HAWThread.h"
#include "Test_Functions.h"

enum ExpectedValues {
	FUNCTOR1, FUNCTOR2, FUNCTOR3, FUNCTOR4
};

class Test_Functor : public thread::HAWThread {
public:
	Test_Functor();
	virtual ~Test_Functor();
	virtual void execute(void*);
	virtual void shutdown();
	void test_Functor_Without_Param();
	void test_Functor_With_Param();
	void test_FunctorMaker_Without_Param();
	void test_FunctorMaker_With_Param();

	bool assert_equals(string function, int actual, const int expected);
	void test_print(string function, int actual, const int expected);
	void success_print(bool success);

private:
};

#endif /* TEST_FUNCTOR_H_ */
