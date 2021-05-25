// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:                                                                    Калоян Илиев
// ФН:                                                                     45793
// Специалност:                                                            Информатика
// Курс:                                                                   1 
// Административна група:
// Ден, в който се явявате на контролното:                                 24.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>        9:30
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> Visual C++
//

//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <cstdlib>

size_t min(size_t a, std::size_t b) {
	return a < b ? a : b;
}

class IntBuffer {
public:
	IntBuffer(std::size_t size)
	{
		arr = new int[size];
		n = size;
	}

	~IntBuffer()
	{
		delete[] arr;
	}

	IntBuffer(IntBuffer& other) {
		n = other.n;
		int* newPtr = new int[n];
		for (size_t i = 0; i < n; ++i) {
			newPtr[i] = other[i];
		}
		delete[] arr;
		arr = newPtr;
	}

	IntBuffer& operator=(IntBuffer other) 
	{	
		std::swap(n, other.n);
		std::swap(arr, other.arr);
		return *this;
	}

	int& operator[](std::size_t index)
	{
		assert(index >= 0 && index <= n);
		return arr[index];
	}

	const int& operator[](std::size_t index) const
	{
		assert(index >= 0 && index <= n);
		return arr[index];
	}

	IntBuffer(std::size_t size, const IntBuffer& other)
	{
		this->arr = new int[size];
		for (size_t i = 0; i < min(this->n, other.n); ++i) {
			arr[i] = other[i];
		}
		n = size;
	}

	int& at(std::size_t index)
	{
		if (index < 0 || index > n) {
			throw std::out_of_range("Invalid index!");
		}
		return arr[index];
	}

	const int& at(std::size_t index) const 
	{
		if (index < 0 || index > n) {
			throw std::out_of_range("Invalid index!");
		}
		return arr[index];
	}

	std::size_t size() const 
	{
		return n;
	}

	void copy_from(const IntBuffer& other, std::size_t count) 
	{
		if (this->n < count || other.n < count) {
			throw std::out_of_range("Size of one of the objects is less than count!");
		}
		for (size_t i = 0; i < count; ++i) {
			arr[i] = other[i];
		}
	}

	bool operator==(const IntBuffer& other) const 
	{
		if (this->n != other.n) return 0;
		for (size_t i = 0; i < n; ++i) {
			if (arr[i] != other[i]) return 0;
		}
		return 1;
	}
	/* TODO
	bool operator<(const IntBuffer& other) const 
	{
		if (this->n < other.n) return 1;
		if (this->n > other.n) return 0;
		for (size_t i = 0; i < n; ++i) {
			if (arr[i] < other[i]) {
				
			}
		}
			
	}
	*/
private:
	size_t n;
	int* arr;
};

class Set {
public:
	Set() 
	{
		elCap = 2;
		elCnt = 0;
		IntBuffer Temp(elCap);
		elements = &Temp;
	}

	void insert(int value) 
	{
		if (elCnt == 0) {
			elements[0] = value;
			return;
		}

		for (size_t i = 0; i < elCap; ++i) {
			if (elements[i] == value) {
				return;
			}
		}

		size_t counter = 0;
		while (elements->at(counter) < value) {
			counter++;
		}

		if (elCnt < elCap) {
			for (size_t i = elCap - 1; i > counter + 1; --i) {
				elements[i] = elements[i - 1];
			}
			elements[counter] = value;
			elCnt++;
		}
		else {
			IntBuffer temp(elCap * 2);
			temp.copy_from(*elements, elCnt);
			for (size_t i = elCap - 1; i > counter + 1; --i) {
				elements[i] = elements[i - 1];
			}
			elements[counter] = value;
			*elements = temp;

			elCnt++;
			elCap = elCap * 2;
		}
	}

	bool contains(int value) const 
	{
		size_t mid = elCnt / 2;
		size_t left = 0;
		size_t right = elCnt;
		do {
			if (elements->at(mid) == value) return 1;
			if (elements->at(mid) < value) {
				left = mid + 1;
				mid = (right - left) / 2;
			}
			else {
				right = mid;
				mid = (right - left) / 2;
			}
		} 		
		while (elements->at(mid) != value || mid > 0);
		return 0;
	}

	std::size_t size() const 
	{
		return elCnt;
	}

private:
	IntBuffer* elements;
	size_t elCnt;
	size_t elCap;
};


int main()
{

	/* size_t N = 0;
	std::cout << "Enter N:\n";
	std::cin >> N;
	Set generated;
	for (size_t i = 0; i < N; ++i) {
		generated.insert(std::rand());
	}
	*/ 
	return 0;
}