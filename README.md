# Barcode Scanner Controller Interface

This code is designed to interface with the Awoo SCB-100 scanner controller via serial port. Code is designed in C/C++ for Windows.

## Usage

To use, got to File > Search to start polling the COM port for data. The program will wait until data is presented on the COM port (program will be unresponsive). When the data is read, the serial number will be displayed in a message box after being converted from ASCII to Unicode. To scan another code, go to File > Search again.

## Note

`COM` port will need to be changed in code (`SerialInterface.cpp `) (e.g. `COM9`)
