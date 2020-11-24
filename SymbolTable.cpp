#include "SymbolTable.h"

/******************************* Metadata Class *******************************/

Metadata::Metadata() {}

Metadata::Metadata(int number, string name, string data) {
    this->row = number;
    this->col = name;
    this->data = data;
}
 
int Metadata::getRow()     { return this->row;  }
string Metadata::getCol()  { return this->col;  }
string Metadata::getData() { return this->data; }



/***************************** SymbolTable Class ******************************/

SymbolTable::SymbolTable() {}

SymbolTable::SymbolTable(string fileName) {
    this->SymbolTable::makeTable(fileName);
}
        
        
string SymbolTable::getData(int table, int row, string column) {
    if (SYMTAB == table) {
        for (unsigned int i = 0; i < symboltable.size(); i++) {
            if (symboltable[i].getRow() == row && symboltable[i].getCol() == column)
                return symboltable[i].getData();
        }
        return "Error: Chosen Row and Column do not exist in this symboltable";
    }
    
    if (LITTAB == table) {
        for (unsigned int i = 0; i < literaltable.size(); i++) {
            if (literaltable[i].getRow() == row && literaltable[i].getCol() == column)
                return literaltable[i].getData();
        }
        return "Error: Chosen Row and Column do not exist in this literaltable";
    }
}
        
string SymbolTable::getByColValue(int table, string col1, string data, string col2) {
    if (SYMTAB == table) {
        int row;
        int found = 0;
         
        for (unsigned int i = 0; i < symboltable.size() && !found; i++) {
            if (symboltable[i].getCol() == col1 && symboltable[i].getData() == data) {
                row = symboltable[i].getRow();
                found = 1;
            }
        }
                
        if (found) {
            for (unsigned int i = 0; i < symboltable.size(); i++) {
                if (symboltable[i].getRow() == row && symboltable[i].getCol() == col2)
                            return symboltable[i].getData();
            }
            return "Error: Chosen Row and Column do not exist in this symboltable";
        }
        else return "Error: Chosen Row and Column do not exist in this symboltable";
    }
    
    if (LITTAB == table) {
        int row;
        int found = 0;
         
        for (unsigned int i = 0; i < literaltable.size() && !found; i++) {
            if (literaltable[i].getCol() == col1 && literaltable[i].getData() == data) {
                row = literaltable[i].getRow();
                found = 1;
            }
        }
                
        if (found) {
            for (unsigned int i = 0; i < literaltable.size(); i++) {
                if (literaltable[i].getRow() == row && literaltable[i].getCol() == col2)
                            return literaltable[i].getData();
            }
            return "Error: Chosen Row and Column do not exist in this literaltable";
        }
        else return "Error: Chosen Row and Column do not exist in this literaltable";
    }
}

void SymbolTable::set(int table, int row, string column, string data) {
    if (SYMTAB == table)
        symboltable.push_back(Metadata(row, column, data));
    if (LITTAB == table)
        literaltable.push_back(Metadata(row, column, data));
}

void SymbolTable::makeTable(string fileName) {
    string symbol = fileName + ".sym";
    const char* symbolFile = symbol.c_str();
    string inputLine;
    inputFile.open(symbolFile);
    vector<string> sym_col;
    vector<string> lit_col;
    
    if (!inputFile.is_open()) {
        cout << "Error with file\n";
        cerr << "Check to make sure file exists within current directory\n";
    }
    
    getline(inputFile, inputLine);
    istringstream sym_buf(inputLine);
    for (string col; sym_buf >> col; ) {
        //cout << col << endl;
        sym_col.push_back(col);
    }
    //cout << "col size: " << sym_col.size() << endl;
    
    //for (int i=0; i < sym_col.size(); i++) {
    //    cout << sym_col.at(i) << ' ';
    //}
    
    int i = 0;
    while (inputFile.good()) {
        getline(inputFile, inputLine);
        if (inputLine.empty()) break;
        
        if ( !((inputLine.substr(0,3)).compare("---") == 0) ) {
            cout << inputLine << endl;
            istringstream buf(inputLine);
            string val;
            for (int j = 0; buf >> val; j++) {
                this->SymbolTable::set(SYMTAB,i,sym_col.at(j),val);
            }
            i++;
        }
    }
    
    getline(inputFile, inputLine);
    istringstream lit_buf(inputLine);
    for (string col; lit_buf >> col; ) {
        //cout << col << endl;
        lit_col.push_back(col);
    }
    
    i = 0;
    while (inputFile.good()) {
        getline(inputFile, inputLine);
        if (inputLine.empty()) break;
        
        if ( !((inputLine.substr(0,3)).compare("---") == 0) ) {
            cout << inputLine << endl;
            istringstream buf(inputLine);
            string val;
            int k = 0;
            for (int j = 0; buf >> val; j++) {
                if ( ((inputLine.substr(k,6)).compare("      ") == 0) ) {
                    this->SymbolTable::set(LITTAB,i,lit_col.at(j),"n/a");
                    j++;
                    k += 7;
                }
                this->SymbolTable::set(LITTAB,i,lit_col.at(j),val);
                k += 7;
            }
            i++;
        }
    }
}

