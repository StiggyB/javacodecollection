/*
 * Test.cpp
 *
 *  Created on: 12.05.2011
 *      Author: Tell
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
