/*
 * Functor.h
 *
 *  Created on: 11.05.2011
 *      Author: Tell
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_


template <typename R, class T >
class Functor {
public:

	Functor();
	~Functor();
	R operator()();
	R operator()(/*Param p1*/);

private:

	T* objFuncp;
	T& pMemObj;
};


#endif /* FUNCTOR_H_ */
