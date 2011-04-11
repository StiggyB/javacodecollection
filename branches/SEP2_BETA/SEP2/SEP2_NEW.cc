#include <cstdlib>
#include <iostream>
#include "Controller/CoreController.h"

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;

#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen."
	<< endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

	perror("PERROR: hello again :D");
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
		return EXIT_FAILURE;
	}
	CoreController* mt = CoreController::getInstance();
	(*mt).start(NULL);
	(*mt).join();
	(*mt).stopProcess();

	cout << "Finishing Test" << endl;

#ifdef SIMULATION
	IOaccess_close(); // Schließe die Verbindung zur Simulation
#endif

	return EXIT_SUCCESS;
}
