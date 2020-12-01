#ifndef TEXTRECORD_H
#define TEXTRECORD_H

#include <iostream>
#include <fstream>
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
        list<string> addressList;
        list<string> tAList;
        list<string> statements;
        SymbolTable sym;
        string fileName;
        int base;
        list<string> instList;
        
        ofstream lisFile;
        ofstream sicFile;

        
    public:

        //void printLis(string);

        TextRecord();

        TextRecord(string);

        void saveStatement(int, string, string);

        string getSixLength(string);

        void print(string, string);
            
        void readLine(string inputLine);
        
        int checkLiteral(string);

        bool checkBase(string mneumonic);
        
        void readInstructionsLoop(string);
        
        int getOpcodeNum(string);
        
        int findOpcodeFormat(int);

        list<string> returnAddress();
        
        string stringHexToStringBinary(string);
        
        string stringBinaryToStringHex(string);
        
        string intDecimalToStringHex(int);
        
        int stringHexToIntDecimal(string);
        
        string charHextoStringBinary(char);
        
        int charNumToIntNum(char);
        
        char zeroToFifteenIntToHexChar(int);
        
        int stringBinaryToIntDecimal(string);
        
        string checkLiteralFun(int);

        string checkSymbolFun(int);

        string checkLiteralAddress(int);

        string checkSymbolAddress(int);
        
        string getSymbolwithStringAddress(string);
};

#endif
