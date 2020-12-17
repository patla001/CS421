#include<iostream>
#include<fstream>
#include<string>
#include "group27translator.h"
#include "dictionary.h"

using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: **
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** 


ofstream translation("translation.txt");

string savedEWord;
string savedToken;
Dictionary d; 

void getEword()
{
	savedEWord = d.lookUp(getCurrentLexeme());
}

void gen(string line)
{
	if (line == "TENSE")
	{
		savedToken = "TENSE: " + getCurrentToken();
		translation << savedToken << endl;
	} else {
		savedEWord = line + ": " + savedEWord;
		translation << savedEWord << endl;
	}
}

	
void writeBlank()
{
	translation << endl;
}


// ----- Changes to the parser.cpp content ---------------------
// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

