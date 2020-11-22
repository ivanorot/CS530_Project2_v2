#include "SymbolTable.h"

using namespace std;

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
        
        
string SymbolTable::getData(int row, string column) {
    for (unsigned int i = 0; i < table.size(); i++) {
        if (table[i].getRow() == row && table[i].getCol() == column)
            return table[i].getData();
    }
    return "Error: Chosen Row and Column do not exist in this table";
}
        
string SymbolTable::getByColValue(string col1, string data, string col2) {
    int row;
    int found = 0;
     
    for (unsigned int i = 0; i < table.size() && !found; i++) {
        if (table[i].getCol() == col1 && table[i].getData() == data) {
            row = table[i].getRow();
            found = 1;
        }
    }
            
    if (found) {
        for (unsigned int i = 0; i < table.size(); i++) {
            if (table[i].getRow() == row && table[i].getCol() == col2)
                        return table[i].getData();
        }
        return "Error: Chosen Row and Column do not exist in this table";
    }
    else return "Error: Chosen Row and Column do not exist in this table";
}

void SymbolTable::set(int row, string column, string data) {
    table.push_back(Metadata(row, column, data));
}

void SymbolTable::makeTable(string fileName) {
    string symbol = fileName + ".sym";
    const char* symbolFile = symbol.c_str();
    string inputLine;
//    string column;
    inputFile.open(symbolFile);
    vector<string> column;
    
    if (!inputFile.is_open()) {
        cout << "Error with file\n";
        cerr << "Check to make sure file exists within current directory\n";
    }
    
    getline(inputFile, inputLine);
    istringstream buf(inputLine);
    for (string col; buf >> col; ) {
        //cout << col << endl;
        column.push_back(col);
    }
    //cout << "col size: " << column.size() << endl;
    
    //for (int i=0; i < column.size(); i++) {
    //    cout << column.at(i) << ' ';
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
                this->SymbolTable::set(i,column.at(j),val);
            }
            i++;
        }
    }
   
    //Private method set used to create the table
    //this->SymbolTable::set(1,"Symbol","FIRST");
    //this->SymbolTable::set(1,"Value","000000");
    //this->SymbolTable::set(1,"Flags","R");
    
    //this->SymbolTable::set(2,"Symbol","LOOP");
    //this->SymbolTable::set(2,"Value","00000B");
    //this->SymbolTable::set(2,"Flags","R");
    
    //this->SymbolTable::set(3,"Symbol","COUNT");
    //this->SymbolTable::set(3,"Value","00001E");
    //this->SymbolTable::set(3,"Flags","R");
    
    //this->SymbolTable::set(4,"Symbol","TABLE");
    //this->SymbolTable::set(4,"Value","000021");
    //this->SymbolTable::set(4,"Flags","R");
    
    //cout << "*****************USER DEMO*****************" << endl << endl;
    
    //cout << this->SymbolTable::getData(1,"Symbol") << endl;
    //cout << this->SymbolTable::getData(1,"Value") << endl;
    //cout << this->SymbolTable::getData(2,"Value") << endl;
    //cout << this->SymbolTable::getByColValue("Value","00001E","Symbol") << endl;
    //cout << this->SymbolTable::getByColValue("Symbol","COUNT","Flags") << endl;

    //cout << "*****************USER DEMO*****************" << endl << endl;

}

