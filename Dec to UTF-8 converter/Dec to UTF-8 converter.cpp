// Dec to UTF-8 converter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>


using namespace std;

string decToHex(int decValue) {
	stringstream ss;
	ss << hex << decValue; // convert to hex
	string hexValue(ss.str()); // store in hexValue string
	return hexValue;
}

string binToHex(string bin) {

	int res = 0;

	for (int count = 0; count < bin.length(); ++count)
	{
		res *= 2;
		res += bin[count] == '1' ? 1 : 0;
	}

	stringstream ss2;
	//ss << "0x" << hex << setw(8) << setfill('0') << concatArr;
	ss2 << hex << res;

	string hexVal(ss2.str());
	//cout << "Hex value: " << hexVal << endl;

	return hexVal;
}

string intArrToString(int intArr[], int sizeOfArr) {
	ostringstream oss("");
	for (int temp = 0; temp < sizeOfArr; temp++)
		oss << intArr[temp];
	return oss.str();
}

int main()
{
	cout << "Enter decimal value:\n";
	int decValue;
	cin >> decValue;

	string hexValue = decToHex(decValue);

	cout << "Hex: " << hexValue << endl;
	string hexCode = "0x";
	hexCode.append(hexValue);
	cout << "appended: " << hexCode << endl;

	bitset<21> bin21Symbols (decValue);
	cout << "Bin: " << bin21Symbols << endl;

	
	int binArr[21];
	
	cout << "BinArr:" << endl;
	for (int i = 0; i < 21; ++i) {
		binArr[i] = bin21Symbols[20-i];
		cout << binArr[i];
	}
	cout << "\n";
	

	// from table, except dec values are checked instead of hex values
	if (decValue >= 0 && decValue <= 127) {
		int byte1[8];
		byte1[0] = 0;
		cout << "Byte1: " << binArr[0];
		int j = 14; // 21-7=14, 21 because the bitset has 21 symbols; 7 because the 1st and only byte (using the table) is formed from 7 bits
		for (int i = 1; i < 8; ++i) {
			byte1[i] = binArr[j];
			cout << byte1[i];
			++j;
		}
		cout << "\n";

		string str = intArrToString(byte1, 8);
		cout << "UTF-8: " << binToHex(str) << endl;
	}
	else if (decValue >= 128 && decValue <= 2047) {
		int byte1[8];
		byte1[0] = 1;
		byte1[1] = 1;
		byte1[2] = 0;

		cout << "Byte1: ";
		for (int i = 0; i < 3; ++i) {
			cout << byte1[i];
		}
		int j = 10; // 21-11=10, 11 because the 1st byte is formed from 5 bits and the 2nd byte is formed from 6 bits, 5+6=11
		for (int i = 3; i < 8; ++i) {
			byte1[i] = binArr[j];
			cout << byte1[i];
			++j;
		}
		cout << "\n";

		int byte2[8];
		byte2[0] = 1;
		byte2[1] = 0;

		cout << "Byte2: ";
		for (int i = 0; i < 2; ++i) {
			cout << byte2[i];
		}
		for (int i = 2; i < 8; ++i) {
			byte2[i] = binArr[j];
			cout << byte2[i];
			++j;
		}
		cout << "\n";

		int concatArr[16];
		cout << "concatArr[16]:\n";
		
		for (int i = 0; i < 8; ++i) {
			concatArr[i] = byte1[i];
			cout << concatArr[i];
		}
		j = 8;
		while (j < 16) {
			for (int i = 0; i < 8; ++i) {
				concatArr[j] = byte2[i];
				cout << concatArr[j];
				++j;
			}
		}
		cout << "\n";
		
		string str = intArrToString(concatArr, 16);
		cout << "UTF-8: " << binToHex(str) << endl;
	}
	else if (decValue >= 2048 && decValue <= 65535) {
	int byte1[8];
	byte1[0] = 1;
	byte1[1] = 1;
	byte1[2] = 1;
	byte1[3] = 0;

	cout << "Byte1: ";
	for (int i = 0; i < 4; ++i) {
		cout << byte1[i];
	}
	int j = 5; // 21-16=5, 16 because the 1st byte is formed from 4 bits, the 2nd byte is formed from 6 bits and the 3rd also from 6bits, 4+6+6=16
	for (int i = 4; i < 8; ++i) {
		byte1[i] = binArr[j];
		cout << byte1[i];
		++j;
	}
	cout << "\n";

	
	int byte2[8];
	byte2[0] = 1;
	byte2[1] = 0;

	cout << "Byte2: ";
	for (int i = 0; i < 2; ++i) {
		cout << byte2[i];
	}
	for (int i = 2; i < 8; ++i) {
		byte2[i] = binArr[j];
		cout << byte2[i];
		++j;
	}
	cout << "\n";

	int byte3[8];
	byte3[0] = 1;
	byte3[1] = 0;

	cout << "Byte3: ";
	for (int i = 0; i < 2; ++i) {
		cout << byte3[i];
	}
	for (int i = 2; i < 8; ++i) {
		byte3[i] = binArr[j];
		cout << byte3[i];
		++j;
	}
	cout << "\n";


	int concatArr[24];
	cout << "concatArr[24]:\n";

	for (int i = 0; i < 8; ++i) {
		concatArr[i] = byte1[i];
		cout << concatArr[i];
	}
	j = 8;
	while (j < 16) {
		for (int i = 0; i < 8; ++i) {
			concatArr[j] = byte2[i];
			cout << concatArr[j];
			++j;
		}
	}
	j = 16;
	while (j < 24) {
		for (int i = 0; i < 8; ++i) {
			concatArr[j] = byte3[i];
			cout << concatArr[j];
			++j;
		}
	}
	cout << "\n";

	string str = intArrToString(concatArr, 24);
	cout << "UTF-8: " << binToHex(str) << endl;

	}
	else if (decValue >= 65536 && decValue <= 1114111) {
	int byte1[8];
	byte1[0] = 1;
	byte1[1] = 1;
	byte1[2] = 1;
	byte1[3] = 1;
	byte1[4] = 0;

	cout << "Byte1: ";
	for (int i = 0; i < 5; ++i) {
		cout << byte1[i];
	}
	int j = 0; // 21-21=0, subtrahend is 21 because 1st byte formed from 3bits, other three bytes each formed from 6bits, 3+3*6=21
	for (int i = 5; i < 8; ++i) {
		byte1[i] = binArr[j];
		cout << byte1[i];
		++j;
	}
	cout << "\n";


	int byte2[8];
		byte2[0] = 1;
		byte2[1] = 0;

		cout << "Byte2: ";
		for (int i = 0; i < 2; ++i) {
			cout << byte2[i];
		}
		for (int i = 2; i < 8; ++i) {
			byte2[i] = binArr[j];
			cout << byte2[i];
			++j;
		}
		cout << "\n";
	
		int byte3[8];
		byte3[0] = 1;
		byte3[1] = 0;

		cout << "Byte3: ";
		for (int i = 0; i < 2; ++i) {
			cout << byte3[i];
		}
		for (int i = 2; i < 8; ++i) {
			byte3[i] = binArr[j];
			cout << byte3[i];
			++j;
		}
		cout << "\n";

		int byte4[8];
		byte4[0] = 1;
		byte4[1] = 0;

		cout << "Byte4: ";
		for (int i = 0; i < 2; ++i) {
			cout << byte4[i];
		}
		for (int i = 2; i < 8; ++i) {
			byte4[i] = binArr[j];
			cout << byte4[i];
			++j;
		}
		cout << "\n";


		int concatArr[32];
		cout << "concatArr[32]:\n";

		for (int i = 0; i < 8; ++i) {
			concatArr[i] = byte1[i];
			cout << concatArr[i];
		}
		j = 8;
		while (j < 16) {
			for (int i = 0; i < 8; ++i) {
				concatArr[j] = byte2[i];
				cout << concatArr[j];
				++j;
			}
		}
		j = 16;
		while (j < 24) {
			for (int i = 0; i < 8; ++i) {
				concatArr[j] = byte3[i];
				cout << concatArr[j];
				++j;
			}
		}
		j = 24;
		while (j < 32) {
			for (int i = 0; i < 8; ++i) {
				concatArr[j] = byte4[i];
				cout << concatArr[j];
				++j;
			}
		}
		cout << "\n";

		string str = intArrToString(concatArr, 32);
		cout << "UTF-8: " << binToHex(str) << endl;

	}
	
	
	return 0;
}

