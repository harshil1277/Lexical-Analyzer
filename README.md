# Lexical-Analyzer
Hard coded Finite state machines for Lexical Analysis 
I will walk you through steps how to run the lexical analyzer we coded. First let us go through the constraints it supports.

    • Identifier: A string starting with an underscore or a letter and followed by any number 
of underscores, letters and digits. Identifiers with two leading underscores (__) are 
disallowed
    • Keywords: short int float double bool char signed unsigned for while do return void switch break case continue goto long static union default if else
    • Signed and unsigned Integer constants such as 45, 10, -1234, +5432, 0, -32, etc.
    • Signed and unsigned Floating-point constants such as 1.4, -3.57, 0.72, etc. 
    • Arithmetic operators: +, -, *, /, %, ++, -- 
    • Assignment operators: =, +=, -=, *=, /= 
    • Relational operators: <, >, <=, >=, == 
    • Special symbols: ( ) ,(comma) [ ] { } ;
    • Ignore the text within comments (anything enclosed within /*---*/). 
      
        
Download the zip file and extract or clone the repository. 

Compiling the c++ program:
go to the folder in which we have FSM.cpp file. 
Run ‘g++ FSM.cpp’ command in this directory.

Get the output of c++ program:
run command ‘./a.out’ in same directory.
Enter input file name , ex: ‘input.in’
Enter output file name for TokenID and Atribute Value , ex : ‘pa_1.out’
Enter output file name for Keyword and Identifier , ex: ‘symbol_table_1.out’

Note: If you have not created the input and output file , first create the files in same directory.

View the output:
TokenID and corresponding values: 
Run the command ‘cat pa_1.out’ i.e cat “output file name” , in the same directory.

Keyword and Indentifier :
Run the command ‘cat symbol_table_1.out’ i.e cat “output file name” , in the same directory.
