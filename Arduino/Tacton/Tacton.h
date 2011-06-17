#ifndef _TACTON_
#define _TACTON_

#include "WProgram.h"

#include <TactonPlayer.h>

class Tacton 
{
	public:
		Tacton(unsigned int nbframes, byte *desc);
		~Tacton();
		
		void play(const TactonPlayer &player) const;
		
		boolean isValid() const { return _patterns && _durations && _frequencies && _amplitudes; }

	private:
		unsigned int _nbframes;
		byte *_patterns;
		unsigned int *_durations;
		unsigned int *_frequencies;
		byte *_amplitudes;
};

#endif
