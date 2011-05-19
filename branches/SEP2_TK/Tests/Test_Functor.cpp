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
	test_Functor_Without_Param();
	test_Functor_With_Param();
	test_FunctorMaker_Without_Param();
	test_FunctorMaker_With_Param();
}
void Test_Functor::shutdown() {

}

void Test_Functor::test_Functor_Without_Param() {
	Test_Functions t;
	Functor<Test_Functions, int, void*> func1(&t, &Test_Functions::test3);
	Functor<Test_Functions, int, void*>* tfunc1 = &func1;
	bool success = assert_equals("Functor1: ", tfunc1->call(NULL), FUNCTOR1);
	success_print(success);
}

void Test_Functor::test_Functor_With_Param() {
	Test_Functions t;
	Functor<Test_Functions, int, int> func2(&t, &Test_Functions::test4);
	Functor<Test_Functions, int, int>* tfunc2 = &func2;
	bool success = assert_equals("Functor2: ", tfunc2->call(0), FUNCTOR2);
	success_print(success);
}
void Test_Functor::test_FunctorMaker_Without_Param() {
	Test_Functions t;
	CallInterface<Test_Functions, int, void*>* func1 =
			FunctorMaker<Test_Functions, int, void*>::makeFunctor(&t, &Test_Functions::test3);
	bool success = assert_equals("FunctorMaker1: ", func1->call(NULL)+2, FUNCTOR3);
	success_print(success);
}
void Test_Functor::test_FunctorMaker_With_Param() {
	Test_Functions t;
	CallInterface<Test_Functions, int, int>* func2 =
			FunctorMaker<Test_Functions, int, int>::makeFunctor(&t, &Test_Functions::test4);
	bool success = assert_equals("FunctorMaker2: ", func2->call(2), FUNCTOR4);
	success_print(success);
}


bool Test_Functor::assert_equals(string function, int actual, const int expected) {
	if(actual != expected ) {
		test_print(function, actual, expected);
		return false;
	} else {
		test_print(function, actual, expected);
		return true;
	}
	return false;
}

void Test_Functor::test_print(string function, int actual, const int expected) {
	cout << "TEST " << function << " RESULT: " << actual << "=?" << expected << endl;
}

void Test_Functor::success_print(bool success) {
	if(success) {
		cout << "Successful" << endl;
	} else {
		cout << "Failure" << endl;
	}
}

