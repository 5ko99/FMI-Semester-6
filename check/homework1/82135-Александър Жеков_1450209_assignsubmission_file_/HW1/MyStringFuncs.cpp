#include "MyString.h"


// Constructors and Destructor
MyString::MyString() {
	strPtr = nullptr;								// Default constructor
	length = 0;
}

MyString::MyString(const char* str) {
	if (str == nullptr) {
		length = 0;
		strPtr = nullptr;
	}
	else {
		length = strlen(str);							// C String copy constructor
		bool freeMem = true;

		try {
			strPtr = new char[length + 1];					// Initializes new object
		}
		catch (std::bad_alloc& ba) {
			freeMem = false;
			strPtr = nullptr;
			length = 0;
			throw;
		}

		if (freeMem) {
			memcpy(strPtr, str, length + 1);
		}
	}
}

MyString::MyString(const MyString& str) {
	if (str.strPtr == nullptr) {
		length = 0;
		strPtr = nullptr;
	}
	else {
		length = str.length;							// C String copy constructor
		bool freeMem = true;

		try {
			strPtr = new char[length + 1];					// Initializes new object
		}
		catch (std::bad_alloc& ba) {
			freeMem = false;
			strPtr = nullptr;
			length = 0;
			throw;
		}

		if (freeMem) {
			memcpy(strPtr, str.strPtr, length + 1);
		}
	}
}													

MyString::~MyString() {
	if (strPtr != nullptr) {						// Destructor
		delete strPtr;								// Deallocates strPtr from the heap
	}								
}


// Functions
char& MyString::at(std::size_t pos) {
	if (pos < length) {
		return *(strPtr + pos);									// Takes in position
	}															// Returns char at that position in the string
	else {														// or throws out_of_range exception
		throw std::out_of_range("No such position in string");
	}
}

const char& MyString::at(std::size_t pos) const {
	if (pos < length) {
		return *(strPtr + pos);
	}															// Const only version of MyString::at(std::size_t pos)
	else {
		throw std::out_of_range("No such position in string");
	}
}

char& MyString::front() {
	return *strPtr;	
}

const char& MyString::front() const {		
	return *strPtr;
}

char& MyString::back() {
	return *(strPtr + length - 1);
}

const char& MyString::back() const {
	return *(strPtr + length - 1);
}

bool MyString::empty() const {
	return (strPtr == nullptr || length == 0);
}

std::size_t MyString::size() {
	return length;
}

void MyString::clear() {
	if (strPtr != nullptr) {
		delete strPtr;											// Frees heap memory, nullifies strPtr
	}															// and makes length equal to 0
	strPtr = nullptr;
	length = 0;
}

void MyString::push_back(char c) {
	bool freeMem = true;

	if (strPtr == nullptr) {
		try {
			strPtr = new char[2];
		}
		catch (std::bad_alloc& ba) {
			throw;
			freeMem = false;
		}

		if (freeMem) {
			strPtr[0] = c;
			strPtr[1] = '\0';
			length = 1;
		}
	}
	else {
		char* destPtr = nullptr;
		try {
			destPtr = new char[length + 2];
		}
		catch (std::bad_alloc& ba) {
			throw;
			freeMem = false;
		}

		if (freeMem) {
			memcpy(destPtr, strPtr, length);
			memcpy(destPtr + length, &c, 1);
			*(destPtr + length + 1) = '\0';
			delete strPtr;
			strPtr = destPtr;
			++length;
		}
	}
}

void MyString::pop_back() {
	if (length == 1) {
		this->clear();
	}
	else {
		*(strPtr+length-1) = '\0';
		--length;
	}
}

const char* MyString::c_str() const {
	if (this->strPtr == nullptr) {
		return nullptr;
	}
	else {
		char* destPtr = nullptr;
		try {
			destPtr = new char[length + 1];
		}
		catch (std::bad_alloc& ba) {
			throw;
			return nullptr;
		}

		memcpy(destPtr, strPtr, length + 1);
		return destPtr;
	}
}


// Operators
char& MyString::operator[](std::size_t pos) {
	return *(strPtr + pos);
}

const char& MyString::operator[](std::size_t pos) const {
	return *(strPtr + pos);
}

MyString& MyString::operator=(const MyString& otherstr) {
	bool freeMem = true;
	char* destPtr = nullptr;

	try {
		destPtr = new char[otherstr.length + 1];
	}
	catch (std::bad_alloc& ba) {
		throw;
		freeMem = false;
	}

	if (freeMem) {
		length = otherstr.length;
		memcpy(destPtr, otherstr.strPtr, length + 1);
		if (strPtr != nullptr) {
			delete strPtr;
		}
		strPtr = destPtr;
	}

	return *this;
}

MyString& MyString::operator=(const char* otherstr) {
	bool freeMem = true;
	char* destPtr = nullptr;

	try {
		destPtr = new char[strlen(otherstr) + 1];
	}
	catch (std::bad_alloc& ba) {
		throw;
		freeMem = false;
	}

	if (freeMem) {
		length = strlen(otherstr);
		memcpy(destPtr, otherstr, length + 1);
		if (strPtr != nullptr) {
			delete strPtr;
		}
		strPtr = destPtr;
	}

	return *this;
}

MyString& MyString::operator+=(char c) {
	bool freeMem = true;
	char* destPtr = nullptr;
	
	try {
		destPtr = new char[length + 2];
	}
	catch (std::bad_alloc& ba) {
		throw;
		freeMem = false;
	}

	if (freeMem) {
		memcpy(destPtr, strPtr, length);
		*(destPtr + length) = c;
		*(destPtr + length + 1) = '\0';
		if (strPtr != nullptr) {
			delete strPtr;
		}
		++length;
		strPtr = destPtr;
	}

	return *this;
}

MyString& MyString::operator+=(const MyString& otherstr) {

	if (otherstr.strPtr == nullptr) {
		if (this->strPtr == nullptr) {
			MyString tempstr;
			return tempstr;
		}
		return *this;
	}

	if (this->strPtr == nullptr) {
		MyString tempstr(otherstr);
		return tempstr;
	}

	bool freeMem = true;
	char* destPtr = nullptr;

	try {
		destPtr = new char[otherstr.length + length + 1];
	}
	catch (std::bad_alloc& ba) {
		throw;
		freeMem = false;
	}

	if (freeMem) {
		memcpy(destPtr, strPtr, length);
		memcpy(destPtr + length, otherstr.strPtr, otherstr.length + 1);
		delete strPtr;
		length += otherstr.length;
		strPtr = destPtr;
	}

	return *this;
}

MyString MyString::operator+(char c) const {
	bool freeMem = true;
	MyString tempstr;

	try {
		tempstr.strPtr = new char[length + 2];
	}
	catch (std::bad_alloc& ba) {
		throw;
		freeMem = false;
	}

	if (freeMem) {
		memcpy(tempstr.strPtr, strPtr, length);
		tempstr[length] = c;
		tempstr[length + 1] = '\0';
		tempstr.length = length + 1;
		return tempstr;
	}
	else {
		if (strPtr != nullptr) {
			return *this;
		}
	}
	return tempstr;
}

MyString MyString::operator+(const MyString& otherstr) const {
	MyString tempstr;
	if (otherstr.strPtr == nullptr) {
		if (strPtr == nullptr) {
			return tempstr;
		}
	}
	else {
		tempstr.strPtr = new char[otherstr.length + length + 1];
		memcpy(tempstr.strPtr, strPtr, length);
		memcpy(tempstr.strPtr + length, otherstr.strPtr, otherstr.length + 1);
		tempstr.length = length + otherstr.length;
		return tempstr;
	}
	return *this;
}

bool MyString::operator==(const MyString& otherstr) const {
	if (strPtr == nullptr && otherstr.strPtr == nullptr) {
		return true;
	}
	else if (strPtr == nullptr || otherstr.strPtr == nullptr) {
		return false;
	}
	else {
		return !strcmp(strPtr, otherstr.strPtr);
	}
}

bool MyString::operator<(const MyString& otherstr) const {
	if (strPtr == nullptr && otherstr.strPtr == nullptr) {
		return false;
	}
	else if (strPtr == nullptr && otherstr.strPtr != nullptr) {
		return true;
	}
	else if (strPtr != nullptr && otherstr.strPtr == nullptr) {
		return false;
	}
	else {
		return (strcmp(strPtr, otherstr.strPtr) < 0);
	}
}