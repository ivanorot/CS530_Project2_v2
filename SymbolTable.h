/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   30 November 2020
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

 /******************************************************************************
   * Program 02: SymbolTable.cpp
   *****************************************************************************
   * PROGRAM DESCRIPTION:
   * This header file includes type definitions used for the SymbolTable
   *****************************************************************************/

#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

#define SYMTAB 1
#define LITTAB 2

using namespace std;

class Metadata {
    private:
        int row;
        string col;
        string data;
    
    public:
        Metadata(); 
        Metadata(int, string, string);
        
        int getRow();
        string getCol();
        string getData();
};

class SymbolTable {
    private:
        ifstream inputFile;
        string inputLine;
        
        vector<string> sym_col;
        vector<string> lit_col; 
        vector<Metadata> symboltable;
        vector<Metadata> literaltable;
        
        void set(int, int, string, string);
        
    public:
        void makeTable(string);
        string symbol, value, flags;
        string name, literal, length, address;
 
        SymbolTable();
        SymbolTable(string);
        
        tuple<int,string> getRowCol(int, string);
        string getData(int, int, string);
        string getByColValue(int, string, string, string);
};

#endif

