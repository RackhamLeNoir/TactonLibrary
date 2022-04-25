#include "TactonPlayer.hpp"

#ifdef _WIN32
	#include <SerialWindows.hpp>
#elif defined(LINUX)
	#include <SerialLinux.hpp>
#else
	#include <SerialMac.hpp>
#endif

#include <stdexcept>
#include <cstring>

TactonPlayer::TactonPlayer(const char *port)
{
	try
	{
#ifdef _WIN32
		_comport = new SerialWindows(port);
#elif defined(LINUX)
		_comport = new SerialLinux(port);
#else
		_comport = new SerialMac(port);
#endif
	}
	catch(...)
	{
		_comport = NULL;
	}
}

TactonPlayer::~TactonPlayer()
{
	delete _comport;
}

void TactonPlayer::start()
{
	if (_comport)
		_comport->WriteData((void *)("S"), 1);
}

void TactonPlayer::stop()
{
	if (_comport)
		_comport->WriteData((void *)("Q"), 1);
}

void TactonPlayer::regist(const Tacton &t)
{
	if (!_comport)
		return;

	unsigned int nbframes = t.getNbFrames();
	unsigned char *buffer = new unsigned char[3 + 6 * nbframes];
	buffer[0] = 'N';
	buffer[1] = (nbframes & 0xff00) >> 8;
	buffer[2] = nbframes & 0xff;

	memcpy(buffer + 3, t.rawCode(), 6 * nbframes);
	_comport->WriteData(buffer, 3 + 6 * nbframes);
	delete []buffer;
}

unsigned int TactonPlayer::registFile(char *filename)
{
	if (!_comport)
		return -1;
	unsigned int nb = 0;

	//load icons
	FILE *f = fopen(filename, "r");
	if (!f)
		throw "Invalid file";

	char buffer[256];
	while ((fgets(buffer, 256, f)) != NULL)
	{
		while((buffer[strlen(buffer) - 1] == '\r') || (buffer[strlen(buffer) - 1] == '\n'))
			buffer[strlen(buffer) - 1] = '\0';
		try
		{
			Tacton t(buffer);
			regist(t);
			nb++;
		}
		catch(...)
		{
		}
	}
	fclose(f);
	return nb;
}

void TactonPlayer::play(unsigned char index)
{
	if (!_comport)
		return;
	unsigned char buffer[2];
	buffer[0] = 'T';
	buffer[1] = index;
	_comport->WriteData(buffer, 2);
}

void TactonPlayer::play(const Tacton &t)
{
	if (!_comport)
		return;

	unsigned int nbframes = t.getNbFrames();
	unsigned char *buffer = new unsigned char[3 + 6 * nbframes];
	buffer[0] = 'V';
	buffer[1] = (nbframes & 0xff00) >> 8;
	buffer[2] = nbframes & 0xff;
	memcpy(buffer + 3, t.rawCode(), 6 * nbframes);
	_comport->WriteData(buffer, 3 + 6 * nbframes);
	delete []buffer;
}

void TactonPlayer::schedule(unsigned char index, unsigned long timestamp)
{
	if (!_comport)
		return;

	unsigned char buffer[6];
	buffer[0] = 'P';
	buffer[1] = index;
	buffer[2] = (unsigned char)((timestamp & 0xff000000) >> 24);
	buffer[3] = (unsigned char)((timestamp & 0x00ff0000) >> 16);
	buffer[4] = (unsigned char)((timestamp & 0x0000ff00) >> 8);
	buffer[5] = (unsigned char)(timestamp & 0x000000ff);
	_comport->WriteData(buffer, 6);
}

void TactonPlayer::setFrequency(unsigned int frequency)
{
	if (!_comport)
		return;

	unsigned char buffer[3];
	buffer[0] = 'F';
	buffer[1] = (unsigned char)((frequency & 0x0000ff00) >> 8);
	buffer[2] = (unsigned char)(frequency & 0x000000ff);
	_comport->WriteData(buffer, 3);
}

void TactonPlayer::setAmplitudes(unsigned char nbtactors, unsigned char *amplitudes)
{
	if (!_comport)
		return;

	unsigned char *buffer = new unsigned char[2 + nbtactors];
	buffer[0] = 'A';
	buffer[1] = nbtactors;
	memcpy(buffer + 2, amplitudes, nbtactors);
	_comport->WriteData(buffer, 2 + nbtactors);
	delete[] buffer;
}

void TactonPlayer::playAngle(unsigned int angle)
{
	if (!_comport)
		return;

	unsigned char *buffer = new unsigned char[3];
	buffer[0] = 'a';
	buffer[1] = (unsigned char)((angle & 0x0000ff00) >> 8);
	buffer[2] = (unsigned char)(angle & 0x000000ff);
	_comport->WriteData(buffer, 3);
	delete[] buffer;
}

//plays an animation alterning a series of angles
void TactonPlayer::playAngleSequence(unsigned char nbangles, unsigned int frameduration, unsigned int nbframes, unsigned int *angles)
{
	if (!_comport)
		return;

	unsigned char *buffer = new unsigned char[6 + 2 * nbangles];
	buffer[0] = 's';
	buffer[1] = nbangles;
	buffer[2] = (unsigned char)((frameduration & 0x0000ff00) >> 8);
	buffer[3] = (unsigned char)(frameduration & 0x000000ff);
	buffer[4] = (unsigned char)((nbframes & 0x0000ff00) >> 8);
	buffer[5] = (unsigned char)(nbframes & 0x000000ff);

	for (int i = 0 ; i < nbangles ; i++)
	{
		buffer[6 + 2 * i] = (angles[i]  & 0x0000ff00) >> 8;
		buffer[6 + 2 * i + 1] = angles[i]  & 0x000000ff;
	}
	_comport->WriteData(buffer, 6 + 2 * nbangles);
	delete[] buffer;
}

void TactonPlayer::stopBuzz()
{
	if (!_comport)
		return;

	_comport->WriteData((void *)("B"), 1);
}

void TactonPlayer::debugRead(char *res, int nb) const
{
	if (_comport)
		_comport->ReadData(res, nb);
}
