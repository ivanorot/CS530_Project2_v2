#include "TextRecord.h"
    //Col 1 == T
    //Col 2-7 == Starting Address
    //Col 8-9 == Length of record in bytes
    //Col 10-69 == Object code

TextRecord::TextRecord() {
    addressCounter = 0;
}

TextRecord::TextRecord(string filename) {
    addressCounter = 0;
    fileName = filename;
    sym.makeTable(fileName);
}


void TextRecord::readLine(string inputLine) {
   
    //int lineLength;
    //Do something with the Starting Address
    //move up to the 8th character
    startingAddress = stringHexToIntDecimal(inputLine.substr(1, 6));
    recordLength = 2*stringHexToIntDecimal(inputLine.substr(7, 2));
    readInstructionsLoop(inputLine.substr(9, recordLength));
}

int TextRecord::checkLiteral(string address) {
    int row;
    string col;
    tie(row,col) = sym.getRowCol(LITTAB,address);
    if (row >= 0) {
        string literal = sym.getData(LITTAB,row,sym.literal);
        
        if (literal[1] == 'c' || literal[1] == 'C') {
            int index = 3;
            int count = 0;
            while (literal[index] != '\'') {
               index++;
               count++;
            }
            return count;
        }
        else if (literal[1] == 'x' || literal[1] == 'X'){
            int index = 3;
            int count = 0;
            while (literal[index] != '\'') {
               index++;
               count++;
            }
            return count;
        }
    }
    return 0;
}

string TextRecord::getSixLength(string hex) {
    int length = hex.length();
    string tempReturn;
    if (length < 6) {
        for (int i = 0; i < (6 - length); i++) {
            tempReturn += '0';
        }
        tempReturn += hex;
    }
    else {
        tempReturn = hex;
    }
    return tempReturn;
}

void TextRecord::readInstructionsLoop(string instructions) {
    int recordCounter = 0;
    string tempString;
    string nixbpe;
    string opCode;
    string taAddress;
    int tempFormat;
    int opcodeNum;
    int length = 0;
    string mneumonic;
    bool baseflag;
    
    bool eflag = false;
    bool jumpflag;
    string tempAddress;
    int newLength;

    LOOP:
    while (recordCounter < recordLength-3) {
        tempAddress = intDecimalToStringHex(recordCounter / 2);
        tempString = getSixLength(tempAddress);
        newLength = checkLiteral(tempString);
        if (newLength > 0) {
            recordCounter += newLength;
            addressCounter += newLength;
            newLength = 0;
            goto LOOP;
        }
        tempAddress.clear();
        tempString.clear();

        jumpflag = true;
        tempString = instructions.substr(recordCounter, 3);
        tempString = stringHexToStringBinary(tempString);
        nixbpe += tempString.substr(6, 6);
        opCode += tempString.substr(0, 6);
        opCode += "00";

        LOOKFOROPCODE:
        opcodeNum = getOpcodeNum(opCode);
        tempFormat = findOpcodeFormat(opcodeNum);
        
        if (tempFormat == 3) {
            if (nixbpe[5] == '1') {
                length = 8;
                eflag = true;
                taAddress += instructions.substr(recordCounter + 3, 5);
            }
            else {
                length = 6;
                taAddress += instructions.substr(recordCounter + 3, 3);
            }
        }
        else if (tempFormat == 2) {
            length = 4;
            taAddress += instructions.substr(recordCounter + 2, 2);
            
        }
        else if (tempFormat == 1) {
            length = 2;
        }
        else {
            opCode.clear();
            opCode += tempString.substr(0, 8);
            if (jumpflag) {
                jumpflag = false;
                goto LOOKFOROPCODE;
            }
        }
       // cout << opCode << "\t" << nixbpe << endl;
        mneumonic += opcodeTable.getOpcode(opcodeNum);
        baseflag = checkBase(mneumonic);
        if (baseflag) {
            base = stringHexToIntDecimal(taAddress);
        }

        if (eflag) {
            mnemonicsList.push_back("+"+mneumonic);
            eflag = false;
        }
        else {
            mnemonicsList.push_back(mneumonic);
        }
        addressList.push_back(getSixLength(intDecimalToStringHex(addressCounter/2)));
        tAList.push_back(taAddress);
        saveStatement(tempFormat, taAddress, nixbpe);
        
        if (baseflag) {
            mnemonicsList.push_back("BASE");
            addressList.push_back(0);
            tAList.push_back("");
            statements.push_back(statements.front());
            baseflag = false;
        }
        
        recordCounter += length;
        addressCounter += length;

        
        mneumonic.clear();
        opCode.clear();
        nixbpe.clear();
        taAddress.clear();
    }
    instructions.clear();
    print();
}

bool TextRecord::checkBase(string mneumonic) {
    if (mneumonic == "LDB") {
        return true;
    }
    return false;
}

void TextRecord::saveStatement(int format, string ta, string nixbpe) {
    StatementDecoder statementDecoder(fileName, base, addressCounter);
    statements.push_back(statementDecoder.getStatement(format, ta, nixbpe));
}

void TextRecord::print() {
    int length = mnemonicsList.size();
   
    string temp;
    for (int i = 0; i < length; i++) {

        cout << addressList.front() <<"\t"<< mnemonicsList.front()<<"\t"<<tAList.front()<<"\t"<< statements.front()<<endl;
        mnemonicsList.pop_front();
        addressList.pop_front();
        tAList.pop_front();
        statements.pop_front();
    }

}
/*void TextRecord::printLis(string programLength) {
    int length = stringHexToIntDecimal(programLength);
    string address;
    int i = 0;
    string temp;
    int symbolRowCount = 0;
    int litRowCount = 0;
    bool instructionCheck;
    bool symbolCheck;
    bool litCheck;

    while(i<length){
        temp = intDecimalToStringHex(i);
        address = getSixLength(temp);
        instructionCheck = (i == addressList.front());
        symbolCheck = (address==checkSymbolAddress(symbolRowCount));
        litCheck = (address == checkLiteralAddress(litRowCount));

        if (symbolCheck == true && instructionCheck == true) {
            cout << address << "\t" << checkSymbolFun(symbolRowCount) << "\t" << mnemonicsList.front() << statements.front() << endl;
            if (checkBase(mnemonicsList.front())) {
                cout << "\t" << "\t" << "\t" << "\t" << "BASE" << getSymbolwithStringAddress(getSixLength(intDecimalToStringHex(base))) << endl;
            }
            symbolRowCount++;
            mnemonicsList.pop_front();
            statements.pop_front();

        }
        else if (instructionCheck == true) {
            cout << address << "\t" << "\t" << "\t" << mnemonicsList.front() << statements.front()<<endl;
            if (checkBase(mnemonicsList.front())) {
                cout << "\t" << "\t" << "\t" << "\t" << "BASE" << getSymbolwithStringAddress(getSixLength(intDecimalToStringHex(base))) << endl;
            }
            mnemonicsList.pop_front();
            statements.pop_front();
        }

        else if (symbolCheck == true) {
            cout << address << "\t" << checkSymbolFun(symbolRowCount) << "\t" << "\t" << "\t"<<endl;
            symbolRowCount++;
        }
        else if (litCheck) {
            cout << address << "\t" << "\t" << "\t" << "*" << checkLiteralFun(litRowCount) << endl;
            litRowCount++;
        }
    }

}*/

list<string> TextRecord::returnAddress() {
    //int length = addressList.size();
    //for (int i = 0; i < length; i++) {
    //    intDecimalToStringHex((addressList.front()) / 2);
    //}
    return addressList;
}


int TextRecord::getOpcodeNum(string opcodeBinary) {
    string temp;
    string tempOpcode = stringBinaryToStringHex(opcodeBinary);
    if (tempOpcode.length() == 1) {
        temp += "0";
        temp += tempOpcode;
        tempOpcode = temp;
    }
    else if (tempOpcode.length() == 0) {
        tempOpcode += "00";
    }

    int opcodeNum = opcodeTable.checkIfOpcode(tempOpcode);
    temp.clear();
    tempOpcode.clear();
    return opcodeNum;
}


int TextRecord::findOpcodeFormat(int opCode) {
    string format;
    format = opcodeTable.getFormat(opCode);
    
    if (format=="3/4") {
        return 3;
    }
    else if (format=="2") {
        return 2;
    }
    else if (format=="1") {
        return 1;
    }
    else {
        return 0;
    }
}


//checked*
string TextRecord::stringHexToStringBinary(string hex) {
    string newTemp;
    
    for (unsigned int i = 0; i < hex.length(); i++) {
        newTemp += charHextoStringBinary(hex[i]);
    }
    return newTemp;
}


//checked*
string TextRecord::stringBinaryToStringHex(string binary) {
    int value = stringBinaryToIntDecimal(binary);
    string hex = intDecimalToStringHex(value);
    return hex;
}


//checked*
string TextRecord::intDecimalToStringHex(int decimal) {
    int hexVal;
    string tempHex;
    string returnHex;
    
    while (decimal > 0) {
        hexVal = decimal % 16;
        decimal = decimal / 16;
        tempHex += zeroToFifteenIntToHexChar(hexVal);
    }
    
    for (unsigned int f = 0; f < tempHex.length(); f++) {
        returnHex += tempHex[(tempHex.length() - 1) - f];
    }

    return returnHex;
}


//checked
int TextRecord::stringHexToIntDecimal(string tempString) {
    string hex = tempString;
    //string charHextoStringBinary(char y);
    //int stringBinaryToIntDecimal(string h);
    int decimal;
    string temp;
    
    for (unsigned int i = 0; i < hex.length(); i++) {
        temp += charHextoStringBinary(hex[i]);
        //cout << temp << endl;
    }
    decimal = stringBinaryToIntDecimal(temp);
    return decimal;
}

//checked
string TextRecord::charHextoStringBinary(char Byte) {
    //char zeroToFifteenIntToHexChar(int f);
    //int charNumToIntNum(char d);
    int hexNum = Byte;
    string binary;  //will save and return the char represented as binary in a string
    char temp;
    hexNum = charNumToIntNum(Byte);
    
    for (int i = 0; i < 4; i++) {
        temp = zeroToFifteenIntToHexChar(1 & hexNum >> (3 - i));
        binary += temp;
    }
    return binary;
}

//checked
int TextRecord::charNumToIntNum(char dec) {
    int num = dec;
    
    if (num >= 48 && num <= 57) {
        num = num - 48;
    }
    else if (num >= 65 && num <= 70) {
        num = num - 65 + 10;
    }
    else if (num >= 97 && num <= 102) {
        num = num - 97 + 10;
    }
    else {
        return 0;
    }
    return num;
}


//checked
char TextRecord::zeroToFifteenIntToHexChar(int num) {
    char tempChar;
    
    if (num < 10) {
        tempChar = (num + 48);
    }
    else {
        tempChar = ((num - 10) + 65);
    }
    return tempChar;
}


//checked
int TextRecord::stringBinaryToIntDecimal(string binary) {
    int result = 0;
    int temp;
    
    for (unsigned int i = 0; i < binary.length(); i++) {
        temp = binary[(binary.length() - 1) - i] == '1';

        for (unsigned int f = 0; f < i; f++) {
            temp = temp * 2;
        }
        result = result + temp;
    }
    return result;
}

string TextRecord::checkLiteralFun(int row) {
        string literal = sym.getData(LITTAB, row, sym.literal);
        return literal;

}

string TextRecord::checkSymbolFun(int row) {
        string symbol = sym.getData(SYMTAB, row, sym.symbol);
        return symbol;
}

string TextRecord::checkLiteralAddress(int row) {
    string literal = sym.getData(LITTAB, row, sym.address);
    return literal;

}

string TextRecord::checkSymbolAddress(int row) {
    string symbol = sym.getData(SYMTAB, row, sym.value);
    return symbol;
}

string TextRecord::getSymbolwithStringAddress(string address) {
    int row;
    string col;
    tie(row, col) = sym.getRowCol(SYMTAB, address);
    if (row >= 0) {
        string symbol = sym.getData(SYMTAB, row, sym.symbol);
        return symbol;
    }
    else
        return "";
}


