
#ifndef LAMPEN_H_
#define LAMPEN_H_

#include <unistd.h>
#include "../HAL/HALCore.h"
#include "../Thread/HAWThread.h"
#include "../Controller/Communication.h"
/**
 * Light Control
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Provides some possibilities to activate the lights.
 *
 * Inherits: HAWThread, Communication
 */
class Lampen : public thread::HAWThread{
public:
	Lampen();
	virtual ~Lampen();
	/**
	 * Flashes a specified light until stopped.
	 * \param period an integer, half of the flash period.
	 * \param color Color of the Light which should flash.
	 */
	void flash(int period, Color color);
	/**
	 * Flashes a specified light until duration expired.
	 * \param period an integer, half of the flash period.
	 * \param duration an integer, specifies how long the light should flash
	 * \param col Color of the Light which should flash.
	 */
	void flash(int period, int duration, Color col);
	/**
	 * Removes a certain light.
	 * \param col specifies the color of the light.
	 */
	void removeLight(Color col);
	/**
	 * Adds a certain light.
	 * \param col specifies the color of the light.
	 */
	void addLight(Color col);
	/**
	 * Adds a certain light.
	 * Equals void addLight(Color col);
	 * \param col specifies the color of the light.
	 */
	void shine(Color col);
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	/**
	 * Boolean to ensure the flashing of the Light.
	 */
	bool running;
	/**
	 * Mutex to ensure threadsafety for lampen thread.
	 */
	Mutex mlight;

	/**
	 * contains information regarding the lights
	 */
	typedef struct lights{
		Color col;
		/**
		 * Time to next change.
		 */
		int time;
		/**
		 * Period for changing between on/off.
		 */
		int period;
		/**
		 * Total duration for the light.
		 * "-1" for unlimited time.
		 */
		int duration;
		/**
		 * True if currently used,
		 * false if unused.
		 */
		bool activ;
		/**
		 * Shows the actual state of the light.
		 * True if currently flashed, false if not.
		 */
		bool on;
	} Lights;

	/**
	 * Array to all lights, containing information about the actual status.
	 */
	Lights array[3];
	/**
	 * Pointer to the HALCore
	 */
	HALCore *h;

	/**
	 * Calculates the bits for the lights.
	 * \returns the calculated light bits
	 */
	int calcLights();
	/**
	 * Calculates the time for the next sleep within the executing loop.
	 * \returns an integer, the time in ms, the lampen-thread will sleep next, but maximal 1 second.
	 */
	int calcTime();
	/**
	 * Gets the next time the thread should be sleeping.
	 * \returns the time when the next light should be changed
	 */
	int getNextTime();
	/**
	 * Calculates which of these values is the minimal.
	 * \param a an integer, which should be compared to the other two
	 * \param b an integer, which should be compared to the other two
	 * \param c an integer, which should be compared to the other two
	 * \returns an integer, the minimal value
	 */
	int getMin(int a, int b, int c);
	/**
	 * Gets the active status of the Color.
	 * \param col the Color which status you want to know
	 * \returns a boolean, true if the Color is activ
	 */
	bool isActiv(Color col);
	/**
	 * Removes a color from the to active list.
	 * \param col the Color which will be deactivated
	 */
	void removeTime(Color col);
	/**
	 * Removes all time information from all colors.
	 */
	void removeAllTime();
	/**
	 * Gets if the light color has the specified time.
	 * \param col the light color which will be checked
	 * \param time the time which should be checked
	 */
	bool hasTime(Color col, int time);
	/**
	 * Adds the time for a specified light color with unlimited duration.
	 * \param col the light color which will be set
	 * \param period the period for the light, "-1" for unlimited
	 */
	void addTime(Color col, int period);
	/**
	 * Adds the time for a specified light color.
	 * \param col the light color which will be set
	 * \param period the period for the light, "-1"  for unlimited
	 * \param duration the maximal duration of the light, "-1" for unlimited
	 */
	void addTime(Color col, int period, int duration);
	/**
	 * Sets the time for a specified light color.
	 * \param col the light color which will be set
	 * \param period the period for the light, "-1" for unlimited
	 * \param duration the maximal duration of the light, "-1" for unlimited
	 * \param activity if the light is used and activated
	 * \param status the current status for the light, false for not flashed.
	 */
	void setTime(Color col,int period,int duration, bool activity, bool status);
};

#endif /* LAMPEN_H_ */
