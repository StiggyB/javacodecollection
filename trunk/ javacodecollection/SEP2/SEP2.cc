#include <cstdlib>
#include <iostream>
#include <Lampen.h>
#include "HW_test.h"

int main(int argc, char *argv[]) {
		#ifdef SIMULATION
		cout << "Simulation aktiv" << endl;
		cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen." << endl;
		IOaccess_open(); // Baue die Verbindung zur Simulation auf
		#endif
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	HW_test l;
	l= HW_test();
	l.start(NULL);
	l.join();
	cout << "Versuch wird beendet" << endl;

#ifdef SIMULATION
	IOaccess_close(); // Schließe die Verbindung zur Simulation
#endif
	return EXIT_SUCCESS;
}
