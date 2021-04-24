#include "MyString.hpp"

MyString::MyString() {
	this->string = nullptr;
	this->lenght = 0;
	this->capacity = 1;
}

void MyString::resize()
{
	char* new_string = new char[this->capacity * 2];
	strcpy_s(new_string, this->lenght + 1, this->string);
	delete[] this->string;
	this->string = new_string;
	this->capacity *= 2;
}

MyString::MyString(const char* str)
{
	this->lenght = strlen(str);
	this->capacity = this->lenght + 1;
	this->string = new char[this->lenght+1];
	if (!this->string)
	{
		return;
	}
	strcpy_s(this->string, strlen(str) + 1, str);
}

MyString::MyString(const MyString& copy) noexcept
{

	this->lenght = copy.lenght;
	this->capacity = this->lenght + 1;
	this->string = new char[this->lenght + 1];
	if (!this->string)
	{
		return;
	}
	strcpy_s(this->string, copy.lenght + 1, copy.string);
}

MyString& MyString::operator=(const MyString& copy) noexcept
{
	if (this == &copy)
	{
		return *this;
	}
	delete[] this->string;
	this->lenght = copy.lenght;
	this->capacity = copy.capacity;
	this->string = new char[lenght + 1];
	strcpy_s(this->string, copy.lenght + 1, copy.string);
	return *this;
}

char& MyString::at(size_t pos)
{
	if (pos<0 || pos>this->lenght)
	{
		throw out_of_range("Position out of range exception!");
	}
	else
	{
		return this->string[pos];
	}
}

const char& MyString::at(size_t pos) const
{
	if (pos<0 || pos>=this->lenght)
	{
		throw out_of_range("Position out of range exception!");
	}
	else
	{
		return this->string[pos];
	}
}

char& MyString::operator[](size_t pos)
{
	assert(pos > 0);
	assert(pos < this->lenght);
	return this->string[pos];
}

const char& MyString::operator[](size_t pos) const
{
	return this->string[pos];
}

char& MyString::front()
{
	return this->string[0];
}

const char& MyString::front() const
{
	return this->string[0];
}

char& MyString::back()
{
	if (this->lenght == 0)
	{
		return this->string[this->lenght];
	}
	return this->string[this->lenght-1];
}
 
const char& MyString::back() const 
{
	if (this->lenght == 0)
	{
		return this->string[this->lenght];
	}
	return this->string[this->lenght-1];
}

bool MyString::empty() const
{
	if (this->lenght == 0)
	{
		return true;
	}
	return false;
}

size_t MyString::size() const
{
	return this->lenght;
}

void MyString::clear()
{
	this->lenght = 0;
	this->capacity = 1;
	delete[] this->string;
	this->string = new char[this->capacity];
	this->string[0] = '\0';
}

void MyString::push_back(char c)
{
	if (this->lenght >= this->capacity)
	{
		this->resize();
	}
	this->string[this->lenght] = c;
	this->lenght += 1;
}

void MyString::pop_back()
{
	this->string[this->lenght-1] = '\0';
	this->lenght--;
}

MyString& MyString::operator+=(char c)
{
	if (this->lenght >= this->capacity)
	{
		this->resize();
	}
	this->string[this->lenght] = c;
	this->lenght += 1;
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	while (this->capacity <= rhs.lenght+this->lenght)
	{
		this->resize();
	}
	unsigned new_lenght =this->lenght + rhs.lenght;
	unsigned j = 0;
	for (unsigned i = this->lenght; this->lenght < new_lenght; i++)
	{
		this->string[i] = rhs.string[j];
		this->lenght++;
		j++;
	}
	this->string[this->lenght] = '\0';
	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString new_string;
	new_string.lenght = this->lenght;
	new_string.capacity = this->capacity;
	new_string.string = new char[new_string.lenght + 1];
	strcpy_s(new_string.string, this->lenght + 1, this->string);
	new_string.push_back(c);
	return new_string;

}

MyString MyString::operator+(const MyString& rhs) const
{
	MyString new_string;
	new_string.lenght = this->lenght;
	new_string.capacity = this->capacity;
	new_string.string = new char[new_string.lenght + 1];
	strcpy_s(new_string.string, this->lenght + 1, this->string);
	new_string.string[new_string.lenght] = '\0';
	new_string+=(rhs);
	return new_string;
}

const char* MyString::c_str() const
{
	return this->string;
}

bool MyString::operator==(const MyString& rhs) const
{
	if (strcmp(this->string, rhs.string) == 0)
	{
		return true;
	}
	return false;
}

bool MyString::operator<(const MyString& rhs) const
{
	if (strcmp(this->string, rhs.string) < 0)
	{
		return true;
	}
	return false;
}

const char* MyString::get_string() const
{
	return this->string;
}

 unsigned MyString::get_lenght() const
{
	return this->lenght;
}

 unsigned MyString::get_capacity() const
 {
	 return this->capacity;
 }
 
MyString::~MyString() {
	delete[] this->string;
}