#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
        vector<Metadata> table;
        void set(int, string, string);
        void makeTable(string);
        
        string fileName;       //prev
        string *symbolNames;   //prev
        int symbolAddress[0];  //prev
    
    public:
        SymbolTable();
        SymbolTable(string);
                 
        string getData(int, string);
        string getByColValue(string, string, string);
};

#endif

