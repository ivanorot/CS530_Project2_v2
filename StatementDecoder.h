#pragma once
/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   [SUBMISSION DATE]
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

 /******************************************************************************
   * Program 02: main.cpp
   *****************************************************************************
   * PROGRAM DESCRIPTION:
   * Starting point for the XE Disassembler Program
   *****************************************************************************
   * GUIDING ALGORITHM:
   * 1.
   *****************************************************************************/
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
        string checkLiteralFun(string);

};
