#pragma once
/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   30 November 2020
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

 /******************************************************************************
   * Program 02: StatementDecoder.h
   *****************************************************************************
   * PROGRAM DESCRIPTION:
   * This header file includes type definitions used for the StatementDecoder
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
