/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   30 November 2020
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

 /******************************************************************************
   * Program 02: OpcodeTable.h
   *****************************************************************************
   * PROGRAM DESCRIPTION:
   * This header file includes type definitions used for the OpcodeTable
   *****************************************************************************/

#ifndef OPCODETABLE_H
#define OPCODETABLE_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class OpcodeTable {
private:
    const string opcodes[59][3] = { { "ADD", "18", "3/4" }, { "ADDR", "90", "2" },  { "ADDF", "58", "3/4" },  { "AND", "40", "3/4" },
                              {"CLEAR", "B4", "2" },  { "COMP", "28", "3/4"}, { "COMPF", "88", "3/4" }, { "COMPR", "A0", "2" },
                              { "DIV", "24", "3/4" }, { "DIVR", "9C", "2" },  { "DIVF", "64", "3/4" },  { "FIX", "C4", "1" },
                              { "FLOAT", "C0", "1" }, { "HIO", "F4", "1" },   { "J", "3C", "3/4" },     { "JEQ", "30", "3/4" },
                              { "JGT", "34", "3/4" }, { "JLT", "38", "3/4" }, { "JSUB", "48", "3/4" },  { "LDA", "00", "3/4" },
                              { "LDB", "68", "3/4" }, { "LDCH", "50", "3/4"}, { "LDL", "08", "3/4" },   { "LDF", "70", "3/4" },
                              { "LDS", "6C", "3/4" }, { "LDT", "74", "3/4" }, { "LDX", "04", "3/4" },   { "LPS", "D0", "3/4" },
                              { "MUL", "20", "3/4" }, { "MULR", "98", "2" },  { "MULF", "60", "3/4" },  { "NORM", "C8", "1" },
                              { "OR", "44", "3/4" },  { "RD", "D8", "3/4" },  { "RMO", "AC", "2" },     { "RSUB", "4C", "3/4" },
                              { "SHIFTL", "A4", "2"}, { "SHIFTR", "A8", "2"}, { "SIO", "F0", "1" },     { "SSK", "EC", "3/4" },
                              { "STA", "0C", "3/4" }, { "STF", "80", "3/4" }, { "STB", "78", "3/4" },   { "STCH", "54", "3/4" },
                              { "STI", "D4", "3/4" }, { "STL", "14", "3/4" }, { "STS", "7C", "3/4" },   { "STSW", "E8", "3/4" },
                              { "STT", "84", "3/4" }, { "STX", "10", "3/4" }, { "SUB", "1C", "3/4" },   { "SUBR", "94", "2" },
                              { "SUBF", "5C", "3/4"}, { "SVC", "B0", "2" },   { "TD", "E0", "3/4" },    { "TIO", "F8", "1" },
                              { "TIX", "2C", "3/4" }, { "TIXR", "B8", "2" },  { "WD", "DC", "3/4" } };


   
public:
    int checkIfOpcode(string);
    string getOpcode(int);
    string getFormat(int);
};
#endif
