/**
 * Test class for the Functor Pattern.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * This class executes test functions for the
 * Functor Pattern and the helper class FunctorMaker.
 * The functions test the pattern with generic return
 * value, generic parameter and without parameter (void*).
 *
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

class Test_Functor: public thread::HAWThread {
public:
	Test_Functor();
	virtual ~Test_Functor();
	virtual void execute(void*);
	virtual void shutdown();
	/**
	 * Function tests callbacks without return value.
	 * The called function prints "Functor2/4: Test successful.".
	 */
	void test_Functor_Without_Return();
	/**
	 * Function tests callbacks with return value.
	 * Assert_equals called and tests the return value.
	 */
	void test_Functor_With_Return();
	/**
	 * Function tests callbacks without return value.
	 * The called function prints "Functor2/4: Test successful.".
	 */
	void test_FunctorMaker_Without_Return();
	/**
	 * Function tests callbacks with return value.
	 * Assert_equals called and tests the return value.
	 */
	void test_FunctorMaker_With_Return();

	/**
	 * Compares actual and expected value and returns true if equals.
	 * \return true if equals, otherwise false
	 */
	bool assert_equals(string function, int actual, const int expected);
	/**
	 * Prints a test description and the return values from the test.
	 */
	void test_print(string function, int actual, const int expected);
	/**
	 * Prints "successful" if all tests are successful, otherwise "failed".
	 */
	void success_print(bool success);

private:
};

#endif /* TEST_FUNCTOR_H_ */
