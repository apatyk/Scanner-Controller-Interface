#include "stdafx.h"
#include "SerialInterface.h"

void SerialInterface::initBarcodeScanner(void)
{
	readerOn = 1;
}

void SerialInterface::readBarcodeScanner(void)
{
	HANDLE hComm;
	DCB CommSettings;
	COMMTIMEOUTS CommTimeoutSettings;
	unsigned char SerialPortBuffer[10];
	DWORD BytesRead, i;
	unsigned short DataValue;
	DWORD EventType;

	/* open serial port and configure to talk to Datalogic barcode scanner */
	hComm = CreateFile(L"COM8", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Unable to connect to serial port COM8", L"Error", MB_OK | MB_APPLMODAL);
		return;
	}
	GetCommState(hComm, &CommSettings);
	CommSettings.BaudRate = 9600;
	CommSettings.fParity = 0;
	CommSettings.Parity = 0;
	CommSettings.ByteSize = 8;
	CommSettings.StopBits = 0;
	SetCommState(hComm, &CommSettings);
	GetCommTimeouts(hComm, &CommTimeoutSettings);
	CommTimeoutSettings.ReadIntervalTimeout = 40;			/* turn these timeouts off, or up to 20 or higher */
	CommTimeoutSettings.ReadTotalTimeoutConstant = 0;
	CommTimeoutSettings.ReadTotalTimeoutMultiplier = 0;
	SetCommTimeouts(hComm, &CommTimeoutSettings);			/* no timeouts on serial port read */
	SetCommMask(hComm, EV_RXCHAR);							/* set mask to fire when byte received */

	if (readerOn)
	{
		/* wait until first byte arrives, then read 3 (with 40ms timeout, which was set above) */
		WaitCommEvent(hComm, &EventType, NULL);
		/* get data from serial port */
		BytesRead = 0;
		while (BytesRead != 3)
			i = ReadFile(hComm, SerialPortBuffer, 3, &BytesRead, NULL);
		DataValue = ((unsigned short)(SerialPortBuffer[1] & 0x0F) << 8) + (unsigned short)(SerialPortBuffer[2]);
		serialNumber = (int)DataValue;
		char text[64];
		sprintf_s(text, "%d", serialNumber);
		PlaySoundA((LPCSTR)SND_ALIAS_SYSTEMASTERISK, NULL, SND_ALIAS_ID);
		MessageBox(NULL, (LPCWSTR)text, L"Success", MB_OK | MB_APPLMODAL);
		//new_aIBI_timestamp = (int)((long int)clock()*(long int)1000 / (long int)CLOCKS_PER_SEC); /* timestamp the IBI locally */
	}

	CloseHandle(hComm);
}

