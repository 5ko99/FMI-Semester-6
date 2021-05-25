// 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� 1
// 
// ���: ������ �������� ��������
// ��: 81921
// �����������: ���������� �����
// ����: 3
// ��������������� �����: 2
// ���, � ����� �� ������� �� �����������: 24.04.2021 
// ������� ��� �� �����������: 9:30
// ��� ���������� ����������: Visual Studio
//
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class IntBuffer {
private:
	size_t sizeOfArray;
	int* elements = new int [sizeOfArray];
public:

	IntBuffer (const IntBuffer& other) {
		this->sizeOfArray = other.sizeOfArray;
		this->elements = other.elements;
	}

	IntBuffer& operator=(const IntBuffer& other) {
		if (this != &other) {
			for (int i = 0; i < this->sizeOfArray; i++) {
				elements[i] = other.elements[i];
			}
		}
		return *this;
	}

	IntBuffer(size_t size) {
		this->elements[sizeOfArray] = this->elements[size];
	}

	IntBuffer(size_t size, const IntBuffer& other) {
		this->elements[sizeOfArray] = this->elements[size];
		if (size >= other.sizeOfArray) {
			this->elements = other.elements;
		}
		else {
			for (size_t i = 0; i < size; i++) {
				this->elements[i] = other.elements[i];
			}
		}
	}

	int& at(size_t index) {
		for (size_t i = 0; i < this->sizeOfArray; i++) {
			if (this->elements[i] == this->elements[index])
				return this->elements[index];
		}
	}

	const int& at(size_t index) const {
		for (size_t i = 0; i < this->sizeOfArray; i++) {
			if (this->elements[i] == this->elements[index])
				return this->elements[index];
		}
	}

	int& operator[](size_t index) {

	}

	const int& operator[](size_t index) const {

	}

	size_t size() const {
		return this->sizeOfArray;
	}

	void copy_from(const IntBuffer& other, size_t count) { 
		for (size_t i = 0; i < count; i++) {
			this->elements[i] = other.elements[i];
		}
	}

	bool operator==(const IntBuffer& other) const {
		if (this->sizeOfArray == other.sizeOfArray) {
			for (int i = 0; i < this->sizeOfArray; i++) {
				if (this->elements[i] == other.elements[i])
					continue;
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool operator<(const IntBuffer& other) const {

	}

	~IntBuffer() {
		delete[] this->elements;
	}
};

class Set {
private:
	IntBuffer elements;
public:
	Set() : elements(0){}

	size_t size() const {
		return this->elements.size();
	}
};

int main()
{

	return 0;
}