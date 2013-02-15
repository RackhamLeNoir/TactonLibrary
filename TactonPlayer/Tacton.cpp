#include "Tacton.hpp"

#include <cstring>
#include <cstdlib>

Tacton::Tacton()
:_nbframes(0), _patterns(NULL), _durations(NULL), _frequencies(NULL), _amplitudes(NULL)
{
}

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

Tacton::Tacton(char *pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude)
:_nbframes(1), _patterns(new unsigned char[1]), _durations(new unsigned int[1]), _frequencies(new unsigned int[1]), _amplitudes(new unsigned char[1])
{
	_patterns[0] = 0;
	_durations[0] = duration;
	_frequencies[0] = frequency;
	_amplitudes[0] = amplitude;

	setPattern(pattern);
}

Tacton::Tacton(const char *pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude)
:_nbframes(1), _patterns(new unsigned char[1]), _durations(new unsigned int[1]), _frequencies(new unsigned int[1]), _amplitudes(new unsigned char[1])
{
	_patterns[0] = 0;
	_durations[0] = duration;
	_frequencies[0] = frequency;
	_amplitudes[0] = amplitude;

	setPattern(pattern);
}

Tacton::Tacton(const Tacton &t)
:_nbframes(t._nbframes)
{
	if (_nbframes > 0)
	{
		_patterns = new unsigned char[t._nbframes];
		memcpy(_patterns, t._patterns, t._nbframes * sizeof(unsigned char));
		_durations = new unsigned int[t._nbframes];
		memcpy(_durations, t._durations, t._nbframes * sizeof(unsigned int));
		_frequencies = new unsigned int[t._nbframes];
		memcpy(_frequencies, t._frequencies, t._nbframes * sizeof(unsigned int));
		_amplitudes = new unsigned char[t._nbframes];
		memcpy(_amplitudes, t._amplitudes, t._nbframes * sizeof(unsigned char));
	}
	else
	{
		_patterns = NULL;
		_durations = NULL;
		_frequencies = NULL;
		_amplitudes = NULL;
	}
}

Tacton::~Tacton()
{
	if (_nbframes > 0)
	{
		delete []_patterns;
		delete []_durations;
		delete []_frequencies;
		delete []_amplitudes;
	}
}

Tacton &Tacton::operator = (const Tacton &t)
{
	if (&t == this)
		return *this;

	if (_nbframes > 0)
	{
		delete []_patterns;
		delete []_durations;
		delete []_frequencies;
		delete []_amplitudes;
	}

	_nbframes = t.getNbFrames();

	if (_nbframes > 0)
	{
		_patterns = new unsigned char[t._nbframes];
		memcpy(_patterns, t._patterns, t._nbframes * sizeof(unsigned char));
		_durations = new unsigned int[t._nbframes];
		memcpy(_durations, t._durations, t._nbframes * sizeof(unsigned int));
		_frequencies = new unsigned int[t._nbframes];
		memcpy(_frequencies, t._frequencies, t._nbframes * sizeof(unsigned int));
		_amplitudes = new unsigned char[t._nbframes];
		memcpy(_amplitudes, t._amplitudes, t._nbframes * sizeof(unsigned char));
	}
	else
	{
		_patterns = NULL;
		_durations = NULL;
		_frequencies = NULL;
		_amplitudes = NULL;
	}

	return *this;
}

const unsigned int Tacton::getNbFrames() const
{
	return _nbframes;
}

__declspec(dllexport) void Tacton::setPattern(char pattern)
{
	setPattern(0, pattern);
}

__declspec(dllexport) void Tacton::setPattern(unsigned int frame, char pattern)
{
	if (frame < _nbframes)
		_patterns[frame] = pattern;
}

__declspec(dllexport) void Tacton::setPattern(char *pattern)
{
	setPattern(0, pattern);
}

__declspec(dllexport) void Tacton::setPattern(const char *pattern)
{
	setPattern(0, pattern);
}

__declspec(dllexport) void Tacton::setPattern(unsigned int frame, char *pattern)
{
	if (frame < _nbframes)
	{
		unsigned char t1 = pattern[0] == '1';
		unsigned char t2 = pattern[1] == '1';
		unsigned char t3 = pattern[2] == '1';
		unsigned char t4 = pattern[3] == '1';
		_patterns[frame] = (t1 << 3) | (t2 << 2) | (t3 << 1) | t4;
	}
}

__declspec(dllexport) void Tacton::setPattern(unsigned int frame, const char *pattern)
{
	if (frame < _nbframes)
	{
		unsigned char t1 = pattern[0] == '1';
		unsigned char t2 = pattern[1] == '1';
		unsigned char t3 = pattern[2] == '1';
		unsigned char t4 = pattern[3] == '1';
		_patterns[frame] = (t1 << 3) | (t2 << 2) | (t3 << 1) | t4;
	}
}

__declspec(dllexport) void Tacton::setDuration(unsigned int duration)
{
	setDuration(0, duration);
}

__declspec(dllexport) void Tacton::setDuration(unsigned int frame, unsigned int duration)
{
	if (frame < _nbframes)
		_durations[frame] = duration;
}

__declspec(dllexport) void Tacton::setFrequency(unsigned int frequency)
{
	setFrequency(0, frequency);
}

__declspec(dllexport) void Tacton::setFrequency(unsigned int frame, unsigned int frequency)
{
	if (frame < _nbframes)
		_frequencies[frame] = frequency;
}

__declspec(dllexport) void Tacton::setAmplitude(unsigned int amplitude)
{
	setAmplitude(0, amplitude);
}

__declspec(dllexport) void Tacton::setAmplitude(unsigned int frame, unsigned int amplitude)
{
	if (frame < _nbframes)
		_amplitudes[frame] = amplitude;
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

  