#include "MyString.h"
#include <string.h>
#include <cassert>

using std::cerr;
using std::out_of_range;

MyString::MyString() : words(nullptr), length(0){}

MyString::MyString(const char* str){
	length = strlen(str);
	try
	{
		words = new char[length + 1];
	}
	catch (...)
	{
		cerr << "not enough space";
	}
	
	strcpy_s(words, length+1, str);
}

MyString::MyString(const MyString& other){
	length = other.length;
	try
	{
		words = new char[length + 1];
	}
	catch (...)
	{
		cerr << "not enough space";
	}
	strcpy_s(words, length + 1, other.words);
}

MyString::~MyString(){
	delete[] words;
}

MyString& MyString::operator=(const MyString& other){
	if (this != &other) {
		delete[] words;
		length = other.length;
		try
		{
			words = new char[length + 1];
		}
		catch (...)
		{
			cerr << "not enough space";
		}
		strcpy_s(words, length + 1, other.words);
	}
	return *this;
}

char& MyString::at(std::size_t pos){
	if (pos >= 0 && pos <= length) {
		return words[pos];
	} else {
		throw out_of_range("pos>length");
	}
}

const char& MyString::at(std::size_t pos) const{
	if (pos >= 0 && pos <= length) {
		return words[pos];
	}
	else {
		throw out_of_range("pos>length");
	}
}

char& MyString::operator[](std::size_t pos){
	assert(length > pos && "there is no such position");
	assert(length < 0 && "there is no such position");
	return words[pos];
}

char& MyString::front(){
	assert(!empty() && "words is empty");
	return words[0];
}

const char& MyString::front() const{
	assert(!empty() && "words is empty");
	return words[0];
}

char& MyString::back(){
	assert(!empty() && "words is empty");
	return words[length];
}

const char& MyString::back() const{
	assert(!empty() && "words is empty");
	return words[length];
}

bool MyString::empty() const{
	if (length == 0) return true;
	return false;
}

std::size_t MyString::size() const{
	return length;
}

void MyString::clear(){
	if (!empty()) {
		delete[] words;
		length = 0;
	}
}

void MyString::push_back(char c){
	words += c;
}

void MyString::pop_back(){
	char* copy = new char[length];
	strcpy_s(copy, length, words);
	delete[] words;
	--length;
	words = new char[length+1];
	for (size_t i = 0; i < length; i++)
	{
		words[i] = copy[i];
	}
	words[length] = '\0';
	delete[] copy;
}

MyString& MyString::operator+=(char c){
	char* copy = new char[length + 1];
	strcpy_s(copy, length, words);
	delete[] words;
	++length;
	copy[length - 1] = c;
	copy[length] = '\0';
	words = copy;
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs){
	char* copy = new char[length + rhs.length + 1];
	strcpy_s(copy, length, words);
	delete[] words;
	int saveLength = length;
	length += rhs.length;
	for (size_t i = saveLength; i < length; i++)
	{
		copy[i] = rhs.words[i - saveLength];
	}
	copy[length] = '\0';
	words = copy;
	return *this;
}

MyString MyString::operator+(char c) const{
	MyString result(*this);
	result += c;
	return result;
}

MyString MyString::operator+(const MyString& rhs) const{
	MyString result(*this);
	result += rhs;
	return result;
}

const char* MyString::c_str() const{
	return this->words;
}

bool MyString::operator==(const MyString& rhs) const {
	if (length != rhs.length) {
		return false;
	} else {
		for (size_t i = 0; i < length; i++)
		{
			if (words[i] != rhs.words[i]) return false;
		}
		return true;
	}

}

bool MyString::operator<(const MyString& rhs) const{
	for (size_t i = 0; i < std::min(length, rhs.length); i++)
	{
		if (words[i] < rhs.words[i]) {
			return true;
		} else if (words[i] < rhs.words[i]) {
			return false;
		}
	}
	if (length < rhs.length) {
		return true;
	} else {
		return false;
	}
}
