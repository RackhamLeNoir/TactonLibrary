#include "Arduino.h"
#include "TactonPlayerPreciseNew.h"

TactonPlayerPreciseNew::TactonPlayerPreciseNew(byte nbtactors, byte *pins, byte pwmPin)
:TactonPlayer(nbtactors, pins), _pwmPin(pwmPin)
{
	pinMode(_pwmPin, OUTPUT);
	init();
}

void TactonPlayerPreciseNew::init() const
{
	//init PWM timer
	TIMSK1 = 0;
	TCNT1 = 0;
	TCCR1A = 0; // CTC mode
	TCCR1B = (1 << WGM12) | (1 << CS10);
}

void TactonPlayerPreciseNew::setFrequency(unsigned int frequency)
{
	TactonPlayer::setFrequency(frequency);
	
	unsigned long ocr = F_CPU / _frequency / 2 - 1;
	byte prescalarbits = (1 << CS10);
	
	if (ocr > 0xffff)
	{
		ocr = F_CPU / _frequency / 64 / 2 - 1;
		prescalarbits = (1 << CS11) | (1 << CS10);
	}
	/*
	Serial.print("_frequency=");
	Serial.print(_frequency, DEC);
	Serial.print(" prescalar=");
	Serial.print(prescalarbits, BIN);
	Serial.print(" ocr=");
	Serial.println(ocr, DEC);*/

	TCCR1B |= prescalarbits;
	OCR1A = ocr;
/*
	_ccper256cv = F_CPU / 512 / _frequency;
	_currentcvi = 0;*/

/*	Serial.print("_frequency=");
	Serial.print(_frequency, DEC);
	Serial.print(" _ccper256cv=");
	Serial.println(_ccper256cv, DEC);*/
}


void TactonPlayerPreciseNew::beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude)
{
	init();
	setFrequency(frequency);
	setAmplitude(amplitude);
	setDuration(duration);
	setPattern(pattern);
	
	//set the pattern
	for (int i = 0 ; i < _nbtactors ; i++)
	{
		if (_pattern & (1 << i))
		{
			analogWrite(_pins[i], _amplitude);
		}
	}
		
	//_active = true;

	//Start the PWM
	TIMSK1 = (1 << OCIE1A);
	
	delay(duration);
	
	//Stop the PWM
	TIMSK1 &= ~(1 << OCIE1A);

//	TIMSK2 = (1 << OCIE2A) | (1 << TOIE2);
//	TIMSK2 = (1 << TOIE2);
//	sei();
}

