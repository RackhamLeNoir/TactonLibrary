#include "Tacton.hpp"

#include "Serial.hpp"

class TactonPlayer
{
	public:
			__declspec(dllexport) TactonPlayer(char *port = "COM5");
			__declspec(dllexport) ~TactonPlayer();

			//set the timestamp to 0, and watch for scheduled tactons
			void __declspec(dllexport) start();
			//stop watching scheduled tactons, and erase registered tactons
			void __declspec(dllexport) stop();

			//register a tacton
			void __declspec(dllexport) regist(const Tacton &t);
			//register a list of tactons in a file, returns the number of tactons loaded
			unsigned int __declspec(dllexport) registFile(char *filename);

			//play a registered tacton
			void __declspec(dllexport) play(unsigned char index);
			//play a specified tacton
			void __declspec(dllexport) play(const Tacton &t);
			//schedule the play of a registered tacton
			void __declspec(dllexport) schedule(unsigned char index, unsigned long timestamp);

private:
		Serial *_comport;
};
