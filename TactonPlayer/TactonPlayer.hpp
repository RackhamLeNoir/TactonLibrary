#ifndef _TACTONPLAYER_
#define _TACTONPLAYER_

#include "Tacton.hpp"

#include <Serial.hpp>

#ifdef _WIN32
	#ifdef _WINDLL
		#define EXPORTED __declspec(dllexport)
	#else 
		#define EXPORTED __declspec(dllimport)
	#endif
#else
	#define EXPORTED
#endif

class EXPORTED TactonPlayer
{
	public:
			TactonPlayer(const char *port = "COM5");
			~TactonPlayer();

			//set the timestamp to 0, and watch for scheduled tactons
			void start();
			//stop watching scheduled tactons, and erase registered tactons
			void stop();

			//register a tacton
			void regist(const Tacton &t);
			//register a list of tactons in a file, returns the number of tactons loaded
			unsigned int registFile(char *filename);

			//play a registered tacton
			void play(unsigned char index);
			//play a specified tacton
			void play(const Tacton &t);
			//schedule the play of a registered tacton
			void schedule(unsigned char index, unsigned long timestamp);

			//sets an amplitude for each vibrator
			void setAmplitudes(unsigned char nbtactors, unsigned char *amplitudes);
			//sets a frequency for all vibrator
			void setFrequency(unsigned int frequency);
			//stop any vibration
			void stopBuzz();

			//sets a vibration on a virtual circle around 4 vibrators
			void playAngle(unsigned int angle);

			//plays an animation alterning a series of angles
			void playAngleSequence(unsigned char nbangles, unsigned int frameduration, unsigned int nbframes, unsigned int *angles);

			//read on the serial port
			void debugRead(char *res, int nb) const;

private:
		Serial *_comport;
};

#endif
