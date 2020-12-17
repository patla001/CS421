#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "dictionary.h"
#include "group27translator.h"
#include "translator.h"

using namespace std;

//----------- Driver ---------------------------


// The new test driver to start the parser
// Done by: Ezer
int main()
{
  ifstream fin;
  string filename;
 // call the reserved words from the scanner
 // create a void init() in the parser code or scanner code
  init();
  // read the file
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  
  int countSentences = 1;
  while (true)
  {     
        cout << "------------------------------------" << endl;
        cout << "       Reading Sentence: " << countSentences << endl;
        cout << "------------------------------------" << endl;
        sentenceS();
        //translation << endl;
        writeBlank();
	// count the number of sentences
        countSentences++;
  }
  
  // calls the <story> to start parsing
  // closes the input file
  cout << "End of file is encountered." << endl;
  fin.close();
  // end of the file

}// end of main()
