#ifndef _TACTON_
#define _TACTON_

#define POS1_UP_FORWARD 0x01
#define POS1_UP_BACKWARD 0x02
#define POS1_DOWN_FORWARD 0x08
#define POS1_DOWN_BACKWARD 0x04

#define POS2_RIGHT 0x01
#define POS2_UP 0x02
#define POS2_LEFT 0x04
#define POS2_DOWN 0x08

#ifdef __MACOSX__
#define EXPORTED
#else
#define EXPORTED __declspec(dllexport)
#endif

class Tacton 
{
	public:
		//creates a tacton using the raw data format
		//6 bytes per frame : 
		//1 for the pattern
		//2 for the duration
		//2 for the frequency
		//1 for the amplitude
		EXPORTED Tacton(unsigned int nbframes, unsigned char *desc);
		//creates a tacton using the CSV format
		//1 field for the number of frames, then 4 fields per frame 
		//1 for the pattern
		//1 for the duration
		//1 for the frequency
		//1 for the amplitude
		EXPORTED Tacton(char *desc);
		EXPORTED Tacton(unsigned int nbframes, unsigned char *patterns, unsigned int *durations, unsigned int *frequencies, unsigned char *amplitudes);
		//create a simple vibration
		EXPORTED Tacton(char *pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		EXPORTED Tacton(const char *pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		EXPORTED Tacton(unsigned char pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		EXPORTED Tacton(const Tacton &t);
		EXPORTED ~Tacton();

		//changes the pattern using raw format
		EXPORTED void setPattern(char pattern);
		EXPORTED void setPattern(unsigned int frame, char pattern);
		//changes the pattern using string format
		EXPORTED void setPattern(char *pattern);
		EXPORTED void setPattern(const char *pattern);
		EXPORTED void setPattern(unsigned int frame, char *pattern);
		EXPORTED void setPattern(unsigned int frame, const char *pattern);
		//changes the duration
		EXPORTED void setDuration(unsigned int duration);
		EXPORTED void setDuration(unsigned int frame, unsigned int duration);
		//changes the frequency
		EXPORTED void setFrequency(unsigned int frequency);
		EXPORTED void setFrequency(unsigned int frame, unsigned int frequency);
		//changes the amplitude
		EXPORTED void setAmplitude(unsigned int amplitude);
		EXPORTED void setAmplitude(unsigned int frame, unsigned int amplitude);

		
		//returns the number of frames
		EXPORTED const unsigned int getNbFrames() const;

		//returns the raw code (useful to send to the serial port)
		EXPORTED void *rawCode() const;

	private:
		unsigned int _nbframes;
		unsigned char *_patterns;
		unsigned int *_durations;
		unsigned int *_frequencies;
		unsigned char *_amplitudes;
};

#endif
