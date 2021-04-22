// 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� 1
// 
// ���: ������ ������ �����
// ��: 45827
// �����������: �����������
// ����: 1
// ��������������� �����: 6
// ���, � ����� �� ������� �� �����������: 17.4.2021
// ������� ��� �� �����������: <8:00>
// ��� ���������� ����������: <Visual C++>
//

// (������ �� �������� ���� �������� ���� ���� �� ���������)
// ����� ��-���� � ���������� �� Visual C++.
// ��� ���������� ���� ����������, ������ �� �� ��������.
// ��� ���� strlen, strcmp � �.�. �� ���������� ���� deprecated,
// ����� ��� �����������:
//
// * �� ���������� ����������� ������ �� ���� �������
//   (strlen_s, strcmp_s � �.�.). � ���� ������ ������ ��
//   �������� �������� ��-���� #define ���������.
//
// * �� ���������� _CRT_SECURE_NO_WARNINGS ����� ��
//   �������� ����������� header ������� �� ������������
//   ����������.
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include < cctype >
#include<exception>

class Registration
{
public:
	Registration() = delete;
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;

private:
	bool validateRegistration(const char* str);
	char registrationStr[9];
};
bool Registration :: validateRegistration(const char* str)
{
	if (str == nullptr)
		return false;

	if (strlen(str) < 8 && strlen(str) > 9)
		return false;

	if (strlen(str) == 8)
	{
		if (!isalpha(str[0]) == false || !isalpha(str[6]) == false || !isalpha(str[5]) == false)
			return false;

		if(!isalnum(str[1]) == false || !isalnum(str[2]) == false || !isalnum(str[3]) || !isalnum(str[4]) == false)
			return false;
	}

	if (strlen(str) == 9)
	{
		if (isalpha(str[0]) == false || !isalnum(str[1]) == false || !isalpha(str[6]) == false || !isalpha(str[7]) == false)
			return false;

		if (!isalnum(str[2]) == false || !isalnum(str[3]) == false || !isalnum(str[4]) == false || !isalnum(str[5]) == false)
			return false;
	}

	return true;
}

Registration::Registration(const char* str)
{
	if(validateRegistration(str) == false)
		throw std::exception("String in not valid");

	strcpy(this->registrationStr, str);
}

Registration& Registration :: operator=(const char* str)
{
	try
	{
		if (validateRegistration(str) == true)
		{
			strcpy(this->registrationStr, str);
		}
	}
	catch (const std::exception&)
	{
		throw;
	}
	return *this;
}

bool Registration :: operator==(const char* str) const
{
	if (strcmp(this->registrationStr, str) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
const char* Registration :: toString() const
{
	char buffer[9];
	for (int i = 0; i < 8; i++)
	{
		buffer[i] = this->registrationStr[i];
	}
	buffer[8] = '\0';
	return buffer;
}
//---------------------------------------------------------
class Vehicle
{
public:
	Vehicle() = delete;
	Vehicle(const char* regnum, const char* description);

private:
	Registration regnum{"00000000"};
	std::string description;
};

Vehicle :: Vehicle(const char* regnum, const char* description)
{
	this-> description = description;
	this->regnum = regnum;
}

//---------------------------------------------------------

class VehicleList
{
public:
	VehicleList(std::size_t capacity);
	~VehicleList();
	VehicleList(const VehicleList& other);
	VehicleList& operator=(VehicleList other);
private:
	Vehicle** list;
	size_t listSize;
	size_t capacity;
};

VehicleList :: VehicleList(std::size_t capacity)
{
	this->capacity = capacity;
	this->listSize = 0;
	Vehicle** list = new Vehicle * [capacity];
}
VehicleList :: ~VehicleList()
{
	for (int i = 0; i < this->listSize ;i++)
	{
		delete[] list[i];
	}

	delete[] list;
	list = nullptr;

	this->capacity = 0;
	this->listSize = 0;
}
VehicleList::VehicleList(const VehicleList& other)
{
	this->capacity = other.capacity;
	this->listSize = other.listSize;

	for (int i = 0; i < this->listSize; i++)
	{
		//...
	}
}
VehicleList& VehicleList :: operator=(VehicleList other)
{
	return *this;
}




int main()
{
	

	return 0;
}