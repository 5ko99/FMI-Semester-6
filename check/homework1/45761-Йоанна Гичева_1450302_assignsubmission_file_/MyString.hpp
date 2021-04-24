#ifndef MYSTRING_HPP_INCLUDED
#define MYSTRING_HPP_INCLUDED

class MyString
{
public:
	MyString();
	MyString(const char* str);

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
	void print();

private:
	char* str;
};

#endif // !MYSTRING_HPP_INCLUDED