#include <cmath>
#include "StringHelper.h"
using std::stoi;

vector<string> StringHelper::splitBy(string source, const string& delimeter)
{
	vector<string> words;
	size_t pos = 0;

	if (source.find(delimeter) == string::npos && !source.empty())
	{
		words.push_back(source);
		return words;
	}

	while ((pos = source.find(delimeter)) != string::npos)
	{
		// Check if there is a quote. If so check if it contains a string and extract it
		size_t quoteOccurence = source.substr(0, pos).find('"');
		if (quoteOccurence != string::npos)
		{
			pos = source.substr(quoteOccurence + 1, source.size() - 1).find('"');
			size_t findNexDelimiter = source.substr(pos, source.size() - 1).find(delimeter);
			if (findNexDelimiter == string::npos)
			{
				words.push_back(source.substr(0, source.size()));
				return words;
			}
			else
			{
				pos = pos + source.substr(pos, source.size() - 1).find(delimeter);
			}
		}

		words.push_back(source.substr(0, pos));
		source.erase(0, pos + delimeter.length());

		if (pos = source.find(delimeter) == string::npos)
		{
			words.push_back(source);
			return words;
		}
	}

	return words;
}

bool StringHelper::isStringInteger(const string& source)
{
	if (source.empty())
	{
		return false;
	}

	bool hasDigits = false;

	for (size_t i = 0; i < source.size(); i++)
	{
		if (i == 0 && source[0] == '-')
		{
			continue;
		}

		if (!isdigit(source[i]))
			return false;
		else
			hasDigits = true;
	}

	if (!hasDigits)
		return false;

	return true;
}

bool StringHelper::isStringDouble(const string& source)
{
	if (source.empty())
	{
		return false;
	}

	size_t numberOfDots = 0;

	for (size_t i = 0; i < source.size(); i++)
	{
		if (source[i] == '.')
		{
			numberOfDots++;
		}
	}

	if (numberOfDots != 1)
	{
		return false;
	}

	vector<string> parts = splitBy(source, ".");
	removeEmptyStringsInVector(parts);

	if (parts.size() != 2)
	{
		return false;
	}

	for (size_t i = 0; i < parts.size(); i++)
	{
		if (!isStringInteger(parts[i]))
		{
			return false;
		}

		if (i == 1 && (parts[i].front() == '-' || parts[i].front() == '+'))
		{
			return false;
		}
	}

	return true;
}

bool StringHelper::isStringValidFormula(const string& source)
{
	string cpy(source);
	trim(cpy);

	if (cpy.empty() || cpy[0] != '=')
		return false;

	cpy.erase(cpy.begin());		 // Remove '=' and begin checking correctness
	addSpaceInBetweenWords(cpy); // Divide words/numbers with spaces so the splitByFunction can catch every element
	vector<string> parts = splitBy(cpy, " ");
	removeEmptyStringsInVector(parts); //Remove empty elements

	if (parts.size() == 0)
		return false;

	if (parts.size() == 1 && !isStringValidString(parts.back()) && !isStringDouble(parts.back()) && !isStringInteger(parts.back()) && !isStringValidCellAddress(parts.back()))
		return false;

	for (size_t i = 0; i < parts.size(); i++)
	{
		if (parts[i] == "(" || parts[i] == ")")
		{
			parts.erase(parts.begin() + i);
			i--;
		}
	}

	if (parts.empty())
		return false;

	size_t opCount = 0;
	size_t numCount = 0;
	for (size_t i = 0; i < parts.size(); i++)
	{
		if (parts[i] == "*" || parts[i] == "/" || parts[i] == "+" || parts[i] == "-" || parts[i] == "^")
			opCount++;
		else if (isStringDouble(parts[i]) || isStringInteger(parts[i]) || isStringValidString(parts[i]) || isStringValidCellAddress(parts[i]))
			numCount++;
	}

	if (opCount > numCount)
	{
		return false;
	}

	for (size_t i = 1; i < parts.size() - 1; i++)
	{
		trim(parts[i]);
		if (!isValidFormulaMember(parts[i]))
			return false;

		if (parts[i] == "+" || parts[i] == "-" || parts[i] == "/" || parts[i] == "*" || parts[i] == "^")
		{
			if ((isStringInteger(parts[i - 1]) || isStringDouble(parts[i - 1]) ||
				isStringValidString(parts[i - 1]) || isStringValidCellAddress(parts[i - 1])) &&
				(isStringDouble(parts[i + 1]) || isStringValidString(parts[i + 1]) ||
					isStringInteger(parts[i + 1]) || isStringValidCellAddress(parts[i + 1])))
				continue;
			else
				return false;
		}
	}

	return true;
}

bool StringHelper::isValidFormulaMember(const string& member)
{

	if (member == "(" || member == ")" || member == "+" || member == "-" || member == "/" || member == "*" || member == "^" || isStringDouble(member) || isStringInteger(member) || isStringValidString(member) || isStringValidCellAddress(member))
	{
		return true;
	}

	return false;
}

string& StringHelper::trim(string& source)
{
	if (source.empty())
	{
		return source;
	}

	size_t start = 0;

	while (source[start] == ' ')
	{
		source.erase(source.begin());
	}

	size_t end = source.size() > 0 ? source.size() - 1 : 0;

	while (source[end] == ' ')
	{
		source.erase(source.begin() + end);
		end--;
	}

	return source;
}

bool StringHelper::isStringValidString(const string& source)
{
	if (source.size() < 2 || source.empty() || source[0] != '"' || source[source.size() - 1] != '"')
	{
		return false;
	}

	return true;
}

void StringHelper::removeQuotations(string& source)
{
	if (!isStringValidString(source))
	{
		return;
	}

	source.erase(source.begin());
	source.erase(source.end() - 1);
}

void StringHelper::removeEmptyStringsInVector(vector<string>& parts)
{
	for (size_t i = 0; i < parts.size(); i++)
	{
		if (parts[i].empty())
		{
			parts.erase(parts.begin() + i);
			i--;
		}
	}
}

string StringHelper::getStringFilledWithSpaces(size_t num_of_spaces)
{
	string s;
	for (size_t i = 0; i < num_of_spaces; i++)
	{
		s.push_back(' ');
	}
	return s;
}

void StringHelper::addSpaceInBetweenWords(string& source)
{
	for (size_t i = 0; i < source.size(); i++)
	{
		if (source[i] == '"')
		{
			i++;
			if (i == source.size() - 1)
			{
				return;
			}

			while (source[i] != '"')
			{
				i++;
				if (i == source.size() - 1)
				{
					return;
				}
			}
		}
		if (!isdigit(source[i]) && !isalpha(source[i]) && source[i] != '.' && source[i] != ' ' && source[i] != '"' && source[i] != '=')
		{
			source.insert(source.begin() + i, ' ');
			source.insert(source.begin() + i + 2, ' ');
			i += 2;
		}
	}
}

bool StringHelper::isStringValidCellAddress(string source)
{
	source = toUpper(source);
	trim(source);

	if (source.empty() || source[0] < 65 || source[0] > 90)
		return false;

	source.erase(source.begin());

	if (!isStringInteger(source))
	{
		return false;
	}

	if (stoi(source) < 1)
	{
		return false;
	}

	return true;
}

Pair StringHelper::extractCellAddressDetails(string source)
{
	Pair pair;
	trim(source);

	if (source[0] >= 65 && source[0] <= 90)
	{
		size_t column = (source[0] - 65);
		source.erase(source.begin());
		pair.value = column;

		size_t rows = 0;
		rows = stoi(source) - 1;
		pair.key = rows;
	}
	else
	{
		size_t column = (source[0] - 97);
		source.erase(source.begin());
		pair.value = column;

		size_t rows = 0;
		rows = stoi(source) - 1;
		pair.key = rows;
	}


	return pair;
}

void StringHelper::enquoteString(string& source)
{
	source.insert(source.begin(), '"');
	source.insert(source.end(), '"');
}

const string StringHelper::toUpper(const string& str)
{
	string item;
	item = str;
	for (size_t i = 0; i < item.size(); i++)
	{
		if (item[i] >= 'a' && item[i] <= 'z')
		{
			item[i] -= 'a' - 'A';
		}
	}

	return item;
}

size_t StringHelper::getQuotesCount(const string& str) {
	size_t count = 0;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '"')
			count++;
	}

	return count;
}
