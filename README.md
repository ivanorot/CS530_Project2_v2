## COURSE:          CS-530 Systems Programming
## SECTION:         01 Synchronous TTh 1900-2015
## PROGRAM #:       2
## LAST MODIFIED:   30 November 2020
## @author Ivan Orozco 822171656 cssc3012
## @author Mariano Hernandez 820450001 cssc3062


***
## Overview

This is an XE disassembler program, `dis`, that can open and disassemble an XE
object file, `<filename>.obj`, along with their accompanying symbol file, 
`<filename>.sym`, and generate an XE source file, `<filename>.sic`, and an
XE listing file,`<filename>.lis`.

To run the program...

>start up a terminal and open the directory where the source code is stored,
>as shown in the "Directories/Files" section:
>
>                cd ./a2
>
>build the executable program:
>
>                make
>
>run the executable:
>
>                dis <filename>

upon execution, the program will generate the appropriate XE source file and
the XE listing file while also outputting the contents of these files to the
terminal.

An output example of this, using some test files, can be found in the "Test
Result" section.


***
## Design Process

See the "System Design Document"
   

***
## Directories/Files

### ./a2

This directory contains any source code files, executables, and amakefile to
run the program; plus information regarding the program.

>- *makefile*
    - set of directives that tell `make` how to compile and link the program

>- *main.cpp*
    - starting point of the program

>- *RecordReader.h*
    - this header file includes type definitions (including function
      prototypes) used for the RecordReader

>- *RecordReader.cpp*
    - source code for the basic RecordReader

>- *TextRecord.h*
    - this header file includes type definitions (including function
      prototypes) used for the TextRecord

>- *TextRecord.cpp*
    - source code for the basic RecordReader

>- *OpcodeTable.h*
    - this header file includes type definitions (including function
      prototypes) used for the OpcodeTable

>- *OpcodeTable.cpp*
    - source code for the basic OpcodeTable

>- *SymbolTable.h*
    - this header file includes type definitions (including function
      prototypes) used for the SymbolTable

>- *SymbolTable.cpp*
    - source code for the basic SymbolTable

>- *StatementDecoder.h*
    - this header file includes type definitions (including function
      prototypes) used for the StatementDecoder

>- *StatementDecoder.cpp*
    - source code for the basic StatementDecoder
    
>- *sample.obj*
    - provided sample object code for testing

>- *sample.sym*
    - provided sample symbol file that contain the SYMTAB and LITTAB

>- *README.md* (this file)
    - details the information of this program



***
## Test Results

(note: if reading unformatted through the markdown language, the files do
not contain any markdown syntax i.e. `<br />`, #, or \`)

output on running some tests using the testing files:<br />


