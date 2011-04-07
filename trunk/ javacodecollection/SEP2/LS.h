/*
 * LS.h
 *
 *  Created on: 30.03.2011
 *      Author: Administrator
 */

#ifndef LS_H_
#define LS_H_

#include "HAWThread.h"

class LS: public thread::HAWThread {
public:
	LS();
	virtual ~LS();
};

#endif /* LS_H_ */
