#ifndef TEXTRECORD_H
#define TEXTRECORD_H

#include <iostream>
#include <string>
#include <cmath>
#include <list>

#include "SymbolTable.h"
#include "StatementDecoder.h"
#include "OpcodeTable.h"

#define SYMTAB 1
#define LITTAB 2

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
        list<string> statements;
        SymbolTable sym;
        string fileName;
        int base;
        
    public:
        TextRecord();
        TextRecord(string);
        void saveStatement(int, string, string);

        void print();
            
        void readLine(string inputLine);
        
        int checkLiteral(string);
        
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
