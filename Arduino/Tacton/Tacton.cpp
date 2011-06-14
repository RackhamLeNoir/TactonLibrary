#include "WProgram.h"
#include "Tacton.h"


/*Tacton::Tacton()
:_nbframes(0), _patterns(NULL), _durations(NULL), _frequencies(NULL), _amplitudes(NULL)
{
}*/

Tacton::Tacton(unsigned int nbframes, byte *desc)
:_nbframes(nbframes), _patterns((byte *)malloc(nbframes * sizeof(byte))), _durations((unsigned int *)malloc(nbframes * sizeof(unsigned int))), _frequencies((unsigned int *)malloc(nbframes * sizeof(unsigned int))), _amplitudes((byte *)malloc(nbframes * sizeof(byte)))
{
	if (isValid())
	{
		for(int i = 0 ; i < nbframes ; i++)
		{
			_patterns[i] = desc[6*i];
			_durations[i] = (((unsigned int)(desc[6*i+1])) << 8) | ((unsigned int)(desc[6*i+2]));
			_frequencies[i] = (((unsigned int)(desc[6*i+3])) << 8) | ((unsigned int)(desc[6*i+4]));
			_amplitudes[i] = desc[6*i+5];
		}
	}
}

/*Tacton::Tacton(const Tacton &tacton)
:_nbframes(tacton._nbframes), _patterns((byte *)malloc(tacton._nbframes * sizeof(byte))), _durations((unsigned int *)malloc(tacton._nbframes * sizeof(unsigned int))), _frequencies((unsigned int *)malloc(tacton._nbframes * sizeof(unsigned int))), _amplitudes((byte *)malloc(tacton._nbframes * sizeof(byte)))
{
	for(int i = 0 ; i < tacton._nbframes ; i++)
	{
		_patterns[i] = tacton._patterns[i];
		_durations[i] = tacton._durations[i];
		_frequencies[i] = tacton._frequencies[i];
		_amplitudes[i] = tacton._amplitudes[i];
	}
}*/

Tacton::~Tacton()
{
	free(_patterns);
	free(_durations);
	free(_frequencies);
	free(_amplitudes);
}
		
void Tacton::play(const TactonPlayer &player) const
{	      
	if (isValid())
		for (int i = 0 ; i < _nbframes ; i++)
			player.beep(_patterns[i], _durations[i], _frequencies[i], _amplitudes[i]);
}

/*Tacton& Tacton::operator=(const Tacton &t) 
{
    if (this == &t)
		return *this;
	if (_patterns)
		free(_patterns);
	if (_durations)
		free(_durations);
	if (_frequencies)
		free(_frequencies);
	if (_amplitudes)
		free(_amplitudes);
	_nbframes = t._nbframes;
	_patterns = (byte *)malloc(_nbframes * sizeof(byte));
	_durations = (unsigned int *)malloc(_nbframes * sizeof(unsigned int));
	_frequencies = (unsigned int *)malloc(_nbframes * sizeof(unsigned int));
	_amplitudes = (byte *)malloc(_nbframes * sizeof(byte));
	for(int i = 0 ; i < _nbframes ; i++)
	{
		_patterns[i] = t._patterns[i];
		_durations[i] = t._durations[i];
		_frequencies[i] = t._frequencies[i];
		_amplitudes[i] = t._amplitudes[i];
	}

    return *this;
}*/
  