#ifndef _TACTON_
#define _TACTON_

class Tacton 
{
	public:
		//creates a tacton using the raw data format
		//6 bytes per frame : 
		//1 for the pattern
		//2 for the duration
		//2 for the frequency
		//1 for the amplitude
		__declspec(dllexport) Tacton(unsigned int nbframes, unsigned char *desc);
		//creates a tacton using the CSV format
		//1 field for the number of frames, then 4 fields per frame 
		//1 for the pattern
		//1 for the duration
		//1 for the frequency
		//1 for the amplitude
		__declspec(dllexport) Tacton(char *desc);
		__declspec(dllexport) Tacton(unsigned int nbframes, unsigned char *patterns, unsigned int *durations, unsigned int *frequencies, unsigned char *amplitudes);
		//create a simple vibration
		__declspec(dllexport) Tacton(unsigned char pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		__declspec(dllexport) ~Tacton();
		
		//returns the number of frames
		__declspec(dllexport) const unsigned int getNbFrames() const;

		//returns the raw code (useful to send to the serial port)
		__declspec(dllexport) void *rawCode() const;

	private:
		unsigned int _nbframes;
		unsigned char *_patterns;
		unsigned int *_durations;
		unsigned int *_frequencies;
		unsigned char *_amplitudes;
};

#endif
