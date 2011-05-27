/*
 * FunctorMaker.h
 *
 *  Created on: 17.05.2011
 *      Author: Tell
 */

#ifndef FUNCTORMAKER_H_
#define FUNCTORMAKER_H_
#include "CallInterface.h"

template<typename T,typename R, typename P>
class FunctorMaker {

public:
	static CallInterface<T, R, P>* makeFunctor(T* pMemObj, R(T:: *objFuncp)(P)) {
		return new Functor<T, R, P>(pMemObj, objFuncp);
	}
};

#endif /* FUNCTORMAKER_H_ */
