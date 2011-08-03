#include "WProgram.h"
#include "Tacton.h"


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

Tacton::~Tacton()
{
	free(_patterns);
	free(_durations);
	free(_frequencies);
	free(_amplitudes);
}
		
void Tacton::play(TactonPlayer &player) const
{	      
	if (isValid())
	{
		for (int i = 0 ; i < _nbframes ; i++)
			player.beep(_patterns[i], (long)_durations[i], _frequencies[i], _amplitudes[i]);
	}
}
