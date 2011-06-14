#include "Tacton.hpp"

#include <cstring>
#include <cstdlib>

Tacton::Tacton(unsigned int nbframes, unsigned char *desc)
:_nbframes(nbframes), _patterns(new unsigned char[nbframes]), _durations(new unsigned int[nbframes]), _frequencies(new unsigned int[nbframes]), _amplitudes(new unsigned char[nbframes])
{
	for(unsigned int i = 0 ; i < nbframes ; i++)
	{
		_patterns[i] = desc[6*i];
		_durations[i] = (((unsigned int)(desc[6*i+1])) << 8) | ((unsigned int)(desc[6*i+2]));
		_frequencies[i] = (((unsigned int)(desc[6*i+3])) << 8) | ((unsigned int)(desc[6*i+4]));
		_amplitudes[i] = desc[6*i+5];
	}
}

Tacton::Tacton(char *desc)
{
	char *buffer = strdup(desc);

	//read the number of frames
	char *token = strtok(buffer, "; ,");
	if (token == NULL)
		throw "Invalid description";
	_nbframes = atoi(token);

	 _patterns = new unsigned char[_nbframes];
	 _durations = new unsigned int[_nbframes];
	 _frequencies = new unsigned int[_nbframes];
	 _amplitudes = new unsigned char[_nbframes];

	for (unsigned int i = 0 ; i < _nbframes ; i++)
	{
		//read the pattern
		if ((token = strtok(NULL, "; ,")) == NULL || strlen(token) != 4)
			throw "Invalid description";
		unsigned char t1 = token[0] == '1';
		unsigned char t2 = token[1] == '1';
		unsigned char t3 = token[2] == '1';
		unsigned char t4 = token[3] == '1';
		_patterns[i] = (t1 << 3) | (t2 << 2) | (t3 << 1) | t4;

		//read the duration
		if ((token = strtok(NULL, "; ,")) == NULL)
			throw "Invalid description";
		_durations[i] = atoi(token);

		//read the frequency
		if ((token = strtok(NULL, "; ,")) == NULL)
			throw "Invalid description";
		_frequencies[i] = atoi(token);

		//read the amplitude
		if ((token = strtok(NULL, "; ,")) == NULL)
			throw "Invalid description";
		_amplitudes[i] = atoi(token);
	}

	free(buffer);
}

Tacton::Tacton(unsigned int nbframes, unsigned char *patterns, unsigned int *durations, unsigned int *frequencies, unsigned char *amplitudes)
:_nbframes(nbframes), _patterns(new unsigned char[nbframes]), _durations(new unsigned int[nbframes]), _frequencies(new unsigned int[nbframes]), _amplitudes(new unsigned char[nbframes])
{
	memcpy(_patterns, patterns, nbframes * sizeof(unsigned char));
	memcpy(_durations, durations, nbframes * sizeof(unsigned int));
	memcpy(_frequencies, frequencies, nbframes * sizeof(unsigned int));
	memcpy(_amplitudes, amplitudes, nbframes * sizeof(unsigned char));
}

Tacton::Tacton(unsigned char pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude)
:_nbframes(1), _patterns(new unsigned char[1]), _durations(new unsigned int[1]), _frequencies(new unsigned int[1]), _amplitudes(new unsigned char[1])
{
	_patterns[0] = pattern;
	_durations[0] = duration;
	_frequencies[0] = frequency;
	_amplitudes[0] = amplitude;
}

Tacton::~Tacton()
{
	delete []_patterns;
	delete []_durations;
	delete []_frequencies;
	delete []_amplitudes;
}

const unsigned int Tacton::getNbFrames() const
{
	return _nbframes;
}

void *Tacton::rawCode() const
{
	unsigned char *res = new unsigned char[_nbframes * 6];
	for (unsigned int i = 0 ; i < _nbframes ; i++)
	{
		res[6*i] = _patterns[i];
		res[6*i+1] = (_durations[i] & 0xff00) >> 8;
		res[6*i+2] = _durations[i] & 0xff;
		res[6*i+3] = (_frequencies[i] & 0xff00) >> 8;
		res[6*i+4] = _frequencies[i] & 0xff;
		res[6*i+5] = _amplitudes[i];
	}
	return res;
}

  