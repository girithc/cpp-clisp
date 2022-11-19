Lisp Interpreter in c++ by Girith Choudhary

About the Lisp interpreter:

This lisp interpreter is written in c++.
All the interpreter calculations of the lisp interpreter are done in the clisp folder.
This lisp interpreter is based on the lisp grammar provided in the CS 403 class.


Instructions to run the program:

run command to generate executeable a.out: g++ clisp/clisp.cpp  -std=c++11.
run command to run a lisp file t1.lisp in folder lispSample: ./a.out lispSample/t1.lisp

Procedure to run a lisp file:
Put the .lisp file in the lispSample folder
run the command: ./a.out lispSample/filename.lisp


Testing

command to test lispInterpreter: ./a.out test

Test Case results are in the test folder.

There are four test cases for this lisp interpreter.
TestCase1 tests nil?, number?, symbol?, list?, set, cond, and print.
TestCase2 tests set, print, cdr, car, 
TestCase3 tests define, cond, +,-,*,= using a function factorial that recursively calculates the factorial of a number
TestCase4 tests define, set, print, >,<=, nil? and cons using a function binTree that inserts an element x in tree and return the resulting tree



