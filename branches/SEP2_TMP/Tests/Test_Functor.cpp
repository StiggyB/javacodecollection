/*
 * Test_Functor.cpp
 *
 *  Created on: 12.05.2011
 *      Author: aax691
 */

#include "Test_Functor.h"


Test_Functor::Test_Functor() {

}

Test_Functor::~Test_Functor() {

}

void Test_Functor::execute(void*) {
	test_functor_triv();
}

void Test_Functor::shutdown() {

}

void Test_Functor::test_function() {
	cout << "Memberfunction is called" << endl;
}

void Test_Functor::test_functor() {
	Functor<void , Sensor> cmd1(sen, &Sensor::shutdown());
	cmd1();
}

void Test_Functor::test_functor_triv() {
	Functor<void, Test_Functor> cmd2(this, &Test_Functor::test_function);
	cmd2();
}
