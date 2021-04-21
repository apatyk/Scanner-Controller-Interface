#pragma once
#include <winbase.h> /* for serial port functions */
#include <stdio.h>
#include <Windows.h>
#include <Mmsystem.h>

// 23-digits for serialized sub-compoments
// 15-digits for washing machines
#define MAX_LEN 32
// to account for space at the beginning of the code
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
