// 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� 1
// 
// ���:������ �������
// ��:45513
// �����������:�����������
// ����:2
// ��������������� �����:1
// ���, � ����� �� ������� �� �����������: 24.04.2021
// ������� ��� �� �����������: 09:30
// ��� ���������� ����������:  Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 


#include <cstddef>
#include<cstdlib>
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

const int MAX_SIZE = 1000;

class IntBuffer {
	int *masive[MAX_SIZE];
	std::size_t *size;

public:
	IntBuffer()
	{
		*masive = NULL;
		*size = 0;
	}

	~IntBuffer()
	{
		delete[]masive;
		delete[]size;
	}

	int getSize()const
	{
		return *size;
	}

	void setSize(int newSize)
	{
		*size = newSize;

	}
	 
	IntBuffer(const IntBuffer& k)
	{
		size = new std::size_t;
		*size = k.getSize();
	}


	IntBuffer(std::size_t sizef)
	{
		size = new std::size_t;
		*size = sizef;
	}

	int& at(std::size_t index)
	{	
		return *masive[index];
	}

	
};

class Set {

	IntBuffer elements;
public:
	Set(int value) :elements(value)
	{};
	
	


};

int main()
{

	return 0;
}