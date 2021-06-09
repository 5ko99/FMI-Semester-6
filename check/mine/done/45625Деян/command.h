#pragma once
#include <string>
#include <vector>

using std::string;
using tokens = std::vector<string>;

class command
{
public:
	command(const string& cmd);
	
	void processCommand();
	inline size_t size() const { return m_tokens.size(); };
	string& operator[](size_t ind);
	const string& operator[](size_t ind) const;

private:
	string m_cmd;
	tokens m_tokens;
};

