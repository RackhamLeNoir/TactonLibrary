#include "Arduino.h"
#include "TactonPlayer.h"

TactonPlayer::TactonPlayer(byte nbtactors, byte *pins)
{
	_nbtactors = min(MAXTACTORS, nbtactors);
	_pins = pins;
	
	for (int i = 0 ; i < _nbtactors ; i++)
	{
		pinMode(pins[i], OUTPUT);
	}	
}

void __cxa_pure_virtual(void) {};