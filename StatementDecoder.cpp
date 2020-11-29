#include <iostream>
#include <string>
#include <fstream>
#include "SymbolTable.h"

using namespace std;

class StatementDecoder {
private:
	SymbolTable symbolTable;


public:
	StatementDecoder(SymbolTable sym) {
		symbolTable = sym;
	}
	//format 1 = XX
	//format 2 = XX[XX]
	//format 3 = XXX[XXX]
	//format 4 = XXX[XXXXX]
	string getStatement(int format, string targetAddress, string nixbpe) {
		if (format == 2) {
			return formatTwo(targetAddress);
		}
		else if ((format == 3)|| (format == 4)) {
			return formatThree(targetAddress, nixbpe);
		}
		
	}
	//Base relative		 b=1, p=0 [xx01xx] TA = B + disp
	//Prog C. relative	 b=0, p=1 [xx10xx] TA = PC + disp

	//immediate Addres	 n=0, i=1 [01xxxx] TA as operand
	//indirect Address	 n=1, i=0 [10xxxx] word at TA is fetch and used as an address to fetch the operand
	//simple addressin	 n=i [00xxxx] or [11xxxx] TA is the location of the operand

	string formatTwo(string targetAddress) {
		string r1 = targetAddress.substr(0, 1);
		string r2 = targetAddress.substr(1, 1);
		string tempReturn;
		tempReturn += registerMnemoic(r1[0]);
		tempReturn += ", ";
		tempReturn += registerMnemoic(r2[0]);

		return tempReturn;
	}
		
	string registerMnemoic(char x) {
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

	string formatThree(string targetAd, string nixbpe) {
		string temp;
		temp += addressingMode(nixbpe);
		temp += targetAd;
		temp += indexAddressing(nixbpe);
		return temp;
	}

	string addressingMode(string nixbpe) {
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

	string indexAddressing(string nixbpe) {
		string x = nixbpe.substr(2, 1);
		if (x == "1") {
			return ", X";
		}
		else {
			return "";
		}
	}

};
