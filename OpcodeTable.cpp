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
#pragma once
#include "OpcodeTable.h"

 int OpcodeTable::checkIfOpcode(string inOpcode) {
        for (int i = 0; i < 59; i++) {
            if (inOpcode == opcodes[i][1]) {
                return i;
            }
        }
        return 100;
    }

    string OpcodeTable::getOpcode(int opcodeNum) {
        if (opcodeNum < 59) {
            return opcodes[opcodeNum][0];
        }
        else 
            return "";
        
    }

    string OpcodeTable::getFormat(int opcodeNum) {
        if (opcodeNum < 59) {
            return opcodes[opcodeNum][2];
        }
        else 
            return "";
    }
