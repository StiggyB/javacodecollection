/*
 * Functor.cpp
 *
 *  Created on: 11.05.2011
 *      Author: Tell
 */

template <typename R, class T>
class Functor {

	//TODO Callinterface old way to impl. a Functor?

private:

	Sensor sen;

public:

	Functor();

	//TODO lookup what is necessary - state? / various params / ...

	R operator()() {
		return (sen/*pointer on the calling class*/);
	}

	R operator(/*Param p1*/);

};
