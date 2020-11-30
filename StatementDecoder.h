#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "SymbolTable.h"
#include "TextRecord.h"

using namespace std;

class StatementDecoder {
    private:
        SymbolTable symbolTable;
        int base;
        int progC;
        string fileName;

    public:
        string getSixLength(string);
        StatementDecoder(string, int, int);
        int format4check(string);
        string getSymbol(string, string);
        string getStatement(int format, string targetAddress, string nixbpe);
        string formatTwo(string targetAddress);
        string registerMnemoic(char x);
        string formatThree(string targetAd, string nixbpe);
        string addressingMode(string nixbpe);
        string indexAddressing(string nixbpe);
        string checkSymbolFun(string);
        

};
