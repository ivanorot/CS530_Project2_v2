/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   30 November 2020
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

/******************************************************************************
  * Program 02: RecordReader.cpp
  *****************************************************************************
  * PROGRAM DESCRIPTION:
  * Opens .obj file and feeds into the TextRecord class.
  *****************************************************************************/

#include "RecordReader.h"

void RecordReader::inputReader(string fileName) {
    SymbolTable sym(fileName);
    
    string object = fileName + ".obj";
    const char* objFile = object.c_str();
    string inputLine;
    inputFile.open(objFile);
    TextRecord textRecord(fileName);
    
  
    cout << endl;
    cout << "Beginning disassembly" << endl;
    
    if (!inputFile.is_open()) {
        cout << "Error with file\n";
        cerr << "Check to make sure file exists within current directory\n";
    }
    
    while (inputFile.good()) {
        getline(inputFile, inputLine);
        
        if (inputLine[0] == 'H') {
             programName += (inputLine.substr(1, 5));
             programLength += (inputLine.substr(13, 5));
             //cout << programName << endl;
        }
        else if (inputLine[0] == 'T') {
            //Col 1 == T
            //Col 2-7 == Starting Address
            //Col 8-9 == Length of record in bytes
            //Col 10-69 == Object code
            textRecord.readLine(inputLine);
        }
   }
    textRecord.print(programName, "0");
    cout << "Disassembly completed" << endl << endl;
}
