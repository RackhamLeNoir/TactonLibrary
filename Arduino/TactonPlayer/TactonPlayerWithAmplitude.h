#ifndef _TACTONPLAYERWITHAMPLITUDE_
#define _TACTONPLAYERWITHAMPLITUDE_

#include "WProgram.h"

#include <TactonPlayer.h>

class TactonPlayerWithAmplitude: public TactonPlayer
{
	public:
		TactonPlayerWithAmplitude(byte nbtactors, byte *pins);
	
		//8bits pattern => max 8 tactors, change type if using more
		void beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude);
	private:
		void init() const;
};

#endif
