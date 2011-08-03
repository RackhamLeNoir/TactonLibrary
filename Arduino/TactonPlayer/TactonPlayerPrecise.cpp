#include "WProgram.h"
#include "TactonPlayerPrecise.h"

#include "pins_arduino.h"

volatile unsigned long _toggle_count;
//volatile bool _active = false;

/*
volatile unsigned long _ccper256cv; // (F_CPU) / (512 * _frequency)
volatile unsigned long _cv; // (F_CPU * _duration) / (256000 * _ccper256cv)
volatile unsigned long _currentcvi; // 0 <= _ccper256cv <= _ccper256cv
volatile unsigned long _currentcv; // 0 <= _currentcv <= _cv
volatile bool _currentstate;
*/

uint8_t TactonPlayerPrecise::_portB = 0;
uint8_t TactonPlayerPrecise::_portC = 0;
uint8_t TactonPlayerPrecise::_portD = 0;


TactonPlayerPrecise::TactonPlayerPrecise(byte nbtactors, byte *pins)
:TactonPlayer(nbtactors, pins)
{
}

void TactonPlayerPrecise::init() const
{
	//init timers
	TIMSK1 = 0;
	TCNT1 = 0;
	TCCR1A = 0; // CTC mode
	TCCR1B = (1 << WGM12) | (1 << CS10);
}

void TactonPlayerPrecise::setFrequency(unsigned int frequency)
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

void TactonPlayerPrecise::setDuration(unsigned long duration)
{
	TactonPlayer::setDuration(duration);
	_toggle_count = 2 * _frequency * _duration / 1000;

/*	_cv = (F_CPU / 1000 * _duration) / 256 / _ccper256cv;
	_currentcv = 0;

/*	Serial.print("_duration=");
	Serial.print(_duration, DEC);
	Serial.print(" _cv=");
	Serial.println(_cv, DEC);*/
}

void TactonPlayerPrecise::setAmplitude(byte amplitude)
{
	TactonPlayer::setAmplitude(amplitude);
//	OCR2A = amplitude;
	
/*	Serial.print("_amplitude=");
	Serial.print(_amplitude, DEC);*/
}

void TactonPlayerPrecise::setPattern(byte pattern)
{
	TactonPlayer::setPattern(pattern);

	_portB = _portC = _portD = 0;
	for (int i = 0 ; i < _nbtactors ; i++)
	{
		pinMode(_pins[i], OUTPUT);
		volatile uint8_t * port = portOutputRegister(digitalPinToPort(_pins[i]));
		if (_pattern & (1 << i))
		{
			if (port == &PORTB)
				_portB |= digitalPinToBitMask(_pins[i]);
			else if (port == &PORTC)
				_portC |= digitalPinToBitMask(_pins[i]);
			else if (port == &PORTD)
				_portD |= digitalPinToBitMask(_pins[i]);
		}
	}	
}

void TactonPlayerPrecise::tooglePins()
{
	PORTB ^= _portB;
	PORTC ^= _portC;
	PORTD ^= _portD;
}

void TactonPlayerPrecise::turnOnPins()
{
	PORTB |= _portB;
	PORTC |= _portC;
	PORTD |= _portD;
}

void TactonPlayerPrecise::turnOffPins()
{
	PORTB &= ~_portB;
	PORTC &= ~_portC;
	PORTD &= ~_portD;
}

void TactonPlayerPrecise::beep(byte pattern, unsigned long duration, unsigned int frequency, byte amplitude)
{
	init();
	setFrequency(frequency);
//	setAmplitude(amplitude);
	setDuration(duration);
	setPattern(pattern);
	//_active = true;
	turnOnPins();
	TIMSK1 = (1 << OCIE1A);
//	TIMSK2 = (1 << OCIE2A) | (1 << TOIE2);
//	TIMSK2 = (1 << TOIE2);
	sei();
}


ISR(TIMER1_COMPA_vect)
{
	if (_toggle_count > 0)
	{
		_toggle_count--;
		TactonPlayerPrecise::tooglePins();
	}
	else
	{
		TIMSK1 &= ~(1 << OCIE1A);
		TactonPlayerPrecise::turnOffPins();
	}
}

/*
ISR(TIMER2_OVF_vect)
{
	_currentcvi++;
	if (_currentcvi >= _ccper256cv)
	{
		_currentstate = !_currentstate;
		_currentcvi = 0;
		_currentcv++;
		if (_currentcv >= _cv)
		{
			//TIMSK2 &= ~(1 << TOIE2);
			TIMSK2 &= ~((1 << OCIE2A) | (1 << TOIE2));
			TactonPlayer::turnOffPins();
			return;
		}
	}
	if (_currentstate)
		TactonPlayer::tooglePins();

//	count1++;
//	if (_active)
//	{
//		TactonPlayer::tooglePins();
//		count2++;
//	}
//	else
//		TactonPlayer::turnOffPins();
}

ISR(TIMER2_COMPA_vect)
{
//	if (_active)
	if (_currentstate)
		TactonPlayer::tooglePins();
//	else
//		TactonPlayer::turnOffPins();
}
*/	
