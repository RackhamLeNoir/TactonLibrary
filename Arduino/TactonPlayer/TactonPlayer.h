#ifndef _TACTONPLAYER_
#define _TACTONPLAYER_

#include "Arduino.h"

//if using more than 8, change type of pattern
#define MAXTACTORS 8

extern "C" void __cxa_pure_virtual(void); 

class TactonPlayer 
{
	public:
		TactonPlayer(byte nbtactors, byte *pins);

		//Same frequency for all the vibrators, different amplitude.
		//Vibrates until stop
		void buzz(unsigned int frequency, byte nbtactors, byte amplitudes[]);

		//Stop any vibration
		void stop();

		//8bits pattern => max 8 tactors, change type if using more
		virtual void beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude) = 0;
/*		
		void debug1() { analogWrite(_pins[0], 255); delay(100); analogWrite(_pins[0], 0); delay(100);}
		void debug2() { analogWrite(_pins[1], 255); delay(100); analogWrite(_pins[1], 0); delay(100); }
		void debug3() { analogWrite(_pins[2], 255); delay(100); analogWrite(_pins[2], 0); delay(100); }
		void debug4() { analogWrite(_pins[3], 255); delay(100); analogWrite(_pins[3], 0); delay(100); }
	*/
	protected:
		virtual void init() const {}
		
		virtual void setFrequency(unsigned int frequency) { _frequency = frequency; }
		virtual void setDuration(unsigned long duration) { _duration = duration; }
		virtual void setAmplitude(byte amplitude) { _amplitude = amplitude; }
		virtual void setPattern(byte pattern) { _pattern = pattern; }

		byte _nbtactors;
		byte *_pins;
		byte _pattern;
		unsigned long _duration;
		unsigned int _frequency;
		byte _amplitude;
};

#endif
