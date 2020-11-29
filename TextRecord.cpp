#include "TextRecord.h"
TextRecord::TextRecord() {}
    //Col 1 == T
    //Col 2-7 == Starting Address
    //Col 8-9 == Length of record in bytes
    //Col 10-69 == Object code


void TextRecord::readLine(string inputLine) {
    addressCounter = 0;
    //int lineLength;
    //Do something with the Starting Address
    //move up to the 8th character
    startingAddress = stringHexToIntDecimal(inputLine.substr(1, 6));
    recordLength = stringHexToIntDecimal(inputLine.substr(7, 2));
    readInstructionsLoop(inputLine.substr(9, recordLength));
}


void TextRecord::readInstructionsLoop(string instructions) {
    string tempString;
    string nixbpe;
    string opCode;
    int tempFormat;
    int opcodeNum;
    int length = 0;
    
    while (addressCounter < recordLength) {
        tempString = instructions.substr(addressCounter, 3);
        tempString = stringHexToStringBinary(tempString);
        nixbpe += tempString.substr(6, 6);
        opCode += tempString.substr(0, 6);
        opCode += "00";
        opcodeNum = getOpcodeNum(opCode);
        tempFormat = findOpcodeFormat(opcodeNum);
        
        if (tempFormat == 3) {
            if (nixbpe[6] == '1') {
                length = 7;
            }
            else {
                length = 6;
            }
        }
        else if (tempFormat == 2) {
            length = 4;
        }
        else if (tempFormat == 1) {
            length = 2;
        }
        cout << opCode << "\t" << nixbpe << endl;
        mnemonicsList.push_back(opcodeTable.getOpcode(opcodeNum));
        addressList.push_back(addressCounter);
        addressCounter += length;
        opCode.clear();
        nixbpe.clear();
    }
}


int TextRecord::getOpcodeNum(string opcodeBinary) {
    string tempOpcode = stringBinaryToStringHex(opcodeBinary);
    int opcodeNum = opcodeTable.checkIfOpcode(tempOpcode);
    return opcodeNum;
}


int TextRecord::findOpcodeFormat(int opCode) {
    string format;
    format = opcodeTable.getFormat(opCode);
    
    if (format.compare("3/4")) {
        return 3;
    }
    else if (format.compare("2")) {
        return 2;
    }
    else if (format.compare("1")) {
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
        tempChar = ((num - 10) + 97);
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

