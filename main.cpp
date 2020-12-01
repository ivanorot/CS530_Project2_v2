/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   [SUBMISSION DATE]
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

/******************************************************************************
  * Program 02: main.cpp
  *****************************************************************************
  * PROGRAM DESCRIPTION:
  * Starting point for the XE Disassembler Program
  *****************************************************************************
  * GUIDING ALGORITHM:
  * 1. 
  *****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "RecordReader.h"


using namespace std;

int main(int argc, char* argv[]) {
    cout << "CS-530: Systems Programming\n";
    cout << "Program 2: A Disassembler Program\n";
    cout << "@author Ivan Orozco 82217656 cssc3012\n";
    cout << "@author Mariano Hernandez 820450001 cssc3062\n\n";
    

    if (argc != 2) {
        cout << "Incorrect number of arguemnts\n";
        cerr << "Correct usage: dis <filename>\n";
       // return 1;    
    }
    
    string fileName = argv[1];
    //string objFile = fileName + ".obj";
    //string symFile = fileName + ".sym";
   
    //cout << "Looking for files:\n";
    //cout << objFile << endl;
    //cout << symFile << endl;
    
    RecordReader disassembler;
    disassembler.inputReader(fileName);
    
    return 0;
}

