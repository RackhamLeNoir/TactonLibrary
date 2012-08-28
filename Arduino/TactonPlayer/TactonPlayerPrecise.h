#ifndef _TACTONPLAYERPRECISE_
#define _TACTONPLAYERPRECISE_

#include "Arduino.h"

#include <TactonPlayer.h>

class TactonPlayerPrecise: public TactonPlayer
{
	public:
		TactonPlayerPrecise(byte nbtactors, byte *pins);
				
		//8bits pattern => max 8 tactors, change type if using more
		void beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude);
		
		inline static void tooglePins();
		inline static void turnOnPins();
		inline static void turnOffPins();

	private:
		void init() const;		
		void setFrequency(unsigned int frequency);
		void setDuration(unsigned long duration);
		void setAmplitude(byte amplitude);
		void setPattern(byte pattern);

		static uint8_t _portB;
		static uint8_t _portC;
		static uint8_t _portD;
		
		unsigned int _frequency;
};

#endif
