// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Ива Мавродиева
// ФН: 45477
// Специалност: Информатика
// Курс: 2
// Административна група: 2
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 09:30
// Кой компилатор използвате: Visual C++
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
// #define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

#define OUT_OF_RANGE_POSSITION_OF_BUFFURE "The given index is not valid."
#define INITIAL_CAPACITY_OF_SET 2

class IntBuffer {

public:
	IntBuffer(size_t size);
	IntBuffer(size_t size, const IntBuffer& other);
	IntBuffer& operator=(const IntBuffer& other);
	~IntBuffer();
	int& at(std::size_t index);
	const int& at(std::size_t index) const;
	int& operator[](std::size_t index);
	const int& operator[](std::size_t index) const;
	size_t size() const;
	void copy_from(const IntBuffer& other, size_t count);
	bool operator==(const IntBuffer& other) const;
	bool operator<(const IntBuffer& other) const;

private:
	void clean();
	void copy(size_t size, const IntBuffer& other);
	bool isValidIndex(size_t index) const;


private:

	int* buffer;
	size_t buffSize;
};

IntBuffer::IntBuffer(size_t size) {

	this->buffer = new int[size];

	if (!this->buffer) {
		this->buffer = nullptr;
		throw new bad_alloc();
	}

	this->buffSize = size;
}

IntBuffer::IntBuffer(size_t size, const IntBuffer& other) {
	copy(size,other);
}

IntBuffer& IntBuffer::operator=(const IntBuffer& other) {

	clean();
	int* buff = new int[other.size()];

	if (!buff) {
		throw new bad_alloc();
	}

	for (size_t i = 0; i < other.size(); i++) {
		buff[i] = other[i];
	}

	this->buffer = buff;
	this->buffSize = other.size();
	return *this;
}

IntBuffer::~IntBuffer(){
	clean();
}

int& IntBuffer::at(size_t index) {

	if (!isValidIndex(index)) {
		throw new out_of_range(OUT_OF_RANGE_POSSITION_OF_BUFFURE);
	}
	return this->buffer[index];
}

const int& IntBuffer::at(size_t index) const {

	if (!isValidIndex(index)) {
		throw new out_of_range(OUT_OF_RANGE_POSSITION_OF_BUFFURE);
	}
	return this->buffer[index];
}

size_t IntBuffer::size() const{
	return this->buffSize;
}

int& IntBuffer::operator[](size_t index) {
	assert(index < this->buffSize);
	return this->buffer[index];
}

const int& IntBuffer::operator[](size_t index) const {
	assert(index < this->buffSize);
	return this->buffer[index];
}

bool IntBuffer::operator==(const IntBuffer& other) const{

	if (this->buffSize != other.size()) {
		return false;
	}

	for (size_t i = 0; i < this->buffSize; i++) {
		if (this->buffer[i] != other[i]) {
			return false;
		}
	}
	return true;
}

bool IntBuffer::operator<(const IntBuffer& other) const {

	if (this->buffSize > other.size()) {
		return false;
	}

	for (size_t i = 0; i < this->buffSize; i++) {
		if (this->buffer[i] > other[i]) {
			return false;
		}
	}
	return true;
}

void IntBuffer::copy_from(const IntBuffer& other, size_t count) {

	if (count > this->buffSize || count > other.size()) {
		throw new out_of_range(OUT_OF_RANGE_POSSITION_OF_BUFFURE);
	}

	clean();
	copy(count, other);
}


bool IntBuffer::isValidIndex(size_t index) const {
	return index < this->buffSize;
}

void IntBuffer::copy(size_t size, const IntBuffer& other) {

	size_t n = size <= other.size() ? size : other.size();

	int* buff = new int[n];

	if (!buff) {
		throw new bad_alloc();
	}

	for (size_t i = 0; i < n; i++) {
		buff[i] = other[i];
	}

	this->buffer = buff;
	this->buffSize = size;
}

void IntBuffer::clean() {
	this->buffSize = 0;
	delete[] this->buffer;
}

class Helper {
public:
	static size_t countDigits(int value) {

		size_t count = 0;

		while(value != 0) {
			count += 1;
			value /= 0;
		}
		return count;
	}

	static IntBuffer& allocateBuffer(int value) {

		size_t size = countDigits(value);
		int* buff = new int[size];

		for(size_t i = size - 1; i >= 0;i--){
			buff[i] = value % 10;
			value /= 10;
		}

		IntBuffer* intBuff = new IntBuffer(size);

		for (size_t i = 0; i < size; i++) {
			intBuff[i] = buff[i];
		}

		return *intBuff;
	}
};

class Set {

public:
	Set();
	~Set();
	void insert(int value);
	bool contains(int value) const;
	size_t size() const;

private:
	void clean();
	void resize();

private:

	IntBuffer** elements;
	size_t capacity;
	size_t sizeOfEl;
};

Set::Set() {

	IntBuffer** buff = new IntBuffer*[INITIAL_CAPACITY_OF_SET];

	if (!buff) {
		throw new bad_alloc();
	}

	this->elements = buff;
	this->capacity = INITIAL_CAPACITY_OF_SET;
	this->sizeOfEl = 0;
}

Set::~Set() {
	clean();
}

bool Set::contains(int value) const {

	size_t digits = Helper::countDigits(value);
	IntBuffer buffer = Helper::allocateBuffer(value);

	for (size_t i = 0; i < this->sizeOfEl; i++) {
		if(this->elements[i] == &buffer){
			return true;
		}
	}
	return false;
}

void Set::insert(int value) {

	if (contains(value)) {
		throw new bad_alloc();
	}

	if (this->sizeOfEl == this->capacity) {
		resize();
	}

	IntBuffer newBuff = Helper::allocateBuffer(value);
	this->elements[sizeOfEl++] = &newBuff;
}

size_t Set::size() const{
	return this->sizeOfEl;

}

void Set::resize() {

	size_t newCapacity = this->capacity * 2;

	IntBuffer** buff = new IntBuffer*[newCapacity];
	if (!buff) {
		throw new bad_alloc();
	}

	for (size_t i = 0; i < this->sizeOfEl; i++) {
		buff[i] = this->elements[i];
	}

	delete[] this->elements;
	this->elements = buff;
	this->capacity = newCapacity;
}

void Set::clean() {

	for (size_t i = 0; i < this->sizeOfEl; i++) {
		delete this->elements[i];
	}

	delete[] this->elements;
	this->elements = nullptr;
	this->sizeOfEl = 0;
	this->capacity = 0;
}

int main()
{
	size_t n;
	cin >> n;
	Set set();
	return 0;
}