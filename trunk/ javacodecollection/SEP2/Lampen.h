/*
 * Lampen.h
 *
 *  Created on: 30.03.2011
 *      Author: Administrator
 */

#ifndef LAMPEN_H_
#define LAMPEN_H_

#include <unistd.h>
#include "HAWThread.h"
#include <HAL.h>

class Lampen : public thread::HAWThread {

public:
	Lampen();
	virtual ~Lampen();
	enum Color {RED,GREEN,YELLOW,OFF};
	void flash(int time,Color color);
	void flash(int time,int duration,Color col);
	void shine(Color col);
	void shine(int color);
	void test();
	void addLight(Color col);
	int getColorCode(Color col);
	void removeLight(Color col);
	void test_HAL();
	HAL h;
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* LAMPEN_H_ */
