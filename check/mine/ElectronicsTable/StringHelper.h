#pragma once
#include <string>
#include <vector>
#include "Pair.h"

using std::string;
using std::vector;

class StringHelper
{
private:
	StringHelper();
public:
	StringHelper(const StringHelper& sh) = delete;
	StringHelper& operator=(const StringHelper& sh) = delete;
	StringHelper(StringHelper&& sh) = delete;
	StringHelper& operator=(StringHelper&& sh) = delete;

	/**
	*	@brief Splits a given string(source) into parts by given delimeter
	*
	*	@param source    - string to be splited
	*	@param delimeter - what to split it by
	*
	*	@returns vector<string> filled with the splited parts
	*/
	static vector<string> splitBy(string source, const string& delimeter);

	/**
	*	@brief Checks if a given string is valid integer number.
	*
	*	@param source - string to be checked
	*	@returns true if valid, false othwerwise
	*/
	static bool isStringInteger(const string& source);

	/**
	*	@brief Checks if a given string is valid real number.
	*
	*	@param source - string to be checked
	*	@returns true if valid, false othwerwise
	*/
	static bool isStringDouble(const string& source);

	/**
	*	@brief Checks if a string is valid table formula
	*
	*	@param source - to be checked
	*	@returns true if valid, false otherwise
	*/
	static bool isStringValidFormula(const string& source);

	/**
	*	@brief Removes leading and ending whitespaces
	*
	*	@param source - string to be trimmed
	*	@returns trimmed source
	*/
	static string& trim(string& source);

	/**
	*	@brief Checks if given string is valid formula member
	*
	*	@param member - string to be checked
	*	@returns true if valid, false otherwise
	*/
	static bool isValidFormulaMember(const string& member);

	/**
	*	@brief Checks if a given string is valid string format
	*
	*	@param source - string to be checked
	*	@returns true if valid, false otherwise
	*/
	static bool isStringValidString(const string& source);

	/**
	*	@brief Removes opening and closing quotations of a given string, if there are any
	*
	*	@param source - string to have it's quotations removed
	*/
	static void removeQuotations(string& source);

	/**
	*	@brief Removes all empty strings from a vector of strings
	*
	*	@param parts - vector of strings to have it's empty strings removed
	*/
	static void removeEmptyStringsInVector(vector<string>& parts);

	/**
	*	@brief Fills a string with num_of_spaces whitespaces
	*
	*	@param num_of_spaces - number of whitespaces to create
	*	@returns string filled with white spaces
	*/
	static string getStringFilledWithSpaces(size_t num_of_spaces);

	/**
	*	@brief Adds whitespace between every 2 words/numbers. Only exception is '.'.
	*	Used to divide words/numbers with ' '.
	*
	*	@param source - string which numbers/words will be divided by whitespace
	*/
	static void addSpaceInBetweenWords(string& source);

	/**
	*	@brief Checks if given string matches a cell adress type("A1" is valid but "AA1" is invalid)
	*
	*	@param source - string to be checked
	*/
	static bool isStringValidCellAddress(string source);

	/**
	*	@brief Goes through a cell address and extracts rows and columns
	*
	*	@param source - string to have it's details extracted
	*	@returns pair of numbers, first one - rows, second one - columns
	*/
	static Pair extractCellAddressDetails(string source);

	/**
	*	@brief Enqote the given string
	*
	*	@param source - string to be enquoted
	*/
	static void enquoteString(string& source);

	/**
	*	@brief Converts all small alphabetic characters to capital characters.
	*
	*	@param str - string to be Uppered
	*	@returns string with all lowercase letters converted to uppercase letters
	*/
	static const string toUpper(const string& str);

	/**
	 * @brief Counts the number of quotes in a given string
	 * @param str string to have it's quotations checked
	 * @return	number of quotes
	*/
	static size_t getQuotesCount(const string& str);
};
