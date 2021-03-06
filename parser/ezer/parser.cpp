#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// token types from the scanner
enum token_type {};

// global buffer for the token the 
// scanner returned
token_type save_token;

// global flag indicating whether
// we have saved a token to eat up or not
bool token_available;

// Type of error: **
// Done by: ** 
void syntaxerror1(  ){    }
// Type of error: **
// Done by: ** 
void syntaxerror2(  ) {    }

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks ahead to see what token comes next from the scanner.
// HOW: checks first to see if the token_available flag is false.
// if so, saved_token gets scanner() result.
// and the flag is set true.
// A token is grabbed but is not eaten up.
// Returns the save_token
// Done by: **
token_type next_token()
{
	string saved_lexeme;
	if (!token_available)  // if there is no saved token yet
	{
		scanner(saved_token, saved_lexeme); // call scanner to grab a new token
		token_available = true;

		if (saved_token == ERROR)
		{
			syntax_error1(saved_lexeme, saved_token);
		}
	}
	return saved_token; // return the saved token
}





// Purpose: Checks and eats up the expected token
// HOW: check to see if expected is different from next_token()
// and if so, generates a syntax error and handles the error
// else token_available become false (eat up) and return true.
// Done by: **
boolean match(tokentype expected) 
{

	if (next_token() != expected) // mismatch has occurred with the next token
	{
		// calls a syntax error function here to generate 
		// a syntax error message here and do recovery
		syntax_error2(saved_lexeme)
	}
	else // match has occurred
	{
		token_available = false; // eat up the token
		return true;		 // say there was a match
	}
}


}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **
// Done by: **

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
