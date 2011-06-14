#include "WProgram.h"
#include "TactonPlayer.h"

TactonPlayer::TactonPlayer(byte nbtactors, byte *pins)
:_nbtactors(nbtactors), _pins(pins)
{
	for (int i = 0 ; i < nbtactors ; i++)
		pinMode(pins[i], OUTPUT);     
}

void TactonPlayer::beep(byte pattern, unsigned int duration, unsigned int frequency, byte amplitude) const
{
    int i;
    long del = (long)(1000000 / frequency);
    long looptime = (long)((((long)duration) * 1000) / (del * 2));
    for (i = 0 ; i < looptime ; i++)
    {
		for (int j = 0 ; j < 8 ; j++)
			if (j < _nbtactors && (pattern & (0x01 << j)))
				analogWrite(_pins[j], amplitude);
		delayMicroseconds(del);
		for (int j = 0 ; j < 8 ; j++)
			if (j < _nbtactors && (pattern & (0x01 << j)))
				analogWrite(_pins[j], 0);
		delayMicroseconds(del);
    }
}
