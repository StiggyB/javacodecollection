/*
 * Test_Callback.cpp
 *
 *  Created on: 11.05.2011
 *      Author: Tell
 */

//TODO test some calls over the functor wrapper from the sensor.



struct Test_Callback {

	void operator() (int i, double d) {
		cout << "Test_Callback::operator()(" << i << ", " << d <<") called." << endl;
	}
};

int main() {

	Test_Callback cb;
	Functor<void, Sensor> cmd(f);
	cmd(4, 4.5);
}

