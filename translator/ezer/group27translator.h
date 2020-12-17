
#include <iostream>

using namespace std;

enum tokenType {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, WORD1, WORD2, PERIOD, ERROR, EOFM };

bool vowel (char s1);
bool singleConsonant(char s1);
bool pairConsonant(char s1);
bool pairConsonantNon(char s1);
bool word(string s); //Word DFA
bool period(string s); //Period DFA
void init(); //Initalizes the reserved words list.
void scanner(tokenType &a, string &s); //Scanner function that calls the DFA(s).

string getCurrentLexeme();
string getCurrentToken();
void syntax_error1(string lexeme , tokenType savedT);
void syntax_error2(string expec, string lexeme );
tokenType next_token();
bool match(tokenType expected);
void tense();
void be();
void verb();
void noun();
void after_verb();
void after_destination();
void after_object();
void after_noun();
void after_subject();
void sentenceS();
