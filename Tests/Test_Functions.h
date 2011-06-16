/**
 * Test Functions.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * This class provides some test
 * functions for the Functor Pattern.
 *
 */

#ifndef TEST_H_
#define TEST_H_
#include <iostream>

class Test_Functions {
public:
	/**
	 * Test function without return value.
	 * Prints "Functor2: Test successful." when called.
	 */
	void test1();
	/**
	 * Test function with return value.
	 * \return test value 0
	 */
	int test2();
};

#endif /* TEST_H_ */
