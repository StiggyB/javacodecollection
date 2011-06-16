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
	test_Functor_Without_Return();
	test_Functor_With_Return();
	test_FunctorMaker_Without_Return();
	test_FunctorMaker_With_Return();
}
void Test_Functor::shutdown() {

}

void Test_Functor::test_Functor_Without_Return() {
	Test_Functions t;
	Functor<Test_Functions, void> func1(&t, &Test_Functions::test1);
	Functor<Test_Functions, void>* tfunc1 = &func1;
	tfunc1->call();
	bool success = assert_equals("Functor1: ", 0, FUNCTOR1);
	success_print(success);
}
void Test_Functor::test_Functor_With_Return() {
	Test_Functions t;
	Functor<Test_Functions, int> func2(&t, &Test_Functions::test2);
	Functor<Test_Functions, int>* tfunc2 = &func2;
	bool success = assert_equals("Functor2: ", tfunc2->call(), FUNCTOR2);
	success_print(success);
}
void Test_Functor::test_FunctorMaker_Without_Return() {
	Test_Functions t;
	CallInterface<Test_Functions, void>* func1 = FunctorMaker<Test_Functions,
			void>::makeFunctor(&t, &Test_Functions::test3);
	func1->call();
	bool success = assert_equals("FunctorMaker1: ", 0, FUNCTOR3 - 2);
	success_print(success);
}
void Test_Functor::test_FunctorMaker_With_Return() {
	Test_Functions t;
	CallInterface<Test_Functions, int>* func2 = FunctorMaker<Test_Functions,
			int>::makeFunctor(&t, &Test_Functions::test4);
	bool success = assert_equals("FunctorMaker2: ", func2->call(), FUNCTOR4);
	success_print(success);
}

bool Test_Functor::assert_equals(string function, int actual,
		const int expected) {
	if (actual != expected) {
		test_print(function, actual, expected);
		return false;
	} else {
		test_print(function, actual, expected);
		return true;
	}
	return false;
}

void Test_Functor::test_print(string function, int actual, const int expected) {
	cout << "TEST " << function << " RESULT: " << actual << "=?" << expected
			<< endl;
}

void Test_Functor::success_print(bool success) {
	if (success) {
		cout << "**************Test successful**************" << endl;
	} else {
		cout << "**************Test failure**************" << endl;
	}
}

