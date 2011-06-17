#ifndef _TACTONPLAYER_
#define _TACTONPLAYER_

#include "WProgram.h"

class TactonPlayer 
{
	public:
		TactonPlayer(byte nbtactors, byte *pins);

		//8bits pattern => max 8 tactors, change type if using more
		void beep(byte pattern, long duration, unsigned int frequency, byte amplitude) const;
		
		void debug1() { analogWrite(_pins[0], 255); delay(100); analogWrite(_pins[0], 0); delay(100);}
		void debug2() { analogWrite(_pins[1], 255); delay(100); analogWrite(_pins[1], 0); delay(100); }
		void debug3() { analogWrite(_pins[2], 255); delay(100); analogWrite(_pins[2], 0); delay(100); }
		void debug4() { analogWrite(_pins[3], 255); delay(100); analogWrite(_pins[3], 0); delay(100); }
	
	private:		
		byte _nbtactors;
		byte *_pins;
};

#endif
