/*
 * Functor.h
 *
 *  Created on: 11.05.2011
 *      Author: Tell
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "CallInterface.h"

template <typename R, class T >
class Functor : public call::CallInterface {
public:
	//Type definition: pointer to a member- function
	typedef void (T:: *pMemFunc)();

	CallInterface* FunctorMaker(T& pMemObj, void (T::*objFuncp)());
	virtual void callback();
	Functor(T& pMemObj, pMemFunc objFuncp);
	~Functor();
	R operator()();
	R operator()(int i/*Param p1*/);

private:

	pMemFunc objFuncp;
	T& pMemObj;
};


#endif /* FUNCTOR_H_ */
