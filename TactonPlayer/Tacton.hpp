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

#ifdef _WIN32
	#ifdef _WINDLL
		#define EXPORTED __declspec(dllexport)
	#else 
		#define EXPORTED __declspec(dllimport)
	#endif
#else
	#define EXPORTED
#endif

class EXPORTED Tacton 
{
	public:
		Tacton();
		//creates a tacton using the raw data format
		//6 bytes per frame : 
		//1 for the pattern
		//2 for the duration
		//2 for the frequency
		//1 for the amplitude
		Tacton(unsigned int nbframes, unsigned char *desc);
		//creates a tacton using the CSV format
		//1 field for the number of frames, then 4 fields per frame 
		//1 for the pattern
		//1 for the duration
		//1 for the frequency
		//1 for the amplitude
		Tacton(char *desc);
		Tacton(unsigned int nbframes, unsigned char *patterns, unsigned int *durations, unsigned int *frequencies, unsigned char *amplitudes);
		//create a simple vibration
		Tacton(char *pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		Tacton(const char *pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		Tacton(unsigned char pattern, unsigned int duration, unsigned int frequency, unsigned char amplitude);
		Tacton(const Tacton &t);
		~Tacton();

		//assignment overload
		Tacton &operator = (const Tacton &t);

		//changes the pattern using raw format
		void setPattern(char pattern);
		void setPattern(unsigned int frame, char pattern);
		//changes the pattern using string format
		void setPattern(char *pattern);
		void setPattern(const char *pattern);
		void setPattern(unsigned int frame, char *pattern);
		void setPattern(unsigned int frame, const char *pattern);
		//changes the duration
		void setDuration(unsigned int duration);
		void setDuration(unsigned int frame, unsigned int duration);
		//changes the frequency
		void setFrequency(unsigned int frequency);
		void setFrequency(unsigned int frame, unsigned int frequency);
		//changes the amplitude
		void setAmplitude(unsigned int amplitude);
		void setAmplitude(unsigned int frame, unsigned int amplitude);

		
		//returns the number of frames
		const unsigned int getNbFrames() const;

		//returns the raw code (useful to send to the serial port)
		void *rawCode() const;

	private:
		unsigned int _nbframes;
		unsigned char *_patterns;
		unsigned int *_durations;
		unsigned int *_frequencies;
		unsigned char *_amplitudes;
};

#endif
