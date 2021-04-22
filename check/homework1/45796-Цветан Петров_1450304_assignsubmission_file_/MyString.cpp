#include "Header.h"
//#include <iostream>

void MyString::setLenght(int arg)
{

	lenght = arg;
}

unsigned int MyString::getLenght() const
{

	return lenght;
}


MyString::MyString() 
{
	content = new(std::nothrow) char [1];
	content[0] = '\0';
	setLenght(0);

}


MyString::MyString(const MyString& str)
{
	unsigned size = str.getLenght();
	content = new(std::nothrow) char[size + 1 ];
	if (content != nullptr) {
		for(unsigned i = 0; i < size; i++) {
			content[i] = str.content[i];
			//index++;
		}
		content[size] = '\0';
		setLenght(size);
	}
	

	
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		

		

		unsigned size = other.getLenght();
		char*temp = new (std::nothrow) char[size+1];
		if (temp != nullptr) {
			for (unsigned i = 0; i < size; i++) {
				temp[i] = other.content[i];
					//index++;
			}
			temp[size] = '\0';
			setLenght(size);
			delete[] content;
			content = temp;
		}
			

		
		
	}
	return *this;
}


MyString::~MyString()
{
	delete[] content;

}
MyString::MyString(const char* str)
{
	
	int index = 0;
	content = new (std::nothrow) char[512];
	while (str[index] != '\0') {
		content[index] = str[index];
		index++;
	}

	content[index] = '\0';

	setLenght(index);
}


char& MyString::at(std::size_t pos)  
{
	try {
		if (pos < getLenght()) {
			return content[pos];
		}
		else {
			throw std::out_of_range("Index is out of range!");
		}
	}
	catch (std::out_of_range& e) {

	}
	
}

const char& MyString::at(std::size_t pos) const
{
	try {
		if (pos < getLenght()) {
			return content[pos];
		}
		else {
			throw std::out_of_range("Index is out of range!");
		}
	}
	catch (std::out_of_range& e) {

	}
	
}

char& MyString::operator[](std::size_t pos) 
{
#ifdef _DEBUG
	assert(pos <= lenght - 1);
#endif
	return content[pos];

}

const char& MyString::operator[](std::size_t pos) const {
#ifdef _DEBUG
	assert(pos <= lenght - 1);
#endif
	return content[pos];
	
}

char& MyString::front() {

#ifdef _DEBUG
	assert(lenght != 0);
#endif
	return content[0];
}

const char& MyString::front() const {
#ifdef _DEBUG
	assert(lenght!=0);
#endif
	return content[0];
	
}

char& MyString::back() {
#ifdef _DEBUG
	assert(lenght != 0);
#endif
	return content[getLenght() - 1];
}

const char& MyString::back() const {
#ifdef _DEBUG
	assert(lenght != 0);
#endif
	return content[getLenght() - 1];
}

bool MyString::empty() const {
	if (getLenght() == 0) {
		return true;
	}
	else {
		return false;
	}
}

std::size_t MyString::size() const {

	return getLenght();
}

void MyString::clear() {
	content[0] = '\0';
	setLenght(0);

}

void MyString::push_back(char c) {
	unsigned size = getLenght();
	
	char* temp = new (std::nothrow) char [size + 2];
	if (temp != nullptr) {
		for (unsigned i = 0; i < size; i++) {
			temp[i] = content[i];
		}

		temp[size] = c;
		temp[size + 1] = '\0';
		setLenght(size + 1);
		delete[] content;
		content = temp;

	}
}

void MyString::pop_back() {

#ifdef _DEBUG
	assert(lenght != 0);
#endif

	unsigned size = getLenght();

	char* temp = new (std::nothrow) char[size];
	if (temp != nullptr) {
		for (unsigned i = 0; i < size - 1; i++) {
			temp[i] = content[i];
		}

		temp[size - 1] = '\0';
		
		setLenght(getLenght() - 1 );
		delete[] content;
		content = temp;

	}
}

MyString& MyString::operator+=(char c) {

	push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {

	unsigned secondlenght = rhs.getLenght();
	char* temp = new (std::nothrow) char[lenght + secondlenght + 2];
	if (temp != nullptr) {
		unsigned index = 0;
		for (unsigned i = 0; i < lenght; i++) {
			temp[i] = content[i];
			index++;
		}

		for (unsigned i = 0; i < secondlenght; i++) {
			temp[index] = rhs.content[i];
			index++;
		}

		temp[index] = '\0';

		delete[] content;
		content = temp;
		setLenght(getLenght() + secondlenght);
	}
	return *this;
}

MyString MyString::operator+(char c) const {

	MyString res ("");
	unsigned lenght = getLenght() + 1;
	char* temp = new(std::nothrow) char[lenght + 1];
	if (temp != nullptr) {
		
		for (unsigned i = 0; i < lenght - 1; i++) {
			temp[i] = content[i];
		}

		temp[lenght - 1] = c;
		temp[lenght] = '\0';
		
		delete[] res.content;
		res.content = temp;
		res.setLenght(lenght);
	}

	return res;
}

MyString MyString::operator+(const MyString& rhs) const {

	MyString res (" ");
	unsigned firstSize = getLenght();
	unsigned secondSize = rhs.getLenght();
	unsigned size = firstSize + secondSize;
	char* temp = new(std::nothrow) char[size + 1];
	if (temp != nullptr) {
		unsigned index = 0;
		for (unsigned i = 0; i < firstSize; i++) {
			temp[index] = content[i];
			index++;
		}

		for (unsigned i = 0; i < secondSize; i++) {
			temp[index] = rhs.content[i];
			index++;
		}

		temp[size] = '\0';

		delete[] res.content;
		res.content = temp;
		res.setLenght(size);
	}

	return res;
}

const char* MyString::c_str() const {

	unsigned size = getLenght();
	char* res = new(std::nothrow) char[size + 1 ];
	if (res != nullptr) {
		for (unsigned i = 0; i < size; i++) {
			res[i] = content[i];
		}
		res[size] = '\0';
	}
	return res;
}

bool MyString::operator==(const MyString& rhs) const {

	unsigned firstSize = getLenght();
	unsigned secondSize = rhs.getLenght();
	if (firstSize == secondSize) {

		for (unsigned int i = 0; i < firstSize; i++) {
			if (content[i] != rhs.content[i]) {
				return false;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

bool MyString::operator<(const MyString& rhs) const {
	unsigned firstSize = getLenght();
	unsigned secondSize = rhs.getLenght();
	
	for (unsigned int i = 0; i < firstSize; i++) {
		if (content[i] != rhs.content[i]) {
			return false;
		}
	}

	return true;
	
}