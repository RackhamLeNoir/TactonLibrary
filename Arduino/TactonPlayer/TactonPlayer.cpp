#include "WProgram.h"
#include "TactonPlayer.h"

TactonPlayer::TactonPlayer(byte nbtactors, byte *pins)
:_nbtactors(nbtactors), _pins(pins)
{
	for (int i = 0 ; i < nbtactors ; i++)
		pinMode(pins[i], OUTPUT);     
}

void TactonPlayer::beep(byte pattern, long duration, unsigned int frequency, byte amplitude) const
{
    int i;
    long del = (long)(1000000 / ((long)frequency));
    long looptime = (long)((duration * 1000) / (del * 2));
	long udel = del % 1000;
	long mdel = del / 1000;
    for (i = 0 ; i < looptime ; i++)
    {
		for (int j = 0 ; j < 8 ; j++)
			if (j < _nbtactors && (pattern & (0x01 << j)))
				analogWrite(_pins[j], amplitude);
		//delayMicroseconds is not accurate over 16383µs
		if (del > 10000)
		{
			delayMicroseconds(udel);
			delay(mdel);
		}
		else
			delayMicroseconds(del);
		for (int j = 0 ; j < 8 ; j++)
			if (j < _nbtactors && (pattern & (0x01 << j)))
				analogWrite(_pins[j], 0);
		if (del > 10000)
		{
			delayMicroseconds(udel);
			delay(mdel);
		}
		else
			delayMicroseconds(del);
    }
}
