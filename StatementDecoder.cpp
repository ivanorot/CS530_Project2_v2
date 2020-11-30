#include "StatementDecoder.h"

StatementDecoder::StatementDecoder(string s, int b, int pc) {
    symbolTable.makeTable(s);
    base = b;
    progC = pc;
    fileName = s;
}



//format 1 = XX
//format 2 = XX[XX]
//format 3 = XXX[XXX]
//format 4 = XXX[XXXXX]
string StatementDecoder::getStatement(int format, string targetAddress, string nixbpe) {
    cout << "progC: " << progC << "\t" << progC/2 << endl;
    if (format == 2) {
        return formatTwo(targetAddress);
    }
    else if ((format == 3)|| (format == 4)) {
        return formatThree(targetAddress, nixbpe);
    }
}

//Base relative		 b=1, p=0 [xxx10x] TA = B + disp
//Prog C. relative	 b=0, p=1 [xxx01x] TA = PC + disp

//immediate Addres	 n=0, i=1 [01xxxx] TA as operand
//indirect Address	 n=1, i=0 [10xxxx] word at TA is fetch and used as an address to fetch the operand
//simple addressin	 n=i [00xxxx] or [11xxxx] TA is the location of the operand
string StatementDecoder::formatTwo(string targetAddress) {
    string r1 = targetAddress.substr(0, 1);
    string r2 = targetAddress.substr(1, 1);
    string tempReturn;
    tempReturn += registerMnemoic(r1[0]);
    tempReturn += ", ";
    tempReturn += registerMnemoic(r2[0]);

    return tempReturn;
}


string StatementDecoder::registerMnemoic(char x) {
    switch (x)
    {
    case '0':
        return "A"; 
    case '1':
        return "X";
    case '2':
        return "L";
    case '3':
        return "B";
    case '4':
        return "S";
    case '5':
        return "T";
    case '6':
        return "F";
    case '8':
        return "PC";
    case '9':
        return "SW";

    default:
        break;
    }
    return "";
}


string StatementDecoder::formatThree(string targetAd, string nixbpe) {
    string temp;
    temp += addressingMode(nixbpe);
    temp += getSymbol(targetAd, nixbpe);
    temp += indexAddressing(nixbpe);
    return temp;
}

//Base relative		 b=1, p=0 [xxx10x] TA = B + disp
//Prog C. relative	 b=0, p=1 [xxx01x] TA = PC + disp

//immediate Addres	 n=0, i=1 [01xxxx] TA as operand
//indirect Address	 n=1, i=0 [10xxxx] word at TA is fetch and used as an address to fetch the operand
//simple addressin	 n=i [00xxxx] or [11xxxx] TA is the location of the operand

string StatementDecoder::getSymbol(string targetAd, string nixbpe) {
    TextRecord hexTranslator;
    //cout << nixbpe << "\t";
    int checkSymbol;
    int size;
    string tempReturn;
    string tempGetSymbol;
    size = format4check(nixbpe);
    //cout << targetAd << endl;
    checkSymbol = hexTranslator.stringHexToIntDecimal(targetAd);
    if (nixbpe[4] == '1') {  //PC relative
        if (checkSymbol > 2048) {
            checkSymbol -= 4096;
        }
        
        checkSymbol += (progC/2);
        //cout << checkSymbol <<"\t";
        tempReturn = hexTranslator.intDecimalToStringHex(checkSymbol);
        tempGetSymbol += getSixLength(tempReturn);
        //cout << tempGetSymbol << "\t";
        tempReturn.clear();
        tempReturn += checkSymbolFun(tempGetSymbol);
        if (tempReturn.size() < 1) {
            tempReturn += checkLiteralFun(tempGetSymbol);
        }
        //cout << tempReturn << endl;
        //cout << ".........................." << endl;
        //check if symbol

    }
    else if (nixbpe[3] == '1') {
        cout << base<<endl;
        checkSymbol += (base);
        //cout << checkSymbol << "\t";
        tempReturn = hexTranslator.intDecimalToStringHex(checkSymbol);
        tempGetSymbol += getSixLength(tempReturn);
        //cout << tempGetSymbol <<"\t";
        tempReturn.clear();
        tempReturn += checkSymbolFun(tempGetSymbol);
        //cout << tempReturn<<endl;
        //cout << ".........................." << endl;


    }
    else {
       tempGetSymbol += getSixLength(targetAd);
       tempReturn += checkSymbolFun(tempGetSymbol);
       //cout << "\t"<< tempReturn << endl;
    }
    return tempReturn;
}

string StatementDecoder::checkLiteralFun(string address) {
    int row;
    string col;
    tie(row, col) = symbolTable.getRowCol(LITTAB, address);
    if (row >= 0) {
        string literal = symbolTable.getData(LITTAB, row, symbolTable.literal);
        return literal;
    }
    else
        return "";
}

string StatementDecoder::checkSymbolFun(string address) {
    int row;
    string col;
    tie(row, col) = symbolTable.getRowCol(SYMTAB, address);
    if (row >= 0) {
        string symbol = symbolTable.getData(SYMTAB, row, symbolTable.symbol);
        return symbol;
    }
    else
        return "";
}

string StatementDecoder::getSixLength(string hex) {
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

int StatementDecoder::format4check(string nixpbe) {
    if (nixpbe[5] == '1') {
        progC += 8;
        return 4;
    }
    else
        progC += 6;
        return 3;
}


string StatementDecoder::addressingMode(string nixbpe) {
    string ni = nixbpe.substr(0, 2);
    if (ni == "10") {
        return "@";
    }
    else if (ni == "01") {
        return "#";
    }
    else {
        return "";
    }
}


string StatementDecoder::indexAddressing(string nixbpe) {
    string x = nixbpe.substr(2, 1);
    if (x == "1") {
        return ",X";
    }
    else {
        return "";
    }
}

