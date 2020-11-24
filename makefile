# COURSE:          CS-530 Systems Programming
# SECTION:         01 Synchronous TTh 1900-2015
# PROGRAM #:       2
# LAST MODIFIED:   [SUBMISSION DATE]
# @author Ivan Orozco 822171656 cssc3012
# @author Mariano Hernandez 820450001 cssc3062

dis: main.o RecordReader.o SymbolTable.o TextRecord.o OpcodeTable.o
	g++ main.o RecordReader.o SymbolTable.o TextRecord.o OpcodeTable.o -o dis

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

RecordReader.o: RecordReader.cpp
	g++ -std=c++11 -c RecordReader.cpp

SymbolTable.o: SymbolTable.cpp
	g++ -std=c++11 -c SymbolTable.cpp

TextRecord.o: TextRecord.cpp
	g++ -std=c++11 -c TextRecord.cpp

OpcodeTable.o: OpcodeTable.cpp
	g++ -std=c++11 -c OpcodeTable.cpp

clean:
	rm *.o dis

