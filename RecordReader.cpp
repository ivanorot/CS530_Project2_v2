/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   [SUBMISSION DATE]
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

/******************************************************************************
  * Program 02: RecordReader.cpp
  *****************************************************************************
  * PROGRAM DESCRIPTION:
  * 
  *****************************************************************************
  * GUIDING ALGORITHM:
  * 1. 
  *****************************************************************************/

#include "RecordReader.h"

void RecordReader::inputReader(string fileName) {
    string object = fileName + ".txt";
    const char* objFile = object.c_str();
    string inputLine;
    inputFile.open(objFile);
    TextRecord textRecord;
    
    //SymbolTable symtab(fileName);
   // cout << endl << symtab.getData(2,"Symbol") << endl << endl;
    
    if (!inputFile.is_open()) {
        cout << "Error with file\n";
        cerr << "Check to make sure file exists within current directory\n";
    }
    
    // while (inputFile.good()) {
    //     getline(inputFile, inputLine);
    //     cout << inputLine << endl;
    // }
    
    while (inputFile.good()) {
        getline(inputFile, inputLine);
        
        if (inputLine[0] == 'H') {
             programName += (inputLine.substr(1, 5));
             cout << programName << endl;
        }
        else if (inputLine[0] == 'T') {
            //Col 1 == T
            //Col 2-7 == Starting Address
            //Col 8-9 == Length of record in bytes
            //Col 10-69 == Object code
            textRecord.readLine(inputLine);
        }
//       else if (inputLine[0] == 'M') {
//           //2-7 starting location of the address to be
//           //modified(relative to the begging of the program)
//           //8-9length of the address field to be modified
//       }
//       else if (inputLine[0] == 'E') { 
//           //2-7 Address first executable instruction
//           //hhg
//       }
   }
}

