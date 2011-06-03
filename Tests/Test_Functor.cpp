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
	Functor<Test_Functions, int> func1(&t, &Test_Functions::test1);
	Functor<Test_Functions, int>* tfunc1 = &func1;
	bool success = assert_equals("Functor1: ", tfunc1->call(), FUNCTOR1);
	success_print(success);
}
void Test_Functor::test_Functor_With_Param() {
	Test_Functions t;
	Functor<Test_Functions, int> func2(&t, &Test_Functions::test1);
	Functor<Test_Functions, int>* tfunc2 = &func2;
	bool success = assert_equals("Functor2: ", tfunc2->call()+1, FUNCTOR2);
	success_print(success);
}
void Test_Functor::test_FunctorMaker_Without_Param() {
	Test_Functions t;
	CallInterface<Test_Functions, int>* func1 =
			FunctorMaker<Test_Functions, int>::makeFunctor(&t, &Test_Functions::test1);
	bool success = assert_equals("FunctorMaker1: ", func1->call()+2, FUNCTOR3);
	success_print(success);
}
void Test_Functor::test_FunctorMaker_With_Param() {
	Test_Functions t;
	CallInterface<Test_Functions, int>* func2 =
			FunctorMaker<Test_Functions, int>::makeFunctor(&t, &Test_Functions::test1);
	bool success = assert_equals("FunctorMaker2: ", func2->call()+3, FUNCTOR4);
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

