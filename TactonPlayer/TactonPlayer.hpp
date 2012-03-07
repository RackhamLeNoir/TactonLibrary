#include "Tacton.hpp"

#include <ArduinoSerial\Serial.hpp>

class TactonPlayer
{
	public:
			__declspec(dllexport) TactonPlayer(const char *port = "COM5");
			__declspec(dllexport) ~TactonPlayer();

			//set the timestamp to 0, and watch for scheduled tactons
			void __declspec(dllexport) start();
			//stop watching scheduled tactons, and erase registered tactons
			void __declspec(dllexport) stop();

			//register a tacton
			__declspec(dllexport) void regist(const Tacton &t);
			//register a list of tactons in a file, returns the number of tactons loaded
			__declspec(dllexport) unsigned int registFile(char *filename);

			//play a registered tacton
			__declspec(dllexport) void play(unsigned char index);
			//play a specified tacton
			__declspec(dllexport) void play(const Tacton &t);
			//schedule the play of a registered tacton
			__declspec(dllexport) void schedule(unsigned char index, unsigned long timestamp);

			//read on the serial port
			__declspec(dllexport) void debugRead(char *res, int nb) const;

private:
		Serial *_comport;
};
