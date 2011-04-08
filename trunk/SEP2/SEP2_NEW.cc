#include <cstdlib>
#include <iostream>
#include "Controller/MasterThread.h"

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	if(ThreadCtl(_NTO_TCTL_IO,0)){
		std::cout << "error for IO Control" << std::endl;
		return EXIT_FAILURE;
	}
	MasterThread mt;
	mt.start(NULL);
	mt.join();
	mt.stopProcess();
	return EXIT_SUCCESS;
}
