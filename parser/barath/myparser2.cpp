#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "scanner.h"
#include "translator.h"

using namespace std;

// INSTRUCTION:  Complete all ** parts.
// You may use any method to connect this file to scanner.cpp
// that you had written.  
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp .
// -----------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: 16
//=================================================

// globally declared to be available, as per instructions
string saved_lexeme;
tokentype saved_token;
bool token_available = false;
// ----- Utility and Globals -----------------------------------
void setSavedLexeme(string lexeme)//Sets the saved lexeme.
{
  saved_lexeme = lexeme;
}

string tokenNameB[30] = { "ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" }; //for the display names of tokens

string getCurrentLexeme() //Gets the current lexeme. Used by translator.
{
  return saved_lexeme;
}

string getCurrentToken() //Gets the current token. Used by translator.
{
  return tokenNameB[saved_token];
}


// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by: Clay Flores
void syntax_error1(tokentype thetype, string saved_lexeme)//when match() function does not match
{
  cout << "SYNTAX ERROR: expected " << tokenNameB[thetype] << " but found " << saved_lexeme <<  endl;
  cout << "Exiting Program" << endl;
  exit(EXIT_FAILURE);
}
//--------------------------------------------------
void syntax_error2(string pFunction, string saved_lexeme)//when a switch statement goes to default
{
  cout << "ERROR: unexpected " << saved_lexeme << " found in " << pFunction << endl;
  cout << "Exiting Program" << endl;
  exit(EXIT_FAILURE);//always ends program
}
// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// next_token(void)
//    Looks ahead to see what token comes next from the scanner.
//    HOW: checks first to see if the token_available flag is false.
//    If so, saved_token gets scanner() result.
//    and the flag is set true.
//    A token is grabbed but is not eaten up.
//    Returns the saved_token
//   Done by : Clay Flores
tokentype next_token()
{
  //cout << "***NEXT TOKEN HAS BEEN CALLED!***" << endl;
  if (!token_available) // if there is no saved token yet
    {
      scanner(saved_token, saved_lexeme); // call scanner to grab a new token
      cout << "Scanner called using word: " << saved_lexeme << endl;
      if (saved_lexeme == "eofm")
	{
	  cout << "SUCCESSFULLY PARSED STORY!" << endl;
	  closeFile();
	  exit(EXIT_SUCCESS);
	}
      //cout << "Scanner determined that " << saved_lexeme << " is " << tokenNameB[saved_token] << endl;
      // if(!(parseQueue.isEmpty()))
      // parseQueue.remove(saved_lexeme);
      //parseQueue.displayAll();
      //cout << saved_lexeme << " has been popped off the queue and is now the new saved_lexeme!" << endl;
      token_available = true; // mark that fact that you have saved it
    }
  return saved_token;    // return the saved token
}

//match(expected)
//Checks and eats up the expected token.
//HOW: checks to see if expected is different from next_token()
//and if so, generates a syntax error and handles the error
//else token_available becomes false (eat up) and returns true.
bool match(tokentype expected)
{
  //cout << "***MATCH HAS BEEN CALLED!***" << endl;
  if (next_token() != expected)  // mismatch has occurred with the next token
    { // calls a syntax error function here to  generate a syntax error message here and do recovery
      syntax_error1(expected, saved_lexeme);
    }
  else  // match has occurred
    {
      cout << "Matched " << tokenNameB[expected] << "<<<<<" << endl;
      token_available = false;  // eat up the token
      return true;              // say there was a match
    }
}


// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: Nick Zimmermann
// ** Be sure to put the name of the programmer above each function
// i.e. All 10 Done by: Nick Zimmermann

//10 <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
void tense()
{
  cout << "Processing (tense)" << endl;
  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;
    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;
    case VERB:
      match(VERB);
      break;
    case VERBNEG:
      match(VERBNEG);
      break;
    default:
      syntax_error2("tense", saved_lexeme);
      break;
    }
  //cout << endl << "***DONE Processing (tense)" << endl << endl;
}
//9 <be> ::=   IS | WAS
void be()
{
  cout << "Processing (be)" << endl;
  switch(next_token())
    {
    case IS:
      match(IS);
      break;
    case WAS:
      match(IS);
      break;
    default:
      syntax_error2("be", saved_lexeme);
      break;
    }
  //cout << "***DONE Processing (be)" << endl;
}
//8 <verb> ::= WORD2
void verb()
{
  cout << "Processing (verb)" << endl;
  match(WORD2);
  //cout << endl << "***DONE Processing (verb)" << endl << endl;
}
//7 <noun> ::= WORD1 | PRONOUN 
void noun()
{
  cout << "Processing (noun)" << endl;
  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      break;
    case PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntax_error2("noun", saved_lexeme);
      break;
    }
  //cout << endl << "***DONE Processing (noun)" << endl << endl;
}
//6 <after verb> ::= <tense> #gen("TENSE")# PERIOD
void after_verb()
{
  cout << "Processing (after_verb)" << endl;
  tense();
  gen("TENSE");
  match(PERIOD);
  //cout << endl << "***DONE Processing (after_verb)" << endl << endl;
}
//5 <after destination> ::= <verb> #getEword# #gen("ACTION")# <after verb>
void after_destination()
{
  cout << "Processing (after_destination)" << endl;
  verb();
  getEword();
  gen("ACTION");
  after_verb();
  //cout << endl << "***DONE Processing (after_destination)" << endl << endl;
}
//4 <after object> ::= <verb> #getEword# #gen("ACTION")# <after verb> | <noun> #getEword# DESTINATION #gen("TO")# <after destination>
void after_object()
{
  cout << "Processing (after_object)" << endl;
  switch(next_token())
    {
    case WORD2: //verb
      match(WORD2);
      getEword();
      gen("ACTION");
      after_verb();
      break;
    case WORD1: //noun
      match(WORD1);
      getEword();
      match(DESTINATION);
      gen("TO");
      after_destination();
      break;
    case PRONOUN: //noun
      match(PRONOUN);
      getEword();
      match(DESTINATION);
      gen("TO");
      after_destination();
      break;
    default:
      syntax_error2("after_object", saved_lexeme);
      break;
    }
  //cout << endl << "***DONE Processing (after_object)" << endl << endl;
}
//3 <after noun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE")# PERIOD  | #getEword# DESTINATION #gen("TO")# <after destination> | OBJECT #gen("OBJECT")# <after object>
void after_noun()
{
  cout << "Processing (after_noun)" << endl;
  switch(next_token())
    {
    case IS: //be
      match(IS);
      gen("DESCRIPTION");
      gen("TENSE");
      match(PERIOD);
      break;
    case WAS: //be
      match(WAS);
      gen("DESCRIPTION");
      gen("TENSE");
      match(PERIOD);
      break;
    case DESTINATION: //DESTINATION
      //getEword(); <- adding this makes it display an incorrect destination for sentence 7.
      match(DESTINATION);
      gen("TO");
      after_destination();
      break;
    case OBJECT: //DESTINATION
      match(OBJECT);
      gen("OBJECT");
      after_object();
      break;
    default:
      //cout << "DEBUG: " << saved_lexeme << " | " << tokenNameB[saved_token] << endl;
      syntax_error2("after_noun", saved_lexeme);
      break;
    }
  //cout << endl << "***DONE Processing (after_noun)" << endl << endl;

}
//2 <after subject> ::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <noun> #getEword# <after noun>
void after_subject()
{
  cout << "Processing (after_subject)" << endl;
  switch(next_token())
    {
    case WORD2: //verb
      match(WORD2);
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
    case WORD1: //noun
      match(WORD1);
      getEword();
      after_noun();
      break;
    case PRONOUN: //noun
      match(PRONOUN);
      getEword();
      after_noun();
      break;
      break;
    default:
      syntax_error2("after_subject", saved_lexeme);
      break;
    }
  //cout << endl << "***DONE Processing (after_subject)" << endl << endl;
}
//1 <s> ::= [CONNECTOR #getEword# #gen("CONNECTOR")#] <noun> #getEword# SUBJECT #gen("ACTOR")# <after subject>
void S()
{
  // parseQueue.remove(saved_lexeme);
  cout << "Processing (S)" << endl;
  if(next_token() == CONNECTOR)
    {
      match(CONNECTOR);
      getEword();
      gen("CONNECTOR");
    }
  noun();
  getEword();
  match(SUBJECT);
  gen("ACTOR");
  after_subject();
  //cout << endl << "***DONE Processing (S)" << endl << endl;
}
