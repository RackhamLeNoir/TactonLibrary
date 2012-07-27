#ifndef _TACTONPLAYERPRECISENEW_
#define _TACTONPLAYERPRECISENEW_

#include "Arduino.h"

#include <TactonPlayer.h>

class TactonPlayerPreciseNew: public TactonPlayer
{
	public:
		TactonPlayerPreciseNew(byte nbtactors, byte *pins, byte pwmPin);
		
		//Same frequency for all the vibrators, different amplitude.
		//Vibrates until stop
		void buzz(unsigned int frequency, byte nbtactors, byte *amplitudes);

		//Stop any vibration
		void stop();
		
		//8bits pattern => max 8 tactors, change type if using more
		void beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude);

	private:
		void init() const;		
		void setFrequency(unsigned int frequency);
		//void setDuration(unsigned long duration);
		//void setAmplitude(byte amplitude);
		//void setPattern(byte pattern);

		byte _pwmPin;
};

#endif
