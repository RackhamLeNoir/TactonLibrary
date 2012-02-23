#include "Arduino.h"
#include "TactonPlayerWithAmplitude.h"

TactonPlayerWithAmplitude::TactonPlayerWithAmplitude(byte nbtactors, byte *pins)
:TactonPlayer(nbtactors, pins)
{
}

void TactonPlayerWithAmplitude::init() const
{
	//set counter 1 as Fast PWM
	TCCR1A |= (1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	//set counter 2 as Fast PWM
	TCCR2A |= ((1 << WGM20) & (1 << WGM21));
	TCCR2B &= ~(1 << WGM22);
}

void TactonPlayerWithAmplitude::beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude)
{
	init();
	setFrequency(frequency);
	setAmplitude(amplitude);
	setDuration(duration);
	setPattern(pattern);

    int i;
    long del = (long)(1000000 / ((long)frequency));
    long looptime = (long)((duration * 1000) / (del * 2));
	long udel = del % 1000;
	long mdel = del / 1000;
	
	Serial.print("del=");
	Serial.print(del);
	Serial.print(" udel=");
	Serial.print(udel);
	Serial.print(" mdel=");
	Serial.print(mdel);
	Serial.print(" looptime=");
	Serial.println(looptime);
	
    for (i = 0 ; i < looptime ; i++)
    {
		for (int j = 0 ; j < MAXTACTORS ; j++)
			if (j < _nbtactors && (pattern & (1 << j)))
				analogWrite(_pins[j], amplitude);
		//delayMicroseconds is not accurate over 16383µs
		if (del > 16000)
		{
			delayMicroseconds(udel);
			if (mdel > 0)
				delay(mdel);
		}
		else
			delayMicroseconds(del);
			
		for (int j = 0 ; j < MAXTACTORS ; j++)
			if (j < _nbtactors && (pattern & (1 << j)))
				analogWrite(_pins[j], 0);
		if (del > 16000)
		{
			delayMicroseconds(udel);
			if (mdel > 0)
				delay(mdel);
		}
		else
			delayMicroseconds(del);
    }
}
