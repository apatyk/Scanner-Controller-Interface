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
	DWORD EventType;
	UCHAR SerialPortBuffer[MAX_LEN] = { 0 };
	DWORD BytesRead, i, BarcodeLength = CODE_LEN;
	UCHAR SerialNumber[CODE_LEN];
	WCHAR DisplayNumber[CODE_LEN];

	// open serial port and configure to talk to scanner controller
	hComm = CreateFile(L"COM9", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Unable to connect to serial port COM9.", L"Error", MB_OK | MB_APPLMODAL);
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
	CommTimeoutSettings.ReadIntervalTimeout = 0;			/* turn these timeouts off, or up to 20 or higher */
	CommTimeoutSettings.ReadTotalTimeoutConstant = 0;
	CommTimeoutSettings.ReadTotalTimeoutMultiplier = 0;
	SetCommTimeouts(hComm, &CommTimeoutSettings);			/* no timeouts on serial port read */
	SetCommMask(hComm, EV_RXCHAR);							/* set mask to fire when byte received */

	if (readerOn)
	{
		// wait until first byte arrives, then read one byte for each character in barcode length (with timeout set above)
		WaitCommEvent(hComm, &EventType, NULL);
		// get data from serial port
		BytesRead = 0;
		while (BytesRead != BarcodeLength)
			i = ReadFile(hComm, SerialPortBuffer, BarcodeLength, &BytesRead, NULL);
		// remove space at beginning of buffer
		for (i = 0; i < BarcodeLength; i++)
			SerialNumber[i] = SerialPortBuffer[i + 1];
		// convert from unsigned char string to wide string (ASCII --> unicode)
		mbstowcs_s(NULL, DisplayNumber, BarcodeLength, (const char*)SerialNumber, MAX_LEN);
		MessageBox(NULL, DisplayNumber, L"Serial Number", MB_OK | MB_APPLMODAL);
	}

	CloseHandle(hComm);
}

