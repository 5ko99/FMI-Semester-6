// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Румен Димитров
// ФН: 45515
// Специалност: Информатика
// Курс: 3
// Административна група: 2
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: Visual Studio 2019
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>


#pragma region IB
class IntBuffer {
public:
	IntBuffer(std::size_t size);
	IntBuffer(std::size_t size, const IntBuffer& other);
	~IntBuffer();

	int& at(std::size_t index);
	const int& at(std::size_t index) const;
	std::size_t get_size() const;
	int& operator[](std::size_t index);
	const int& operator[](std::size_t index) const;
	void set_elem(std::size_t index, int value);


	bool operator==(const IntBuffer& other) const;
	void resize();
	


private:
	std::size_t size;
	int* dyn_array;

};

IntBuffer::IntBuffer(std::size_t size) {
	dyn_array = new int[size];
	for (int i = 0; i < size; i++) {
		dyn_array[i] = 0;
	}
}

IntBuffer::IntBuffer(std::size_t size, const IntBuffer& other) {
	dyn_array = new int[size];
	std::size_t N = 0;
	if (size > other.get_size())
		N = other.get_size();
	else
		N = size;
	for (int i = 0; i < N; i++) {
		dyn_array[i] = other.dyn_array[i];
	}
}

IntBuffer::~IntBuffer() {
	delete[] dyn_array;
}

int& IntBuffer::at(std::size_t index) {
	return dyn_array[index];
}

const int& IntBuffer::at(std::size_t index) const {
	return dyn_array[index];
}


std::size_t IntBuffer::get_size() const {
	return size;
}

int& IntBuffer::operator[](std::size_t index) {
	assert(index >= 0 && index < size);
	return dyn_array[index];
}

const int& IntBuffer::operator[](std::size_t index) const {
	assert(index >= 0 && index < size);
	return dyn_array[index];
}

bool IntBuffer::operator==(const IntBuffer& other) const {
	if (size == other.size) {
		for (int i = 0; i < size; i++) {
			if (dyn_array[i] != other.dyn_array[i])
				return false;
		}
		return true;
	}
	return false;
}

void IntBuffer::set_elem(std::size_t index, int value) {
	if (index < size) {
		dyn_array[index] = value;
	}
	else {
		resize();
		dyn_array[index] = value;
	}
}

void IntBuffer::resize() {
	int *dyn_array2 = new int[size];
	for (int i = 0; i < size; i++) {
		dyn_array2[i] = dyn_array[i];
	}
	delete[] dyn_array;
	dyn_array = new int[size * 2];
	for (int i = 0; i < size; i++) {
		dyn_array[i] = dyn_array2[i];
	}
	delete[] dyn_array2;
}

#pragma endregion

class Set {
public:
	Set();
	//void insert(int value);
	bool contains(int value) const;
	std::size_t size() const;
private:
	IntBuffer* elements;
};

Set::Set() {
	elements = new IntBuffer(2);
}


bool Set::contains(int value) const {
	int idx = size() / 2;
	while (value != (*elements)[idx]) {
		if (value > (*elements)[idx]) {
			idx = (idx + size()) / 2;
			if (idx == size() - 1 && value != (*elements)[idx]) return false;
		}
		else if (value < (*elements)[idx]) {
			idx = idx / 2;
			if (idx == 0 && value != (*elements)[idx]) return false;
		}
	}
	if (value == (*elements)[idx]) return true;
}

std::size_t Set::size() const {
	return elements->get_size();
}

int main()
{

	return 0;
}