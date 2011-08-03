#ifndef _SERIALWINDOWS_
#define _SERIALWINDOWS_

#include "Serial.hpp"

#include <windows.h>

class SerialWindows : public Serial
{
    public:
        //Initialize Serial communication with the given COM port
        SerialWindows(const char *portName);
        //Close the connection
        //NOTA: for some reason you can't connect again before exiting
        //the program and running it again
        ~SerialWindows();
        //Read data in a buffer, if nbChar is greater than the
        //maximum number of bytes available, it will return only the
        //bytes available. The function return -1 when nothing could
        //be read, the number of bytes actually read.
        int ReadData(void *buffer, unsigned int nbChar);
        //Writes data from a buffer through the Serial connection
        //return true on success.
        bool WriteData(void *buffer, unsigned int nbChar);


    private:
        //Serial comm handler
        HANDLE _hSerial;
        //Get various information about the connection
        COMSTAT _status;
        //Keep track of last error
        DWORD _errors;
};
#endif
