#include "Arduino.h"
#include "TactonPlayerPreciseNew.h"

TactonPlayerPreciseNew::TactonPlayerPreciseNew(byte nbtactors, byte *pins, byte pwmPin)
:TactonPlayer(nbtactors, pins), _pwmPin(pwmPin)
{
	pinMode(_pwmPin, OUTPUT);
	digitalWrite(_pwmPin, LOW);
	init();
}

void TactonPlayerPreciseNew::init() const
{
	//init PWM timer

	//CTC mode
	TCCR1A = (1 << COM1A0) | (1 << COM1B0); 
	TCCR1B = (1 << WGM12);
	//set duty cycle to 0;
	OCR1A = 0;
	
	//set prescalar for timer0 and timer2 to 1
	// /!\ this affects delay!
	TCCR0B &= ~(1 << CS01);
	TCCR2B &= ~(1 << CS21);
}

void TactonPlayerPreciseNew::setFrequency(unsigned int frequency)
{
	//TactonPlayer::setFrequency(frequency);

	sei();
	init();
	
	unsigned long ocr = F_CPU / frequency / 2 - 1;
	byte prescalarbits = (1 << CS10);
	
	if (ocr > 0xffff)
	{
		ocr = F_CPU / frequency / 64 / 2 - 1;
		prescalarbits = (1 << CS11) | (1 << CS10);
	}
/*
	Serial.print("Set freq ");
	Serial.println(frequency, DEC);
	Serial.print("OCR ");
	Serial.println(ocr, DEC);
	Serial.print("Prescalar ");
	Serial.println(prescalarbits, HEX);*/
	//set pre-scaler
	TCCR1B |= prescalarbits;
	//set duty cycle
	OCR1A = ocr;
}

//Sets a different amplitudes for each vibrator
void TactonPlayerPreciseNew::setAmplitudes(byte nbtactors, byte *amplitudes)
{
	if (nbtactors != _nbtactors)
		return;

	//set the amplitudes
	for (int i = 0 ; i < _nbtactors ; i++)
		analogWrite(_pins[i], amplitudes[i]);
}

//Stop any vibration
void TactonPlayerPreciseNew::stop()
{
	TCCR1A = 0;
	//set duty cycle to 0
	OCR1A = 0;
	OCR1B = 0;
	//clear the pattern
	for (int i = 0 ; i < _nbtactors ; i++)
		digitalWrite(_pins[i], LOW);
}

//Play a Tacton for a specified duration, frequency and amplitude
void TactonPlayerPreciseNew::beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude)
{	
	//set the pattern
	for (int i = 0 ; i < _nbtactors ; i++)
	{
		if (pattern & (1 << i))
			analogWrite(_pins[i], amplitude);
		else
			digitalWrite(_pins[i], LOW);
	}
	
	//set the frequency and activate the output
	setFrequency(frequency);
	
	// /!\ multiply by 64 when the prescalar is applied to timer0
	delay(64*duration);
	
	//Stop the PWM
	TCCR1A = 0;

	//set duty cycle to 0
	OCR1A = 0;
	OCR1B = 0;
	//clear the pattern
	for (int i = 0 ; i < _nbtactors ; i++)
		digitalWrite(_pins[i], LOW);
}

