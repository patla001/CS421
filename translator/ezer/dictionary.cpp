
#include <iostream>
#include <stdlib.h>
#include <string>
#include <iterator>
#include <fstream>
#include <map>

#include "dictionary.h"

using namespace std;

string Dictionary::lookUp(string word)
{
	WORDS* ew = this-> englishWords[word];
	WORDS* jw = this-> japaneseWords[word];

	if (ew != NULL && ew-> englishWord == word)
	{
		word = ew-> japaneseWord;
	} else if (jw != NULL && jw-> japaneseWord == word)
	{
		word = jw -> englishWord;
	} else {
		cout << "From Dictionary::lookUp: " << word << " is not in the dictionary." << endl;
	}

	return word;
}

void Dictionary::read()
{
	cout << "Reading lexicon.txt..." << endl;
	ifstream dictionaryFile("lexicon.txt");
	string input;
	while(dictionaryFile >> input)
	{
		WORDS* wordInput = new WORDS;
		wordInput -> japaneseWord = input;
		dictionaryFile >> input;
		wordInput -> englishWord = input;
		this -> japaneseWords.insert( pair<string, WORDS*>(wordInput->japaneseWord, wordInput));
		this -> englishWords.insert( pair<string, WORDS*>(wordInput->englishWord, wordInput));
	}
	cout << "Done translating..." << endl;
}

Dictionary::Dictionary()
{
	read();
}

Dictionary::~Dictionary()
{
	this->japaneseWords.clear();
	this->englishWords.clear();
}

