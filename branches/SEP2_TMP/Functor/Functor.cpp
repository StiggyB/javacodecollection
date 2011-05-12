/*
 * Functor.cpp
 *
 *  Created on: 11.05.2011
 *      Author: Tell
 *
 *
 *     Functor for member-function pointer.
 */

#include "Functor.h"


template <typename R, class T>
Functor<R, T>::Functor(T& pMemObj, pMemFunc objFuncp)
:pMemObj(pMemObj), objFuncp(objFuncp) {
}

template <typename R, class T>
Functor<R, T>::~Functor() {
}

template <typename R, class T>
CallInterface* FunctorMaker(T& pMemObj, void (T::*objFuncp)()) {
	return new Functor<R, T> (pMemObj, objFuncp);
}

template <typename R, class T>
void Functor<R, T>::callback() {
	(pMemObj.*objFuncp)();
}

//TODO lookup what is necessary - state? / various params / ...
template <typename R, class T>
R Functor<R, T>::operator()() {
	return (pMemObj.*objFuncp) /*pointer on the calling class*/();
}


