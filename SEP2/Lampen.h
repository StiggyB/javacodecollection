#ifndef LAMPEN_H_
#define LAMPEN_H_

#include <unistd.h>
#include "Thread_HAWThread.h"
#include "HAL.h"

class Lampen : public thread::HAWThread {

public:
	Lampen();
	virtual ~Lampen();
	enum Color {RED,GREEN,YELLOW,OFF};
	void flash(int time,Color color);
	void flash(int time,int duration,Color col);
	void shine(Color col);
	void shine(int color);
	void prepare();
	void addLight(Color col);
	void lampen_M1();
	int getColorCode(Color col);
	void removeLight(Color col);

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
