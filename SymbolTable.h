#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
        string symbolfile;
        ifstream inputFile;
        vector<Metadata> symboltable;
        vector<Metadata> literaltable;
        void set(int, int, string, string);
        void makeTable(string);
        
        string fileName;       //prev
        string *symbolNames;   //prev
        int symbolAddress[0];  //prev
    
    public:
        SymbolTable();
        SymbolTable(string);
                 
        string getData(int, int, string);
        string getByColValue(int, string, string, string);
};

#endif

