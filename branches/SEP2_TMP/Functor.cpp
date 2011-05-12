/*
 * Functor.cpp
 *
 *  Created on: 11.05.2011
 *      Author: Tell
 *
 *
 *     Functor for member-function pointer.
 */

	//TODO Callinterface old way to impl. a Functor?


Functor<R, T>::Functor() {

}

Functor<R, T>::~Functor() {

}

Functor<R, T>::Functor(T& pMemObj, T objFuncp)
:pMemObj(pMemObj), objFuncp(objFuncp) {
}

//TODO lookup what is necessary - state? / various params / ...

R Functor<R, T>::operator()() {
	return ((*objFuncp).*pMemObj /*pointer on the calling class*/)();
}

R Functor<R, T>::operator()(/*Param p1*/) {

}

