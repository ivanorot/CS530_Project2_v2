#ifndef TEXTRECORD_H
#define TEXTRECORD_H

#include <iostream>
#include <string>
#include <cmath>
#include <list>

#include "OpcodeTable.h"

using namespace std;

class TextRecord {
    private:
        int startingAddress;
        int addressCounter;
        int recordLength;
        OpcodeTable opcodeTable;
        list<string> mnemonicsList;
        list<int> addressList;
        list<string> tAList;
        
    public:
        TextRecord();

        void print();
            
        void readLine(string inputLine);
        
        void readInstructionsLoop(string);
        
        int getOpcodeNum(string);
        
        int findOpcodeFormat(int);

        list<int> returnAddress();
        
        string stringHexToStringBinary(string);
        
        string stringBinaryToStringHex(string);
        
        string intDecimalToStringHex(int);
        
        int stringHexToIntDecimal(string);
        
        string charHextoStringBinary(char);
        
        int charNumToIntNum(char);
        
        char zeroToFifteenIntToHexChar(int);
        
        int stringBinaryToIntDecimal(string);
};

#endif
