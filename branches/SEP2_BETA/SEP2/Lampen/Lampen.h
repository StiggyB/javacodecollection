/*
 * Lampen.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef LAMPEN_H_
#define LAMPEN_H_

#include <unistd.h>
#include "../Controller/CoreController.h"
#include "../Thread/HAWThread.h"

class Lampen : public thread::HAWThread{
public:
	Lampen();
	virtual ~Lampen();
	void flash(int time, Color color);
	void flash(int time, int duration, Color col);
	void removeLight(Color col);
	void addLight(Color col);
	void shine(Color col);
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* LAMPEN_H_ */
