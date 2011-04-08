/*
 * Lampen.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef LAMPEN_H_
#define LAMPEN_H_

#include <unistd.h>
#include "../HAL/HAL.h"
#include "../Thread/HAWThread.h"

class Lampen : public thread::HAWThread{
public:
	Lampen();
	virtual ~Lampen();
	void flash(int time, HAL::Color color);
	void flash(int time, int duration, HAL::Color col);
	void prepare();
	void lampen_M1();
	void removeLight(HAL::Color col);
	void addLight(HAL::Color col);
	void shine(HAL::Color col);

	//tests:
	void test();
	void test_HAL();
	void test_HAL_Lampen_write_reset();
	void test_HAL_CheckVal();
	void testIRQ();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	HAL* h;
};

#endif /* LAMPEN_H_ */
