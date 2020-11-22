# COURSE:          CS-530 Systems Programming
# SECTION:         01 Synchronous TTh 1900-2015
# PROGRAM #:       2
# LAST MODIFIED:   [SUBMISSION DATE]
# @author Ivan Orozco 822171656 cssc3012
# @author Mariano Hernandez 820450001 cssc3062

dis: main.o RecordReader.o SymbolTable.o
	g++ main.o RecordReader.o SymbolTable.o -o dis

main.o: main.cpp
	g++ -c main.cpp

RecordReader.o: RecordReader.cpp
	g++ -c RecordReader.cpp

SymbolTable.o: SymbolTable.cpp
	g++ -c SymbolTable.cpp

clean:
	rm *.o dis

