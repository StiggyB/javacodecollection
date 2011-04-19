/**
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 */


#include <cstdlib>
#include <iostream>
#include "Controller/StartThread.h"
#include "Controller/InterruptController.h"
#include "Controller/CoreController.h"
#include "HAL/HAL.h"

void stopController();

/**
 * starting the program!
 */

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	atexit(stopController);
	/**
	 *if simulation is wanted, than you'll get it ;)
	 */
#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen."
	<< endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

	/**
	 * getting IO Control for QNX
	 */
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
		return EXIT_FAILURE;
	}

	/**
	 * starting the CoreController
	 */
	StartThread st;
	st.start(NULL);
	st.join();
	/**
	 * clean up
	 */
	st.stopProcess();

	cout << "Finishing Test" << endl;

#ifdef SIMULATION
	IOaccess_close(); // Schließe die Verbindung zur Simulation
#endif

	return EXIT_SUCCESS;
}

/**
 * stops all Controller
 */
void stopController(){
	CoreController::deleteInstance();
	InterruptController::deleteInstance();
	HAL::deleteInstance();
}
