#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct WORDS
{
	string englishWord;
	string japaneseWord;
};

class Dictionary
{
	private:
		unordered_map <string, WORDS*> englishWords;
		unordered_map <string, WORDS*> japaneseWords;
	void read();
	public:
		Dictionary();
		~Dictionary();
		string lookUp(string);
};
