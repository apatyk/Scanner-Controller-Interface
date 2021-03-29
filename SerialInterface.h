#pragma once
#include <winbase.h> /* for serial port functions */
#include <stdio.h>
#include <Windows.h>
#include <Mmsystem.h>

#define MAX_LEN 32
#define CODE_LEN 16

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
