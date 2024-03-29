
#ifndef FUNCTORMAKER_H_
#define FUNCTORMAKER_H_
#include "CallInterface.h"

/**
 * Helper class FunctorMaker.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * This class is a Helper and makes
 * generic CallInterface function pointer.
 *
 */
template<typename T, typename R>
class FunctorMaker {

public:
	/**
	 * This method makes a generic function pointer from CallInterface
	 * The generics T, R, P represent the type from the object,
	 * the return type, the parameter type.
	 * If the parameter list is empty you should choose a "void*" with Null.
	 * \param pMemObj is a pointer on a instance from type T.
	 * \param objFuncp is a function pointer from
	 * 	type T with param P and return type R.
	 * \return Function pointer from type CallInterface<T, R, P>.
	 */
	static CallInterface<T, R>* makeFunctor(T* pMemObj, R(T::*objFuncp)()) {
		return new Functor<T, R>(pMemObj, objFuncp);
	}
};

#endif /* FUNCTORMAKER_H_ */
