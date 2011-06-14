#include "SerialWindows.hpp"

#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#endif

SerialWindows::SerialWindows(char *portName)
:Serial(portName)
{
    //Try to connect to the given port throuh CreateFile
    _hSerial = CreateFileA(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, //FILE_ATTRIBUTE_NORMAL,
            NULL);

    //Check if the connection was successfull
    if(_hSerial == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if(GetLastError() == ERROR_FILE_NOT_FOUND)
            cerr << "ERROR: Handle was not attached. Reason: " << portName << " not available." << endl;
        else
            cerr << "ERROR unknown" << endl;
		char buffer[256];
		sprintf(buffer, "Port %s does not exist or not reachable", portName);
		throw buffer;
    }
    else
    {
	/*	
	COMMTIMEOUTS commTimeouts;
	commTimeouts.ReadIntervalTimeout = 1;
	commTimeouts.ReadTotalTimeoutMultiplier = 10;
	commTimeouts.ReadTotalTimeoutConstant = 100;
	commTimeouts.WriteTotalTimeoutMultiplier = 10;
	commTimeouts.WriteTotalTimeoutConstant = 100;
	if (SetCommTimeouts(_comport, &commTimeouts) == 0)
		throw "Cannot set COM port timeouts";*/


        //If connected we try to set the comm parameters
        DCB dcbSerialParams = {0};

        //Try to get the current
        if (!GetCommState(_hSerial, &dcbSerialParams))
            //If impossible, show an error
            cerr << "ERROR: failed to get current serial parameters!" << endl;
        else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate=CBR_57600;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;

             //Set the parameters and check for their proper application
             if(!SetCommState(_hSerial, &dcbSerialParams))
                cerr << "ERROR: Could not set Serial Port parameters" << endl;
             else
             {
                 //If everything went fine we're connected
                 _connected = true;
                 //We wait 2s as the arduino board will be reseting
				 Sleep(2000);
                 //SDL_Delay(ARDUINO_WAIT_TIME);
             }
        }
    }
}

SerialWindows::~SerialWindows()
{
    //Check if we are connected before trying to disconnect
    if(_connected)
    {
        //We're no longer connected
        _connected = false;
        //Close the serial handler
        CloseHandle(_hSerial);
    }
}

int SerialWindows::ReadData(void *buffer, unsigned int nbChar)
{
    //Number of bytes we'll have read
    DWORD bytesRead = 0;
    //Number of bytes we'll really ask to read
    unsigned int toRead = 0;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(_hSerial, &_errors, &_status);

    //Check if there is something to read
    if(_status.cbInQue > 0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if(_status.cbInQue > nbChar)
			toRead = nbChar;
        else
			toRead = _status.cbInQue;

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(_hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
            return bytesRead;
    }

    //If nothing has been read, or that an error was detected return -1
    return -1;
}


bool SerialWindows::WriteData(void *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if(!WriteFile(_hSerial, buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(_hSerial, &_errors, &_status);

        return false;
    }
    else
	{
        ClearCommError(_hSerial, &_errors, &_status);
/*		if(!FlushFileBuffers(_hSerial))
			cout << "ERROR while flushing" << endl;*/
/*		stringstream s;
		s << bytesSend << " SENT" << endl;
		OutputDebugString(s.str().c_str());*/
        return true;
	}
}
