#include <algorithm>
#include <string>

using namespace std;

bool isLetter(char letter)
{
	bool res = ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'));
	return res;
}

bool isDigit(char digit)
{
	bool res = (digit >= '0' && digit <= '9');
	return res;
}

void strToUpper(string& s)
{
	for_each(s.begin(), s.end(), [](char& c) {
		c = ::toupper(c);
		});
}

string strToQuoted(const string& s)
{
	// TODO:
	return  "\"" + s + "\"";
}
