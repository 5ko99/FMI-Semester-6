#pragma once
#include <string>
#include <vector>
#include "CommandType.h"

using std::string;
using std::vector;

class CommandParser
{
private:
	string raw;
	vector<string> tokens;

public:
	/**
	 * @brief Sets the inner raw string of data and splits it into tokens
	 * @param str - string to be set and splited
	*/
	void setData(const string& str);

	/**
	*	@brief Splits raw into parts(tokens) and pushes them inside tokens private member.
	*/
	void tokenizeInnerString();

	/**
	 * @brief Counts the number of quotes in a given string
	 * @param str - string to check
	 * @returns number of quotes
	*/
	size_t getNumberOfQuotes(const string& str);

	/**
	*	@brief Getter
	*	@returns returns raw string
	*/
	string& getRaw();

	/**
	*	@brief Getter
	*
	*	@returns size of tokens
	*/
	size_t size() const;

	/**
	*	@brief Getter. Throws out_of_range if pos is invalid
	*
	*	@param pos - index to be accessed
	*	@returns the element at index pos
	*/
	const string& atToken(size_t pos) const;

	/**
	*	@brief Clears raw, leaves it empty. Clears tokens, leaves it empty
	*/
	void clearCmd();

	/**
	*	@returns the type of the input command
	*/
	CommandType getCommandType() const;
};