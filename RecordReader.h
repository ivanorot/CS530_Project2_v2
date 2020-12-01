/************************************************
 * COURSE:          CS-530 Systems Programming
 * SECTION:         01 Synchronous TTh 1900-2015
 * PROGRAM #:       2
 * LAST MODIFIED:   [SUBMISSION DATE]
 * @author Ivan Orozco 82217656 cssc3012
 * @author Mariano Hernandez 820450001 cssc3062
 ************************************************/

/******************************************************************************
  * Program 02: RecordReader.h 
  *****************************************************************************
  * PROGRAM DESCRIPTION:
  * This header file includes type definitions used for the RecordReader 
  *****************************************************************************/
#pragma once

#ifndef RECORDREADER_H
#define RECORDREADER_H

#include <iostream>
#include <string>
#include <fstream>

#include "SymbolTable.h"
#include "TextRecord.h"

#define SYMTAB 1
#define LITTAB 2

using namespace std;

class RecordReader {
    private:
        ifstream inputFile;
        string programName;
        string programLength;
    public:
        void inputReader(string);
};
#endif

