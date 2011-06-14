#ifndef _TACTON_
#define _TACTON_

#include "WProgram.h"

#include <TactonPlayer.h>

class Tacton 
{
	public:
//		Tacton();
		Tacton(unsigned int nbframes, byte *desc);
//		Tacton(const Tacton &tacton);
		~Tacton();
		
		void play(const TactonPlayer &player) const;
		
//		Tacton & operator=(const Tacton &t);
		boolean isValid() const { return _patterns && _durations && _frequencies && _amplitudes; }

	private:
		unsigned int _nbframes;
		byte *_patterns;
		unsigned int *_durations;
		unsigned int *_frequencies;
		byte *_amplitudes;
};

#endif
