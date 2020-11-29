#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "SymbolTable.h"

using namespace std;

class StatementDecoder {
    private:
        SymbolTable symbolTable;


    public:
        StatementDecoder(string);
        
        string getStatement(int format, string targetAddress, string nixbpe);
        string formatTwo(string targetAddress);
        string registerMnemoic(char x);
        string formatThree(string targetAd, string nixbpe);
        string addressingMode(string nixbpe);
        string indexAddressing(string nixbpe);

};
