#pragma once
#include <string>
#include <fstream>

using std::string;
using std::ofstream;

class editor
{
public:
	editor(const string& path = "");
	~editor();

	void open(const string& path);
	void close();
	inline size_t size() { return m_size; };
	void edit(size_t offset, uint8_t value);
	void display(size_t offset, size_t limit);

private:
	ofstream m_out;
	size_t m_size;
};