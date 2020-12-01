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
   * Structure for two user accessible tables, SYMTAB and LITTAB
   *****************************************************************************/

#include "SymbolTable.h"

/******************************* Metadata Class *******************************/
// underlying structure to store information from the .sym file
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


// Get the row and column of a given value if found in the table
tuple<int,string> SymbolTable::getRowCol(int table, string value) {
     if (SYMTAB == table) {
        for (unsigned int i = 0; i < symboltable.size(); i++) {
            if (symboltable[i].getData() == value)
                return make_tuple(symboltable[i].getRow(),symboltable[i].getCol());
        }
        return make_tuple(-1,"Not in table");
    }
    
    if (LITTAB == table) {
        for (unsigned int i = 0; i < literaltable.size(); i++) {
            if (literaltable[i].getData() == value)
                return make_tuple(literaltable[i].getRow(),literaltable[i].getCol());
        }
        return make_tuple(-1,"Not in table");
    }
   
}


// Get data in table given a row and column
string SymbolTable::getData(int table, int row, string column) {
    if (SYMTAB == table) {
        for (unsigned int i = 0; i < symboltable.size(); i++) {
            if (symboltable[i].getRow() == row && 
                symboltable[i].getCol() == column)
                return symboltable[i].getData();
        }
        return "";
    }
    
    if (LITTAB == table) {
        for (unsigned int i = 0; i < literaltable.size(); i++) {
            if (literaltable[i].getRow() == row && 
                literaltable[i].getCol() == column)
                return literaltable[i].getData();
        }
        return "";
    }
}

// Given a column, get data next to a another given value and it’s column
string SymbolTable::getByColValue(int table, string col1, string data, string col2) {
    if (SYMTAB == table) {
        int row;
        int found = 0;
         
        for (unsigned int i = 0; i < symboltable.size() && !found; i++) {
            if (symboltable[i].getCol() == col1 && 
                symboltable[i].getData() == data) {
                
                row = symboltable[i].getRow();
                found = 1;
            }
        }
                
        if (found) {
            for (unsigned int i = 0; i < symboltable.size(); i++) {
                if (symboltable[i].getRow() == row && 
                    symboltable[i].getCol() == col2)
                    return symboltable[i].getData();
            }
            return "Error: Row and Column do not exist in this symboltable";
        }
        else return "Error: Row and Column do not exist in this symboltable";
    }
    
    if (LITTAB == table) {
        int row;
        int found = 0;
         
        for (unsigned int i = 0; i < literaltable.size() && !found; i++) {
            if (literaltable[i].getCol() == col1 && 
                literaltable[i].getData() == data) {
                
                row = literaltable[i].getRow();
                found = 1;
            }
        }
                
        if (found) {
            for (unsigned int i = 0; i < literaltable.size(); i++) {
                if (literaltable[i].getRow() == row && 
                    literaltable[i].getCol() == col2)
                    return literaltable[i].getData();
            }
            return "Error: Row and Column do not exist in this literaltable";
        }
        else return "Error: Row and Column do not exist in this literaltable";
    }
}

// store data in table
void SymbolTable::set(int table, int row, string column, string data) {
    if (SYMTAB == table) symboltable.push_back(Metadata(row, column, data));
    if (LITTAB == table) literaltable.push_back(Metadata(row, column, data));
}

// create two user accessible tables: SYMTAB & LITTAB
void SymbolTable::makeTable(string fileName) {
    string file = fileName + ".sym";
    const char* symbolFile = file.c_str();
    
    inputFile.open(symbolFile);
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
    
    for (int i = 0; i < sym_col.size(); i++) {
        if ( ((sym_col.at(i)).substr(0,3)).compare("Sym") == 0 ||
             ((sym_col.at(i)).substr(0,3)).compare("sym") == 0 ) 
            this->symbol = sym_col.at(i);
        if ( ((sym_col.at(i)).substr(0,3)).compare("Val") == 0 ||
             ((sym_col.at(i)).substr(0,3)).compare("val") == 0 ) 
            this->value = sym_col.at(i);
        if ( ((sym_col.at(i)).substr(0,3)).compare("Fla") == 0 ||
             ((sym_col.at(i)).substr(0,3)).compare("fla") == 0 ) 
            this->flags = sym_col.at(i);
    }
    
    int i = 0;
    while (inputFile.good()) {
        getline(inputFile, inputLine);
        if (inputLine.empty()) break;
        
        if ( !((inputLine.substr(0,3)).compare("---") == 0) ) {
            //cout << inputLine << endl;
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
    
     for (int i = 0; i < lit_col.size(); i++) {
        if ( ((lit_col.at(i)).substr(0,3)).compare("Nam") == 0 ||
             ((lit_col.at(i)).substr(0,3)).compare("nam") == 0 ) 
            this->name = lit_col.at(i);
        if ( ((lit_col.at(i)).substr(0,3)).compare("Lit") == 0 ||
             ((lit_col.at(i)).substr(0,3)).compare("lit") == 0 ) 
            this->literal = lit_col.at(i);
        if ( ((lit_col.at(i)).substr(0,3)).compare("Len") == 0 ||
             ((lit_col.at(i)).substr(0,3)).compare("len") == 0 ) 
            this->length = lit_col.at(i);
        if ( ((lit_col.at(i)).substr(0,3)).compare("Add") == 0 ||
             ((lit_col.at(i)).substr(0,3)).compare("add") == 0 ) 
            this->address = lit_col.at(i);
    }

    
    i = 0;
    while (inputFile.good()) {
        getline(inputFile, inputLine);
        if (inputLine.empty()) break;
        
        if ( !((inputLine.substr(0,3)).compare("---") == 0) ) {
            //cout << inputLine << endl;
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

