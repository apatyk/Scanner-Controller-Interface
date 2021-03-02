#pragma once
#include <winbase.h> /* for serial port functions */
#include <stdio.h>
#include <Windows.h>
#include <Mmsystem.h>


class SerialInterface {
public:
	static SerialInterface & getInstance()
	{
		static SerialInterface instance;
		return instance;
	}
	void readBarcodeScanner(void);
	void initBarcodeScanner(void);
private:
	int serialNumber;
	bool readerOn;
};
