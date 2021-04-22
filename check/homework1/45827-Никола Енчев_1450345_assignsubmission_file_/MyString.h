#pragma once

void createDynCopy(char*& destination, const char* source);
class MyString
{
public:
	MyString();
	~MyString();
	MyString(const char* str);
	MyString(const MyString& source);
	MyString& operator=(const MyString& rhs);
	char& at(size_t pos);
	const char& at(size_t pos) const;
	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;
	bool empty() const;
	size_t size() const;
	void clear();
	void push_back(char c);
	void pop_back();
	MyString& operator+=(char c);
	MyString& operator+=(const MyString& rhs);
	MyString operator+(char c) const;
	MyString operator+(const MyString& rhs) const;
	const char* c_str() const;
	bool operator==(const MyString& rhs) const;
	bool operator<(const MyString& rhs) const;

private:
	char* str;
	size_t used{ 0 };
	size_t capacity{ 0 };

};