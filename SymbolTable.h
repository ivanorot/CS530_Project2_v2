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
        
        
        //string fileName;       //prev
        //string *symbolNames;   //prev
        //int symbolAddress[0];  //prev
    
    public:
        void makeTable(string);
        string symbol, value, flags;
        string name, literal, length, address;
 
        SymbolTable();
        SymbolTable(string);
        
        tuple<int,string> getRowCol(int, string);
        //int getRowCol(int, string);
        string getData(int, int, string);
        string getByColValue(int, string, string, string);
};

#endif

