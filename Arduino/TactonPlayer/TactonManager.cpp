#include "Arduino.h"
#include "TactonManager.h"

void* operator new(size_t n, void * p) { 
  return p; 
}
void* operator new(size_t n) { 
  return malloc(n); 
}
void operator delete (void * p) { 
  free(p); 
};

TactonManager::TactonManager(TactonPlayer *player)
: _nbplays(0), _nbtactons(0), _player(player)
{
}

void TactonManager::add(unsigned int nbframes, byte *desc)
{
	if (_nbtactons < MAXTACTONS)
	{
		_tactons[_nbtactons] = new Tacton(nbframes, desc);
		if (_tactons[_nbtactons])
		{
			Serial.println("Tacton added");
			_nbtactons++;
		}
	}
}

const Tacton *TactonManager::get(byte numtacton) const
{
	if (numtacton < _nbtactons)
		return _tactons[numtacton];
	else
		return NULL;
}

void TactonManager::clear()
{
	for (int i = 0 ; i < _nbtactons ; i++)
		delete _tactons[i];
	_nbtactons = 0;
	_nbplays = 0;
}

void TactonManager::addPlay(byte index, unsigned long timestamp)
{
	if (index >= _nbtactons || _nbplays >= MAXPLAYBUFFER)
		return;
	_playindex[_nbplays] = index;
	_playtimestamps[_nbplays] = timestamp;
	_nbplays++;	
}

void TactonManager::play(byte index)
{
	if (index < _nbtactons)
		_tactons[index]->play(*_player);
}

void TactonManager::play(unsigned int nbframes, byte *desc)
{
	Tacton t(nbframes, desc);
	t.play(*_player);
}

void TactonManager::setOffset(unsigned long timestamp)
{
	_offset = timestamp;
}

void TactonManager::checkPlay()
{
	unsigned long now = millis() - _offset;
/*	if (_nbplays == 0 || _playtimestamps[0] > now)
		return;
	Serial.print("Play at ");
	Serial.println(now, DEC);
	play(_playindex[0]);
	//shift other plays
	for (int i = 0 ; i < _nbplays ; i++)
	{
		_playindex[i] = _playindex[i + i];
		_playtimestamps[i] = _playtimestamps[i + i];		
	}
	_nbplays--;*/

	int i = 0, j = 0;
	while (_nbplays > 0 && i < MAXPLAYBUFFER && _playtimestamps[i] < now)
	{
		//TEST
		Serial.print("Play ");
		Serial.println(_playtimestamps[i], DEC);
		Serial.print(" at ");
		Serial.println(now, DEC);
		//
		play(_playindex[i]);
		i++;
		_nbplays--;
	}
	if (i == 0)
		return;
	//shift not played tactons
	for (j = 0 ; i + j < MAXPLAYBUFFER ; j++)
	{
		_playindex[j] = _playindex[j + i];
		_playtimestamps[j] = _playtimestamps[j + i];		
	}
	//erase shifted values
/*	for (i = j ; i < MAXPLAYBUFFER ; i++)
	{
		_playindex[i] = 0xff;
		_playtimestamps[i] = 0xffffffff;
	}*/
}

void TactonManager::setFrequency(unsigned int freq)
{
	_player->setFrequency(freq);
}

void TactonManager::setAmplitudes(unsigned int nbf, byte *desc)
{
	_player->setAmplitudes(nbf, desc);
}

void TactonManager::stop()
{
	_player->stop();
}

void TactonManager::setAngle(unsigned int angle)
{
	_player->setAngle(angle);
}

void TactonManager::setAngleSequence(unsigned int nbangles, unsigned int frameduration, unsigned int nbframes, byte *angles)
{/*
	Serial.print("Nb angles ");
	Serial.println(nbangles);
	Serial.print("Frame duration ");
	Serial.println(frameduration);
	Serial.print("Nb frames ");
	Serial.println(nbframes);*/
	
	unsigned int a[nbangles];
	for (int i = 0 ; i < nbangles ; i++)
		a[i] = (angles[2 * i] << 8) |angles[2 * i + 1];
	
	for (int i = 0 ; i < nbframes ; i++)
	{
		setAngle(a[i % nbangles]);
/*	Serial.print("Angle ");
	Serial.println(a[i % nbangles]);*/
		// /!\ don't forget to multiply if the timer was changed in TactonPlayer
		delay(64 * frameduration);
	}
	_player->clear();
}
