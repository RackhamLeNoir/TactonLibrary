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
//	TCNT1 = 0;
	//CTC mode
	TCCR1A = (1 << COM1A0) | (1 << COM1B0); 
	TCCR1B = (1 << WGM12);
	//set duty cycle to 0;
	OCR1A = 0;
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
	Serial.println(ocr, HEX);*/

	//set pre-scaler
	TCCR1B |= prescalarbits;
	//set duty cycle
	OCR1A = ocr;
	/*Serial.print(" OCR1A=");
	Serial.println(OCR1A, HEX);*/
	//OCR1B = ocr;
/*
	_ccper256cv = F_CPU / 512 / _frequency;
	_currentcvi = 0;*/

/*	Serial.print("_frequency=");
	Serial.print(_frequency, DEC);
	Serial.print(" _ccper256cv=");
	Serial.println(_ccper256cv, DEC);*/
}

//Start a vibration of a given frequency, with different amplitudes for each vibrator
void TactonPlayerPreciseNew::buzz(unsigned int frequency, byte nbtactors, byte *amplitudes)
{
	if (nbtactors != _nbtactors)
		return;
		
	sei();
	init();
	
	//set the amplitudes
	for (int i = 0 ; i < _nbtactors ; i++)
		analogWrite(_pins[i], amplitudes[i]);

	setFrequency(frequency);
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
	sei();
	init();
//	setAmplitude(amplitude);
//	setDuration(duration);
//	setPattern(pattern);
	
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
//	analogWrite(9, 1);
	/*
	Serial.print("Start pattern");
	Serial.println(pattern, HEX);
	*/
	//Start the PWM
//	TCCR1A |= 1 << COM1A1;
//	TIMSK1 = (1 << OCIE1A);
	
//	Serial.print("Wait");
//	Serial.println(duration, DEC);
	delay(duration);
	
/*	Serial.println("TCCR1");
	Serial.println(TCCR1A, BIN);
	Serial.println(TCCR1B, BIN);
	*/
	//Stop the PWM
//	TIMSK1 &= ~(1 << OCIE1A);
//	TCCR1A &= ~(1 << COM1A1);

	TCCR1A = 0;

	//set duty cycle to 0
	OCR1A = 0;
	OCR1B = 0;
	//clear the pattern
	for (int i = 0 ; i < _nbtactors ; i++)
		digitalWrite(_pins[i], LOW);

//	Serial.println("Stop");

//	TIMSK2 = (1 << OCIE2A) | (1 << TOIE2);
//	TIMSK2 = (1 << TOIE2);
//	sei();
}

