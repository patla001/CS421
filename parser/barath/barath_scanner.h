#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

#ifndef __SCANNER_H__
#define __SCANNER_H__
//function prototypes let us call these functions in any scope: Scanner, Parser, or translator.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};
void readFile(string filename); //Initalizes the read file from any scope: Scanner, Parser, or Translator.
void closeFile(); 
bool word(std::string s); //Word DFA
bool period(std::string s); //Period DFA
void init(); //Initalizes the reserved words list.
int scanner(tokentype& a, std::string& w); //Scanner function that calls the DFA(s).
#endif
