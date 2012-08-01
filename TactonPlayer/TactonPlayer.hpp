#include "Tacton.hpp"

#ifdef __MACOSX__
#include <Serial.hpp>
#define EXPORTED
#else
#include <ArduinoSerial\Serial.hpp>
#define EXPORTED __declspec(dllexport)
#endif

class TactonPlayer
{
	public:
			EXPORTED TactonPlayer(const char *port = "COM5");
			EXPORTED ~TactonPlayer();

			//set the timestamp to 0, and watch for scheduled tactons
			EXPORTED void start();
			//stop watching scheduled tactons, and erase registered tactons
			EXPORTED void stop();

			//register a tacton
			EXPORTED void regist(const Tacton &t);
			//register a list of tactons in a file, returns the number of tactons loaded
			EXPORTED unsigned int registFile(char *filename);

			//play a registered tacton
			EXPORTED void play(unsigned char index);
			//play a specified tacton
			EXPORTED void play(const Tacton &t);
			//schedule the play of a registered tacton
			EXPORTED void schedule(unsigned char index, unsigned long timestamp);

			//sets an amplitude for each vibrator
			EXPORTED void setAmplitudes(unsigned int nbtactors, unsigned char *amplitudes);
			//sets a frequency for all vibrator
			EXPORTED void setFrequency(unsigned int frequency);
			//stop any vibration
			EXPORTED void stopBuzz();

			//read on the serial port
			EXPORTED void debugRead(char *res, int nb) const;

private:
		Serial *_comport;
};
