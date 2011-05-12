/*
 * FunctorSimple.cpp
 *
 *  Created on: 12.05.2011
 *      Author: Tell
 */

#include "FunctorSimple.h"

template<class T>
FunctorSimple<T>::FunctorSimple(T& pMemObj, T objFuncp)
:pMemObj(pMemObj),
 objFuncp(objFuncp) {
}

template<class T>
FunctorSimple<T>::~FunctorSimple() {

}

template<class T>
void FunctorSimple<T>::operator()() {
		return ((*objFuncp).*pMemObj /*pointer on the calling class*/);
}

