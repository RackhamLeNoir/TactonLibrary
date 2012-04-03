#include "TactonPlayer.hpp"

#include <ArduinoSerial\SerialWindows.hpp>

#include <stdexcept>

TactonPlayer::TactonPlayer(const char *port)
{
	try
	{
		_comport = new SerialWindows(port);
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
		_comport->WriteData("S", 1);
}

void TactonPlayer::stop()
{
	if (_comport)
		_comport->WriteData("Q", 1);
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

void TactonPlayer::debugRead(char *res, int nb) const
{
	if (_comport)
		_comport->ReadData(res, nb);
}
