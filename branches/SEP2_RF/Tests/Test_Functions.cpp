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

void Test_Functions::test1() {
	cout << "Functor1: Test return" << endl;
}
int Test_Functions::test2() {
	return 1;
}
void Test_Functions::test3() {
	cout << "FunctorMaker1: Test return" << endl;
}
int Test_Functions::test4() {
	return 3;
}

