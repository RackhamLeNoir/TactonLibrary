#ifndef _TACTONMANAGER_
#define _TACTONMANAGER_

#include "WProgram.h"

#include <Tacton.h>
#include <TactonPlayer.h>

#define MAXTACTONS		16
#define MAXPLAYBUFFER	10

class TactonManager
{
	public:
		TactonManager(TactonPlayer *player);
		
//		void add(const Tacton &t);
		void add(unsigned int nbframes, byte *desc);
		const Tacton *get(byte numtacton) const;
		
		void play(byte index);
		void play(unsigned int nbframes, byte *desc);
		void addPlay(byte index, unsigned long timestamp);
		void checkPlay();
		void setOffset(unsigned long timestamp);

		void clear();
		
	private:
		byte _nbplays;
		byte _nbtactons;
		Tacton *_tactons[MAXTACTONS];
		byte _playindex[MAXPLAYBUFFER];
		unsigned long _playtimestamps[MAXPLAYBUFFER];
		TactonPlayer *_player;
		unsigned long _offset;
};

#endif
