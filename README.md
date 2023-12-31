The BigAdd Analyzer has 3 main parts:

1. The first part is lexical analysis. The program analyzes the code and breaks it down to keywords.
2. The second part is the interpreter.c file. This file works as the main file for the interpreter and holds the two main functions we used in this project: interpreter( ) and detectWordInterpreter( ).
3. The third part is the operations.c file. This file holds the necessary functions to correctly parse, divise and run the code the interpreter is given. These operations are declaration, assignment, addition, subtraction, printing and looping.  There also is a smaller and more up to date version of the function we used in the lexical analyzer called wordSeperator ( ) which helps us divise the line we read from the file to words.

Also to note, every defined function has it’s own rules declared in the BigAdd Language file. The program follows these rules while parsing the code. For example, assignment has the rule of move <int_value> to <variable>. While parsing the assignment code, the program first checks for the move keyword, then checks if the next word is indeed an int value, then checks for the “to” keyword and lastly it checks for the variable. All these checks are done in a tree-like structure, and any errors found in the chain immediately exits the program.
