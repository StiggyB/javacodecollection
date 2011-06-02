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

#include "Test_Functions.h"
using namespace std;

void Test_Functions::test(const char* text) {
	cout << text << endl;
}

void Test_Functions::test2() {
	cout << "test" << endl;
}

int Test_Functions::test3(void* val) {
	return 0;
}

int Test_Functions::test4(int a) {
	return a+1;
}
int Test_Functions::test5(int a, int b) {
	return a+b;
}
