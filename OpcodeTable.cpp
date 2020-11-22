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
