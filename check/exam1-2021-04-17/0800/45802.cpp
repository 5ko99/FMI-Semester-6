// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Асен Димитров Плеснев
// ФН: 45802
// Специалност: Информатика
// Курс: I
// Административна група: 5
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstddef> 

using namespace std;

class Registration {
	char* regNum = nullptr;

	size_t currSize = 0;

	size_t originalSize = 9;

	bool checkIfNumberIsValid(const char* str)
	{
		size_t strSize = strlen(str);

		if (strSize == this->originalSize - 1 || strSize == this->originalSize - 2)
		{
			this->currSize = strSize + 1;

			if (this->originalSize - this->currSize == 1)
			{
				for (size_t i = 0; i < this->currSize - 1; i++)
				{
					if (i == 0 || i == 5 || i == 6)
					{
						if (!isalpha(str[i]))
						{
							return false;
						}
					}
					else
					{
						if (!isdigit(str[i]))
						{
							return false;
						}
					}
				}
			}
			else
			{
				for (size_t i = 0; i < this->currSize - 1; i++)
				{
					if (i == 0 || i == 1 || i == 6 || i == 7)
					{
						if (!isalpha(str[i]))
						{
							return false;
						}
					}
					else
					{
						if (!isdigit(str[i]))
						{
							return false;
						}
					}
				}
			}

			return true;

		}

		return false;
	}

public:
	Registration(const char* str)
	{
		try
		{
			if (!this->checkIfNumberIsValid(str))
			{
				throw exception("Registration number must be 9 chars long and must be in valid format");
			}
		}
		catch (const exception& e)
		{
			cerr << e.what();
		}

		this->regNum = new char[this->currSize];

		for (size_t i = 0; i < this->currSize - 1; i++)
		{
			this->regNum[i] = str[i];
		}

		this->regNum[this->currSize - 1] = '\0';
	}

	Registration(const Registration& r)
	{
		(*this) = r;
	}

	~Registration()
	{
		delete[] this->regNum;
	}

	Registration& operator=(const Registration& r)
	{
		try
		{
			if (!this->checkIfNumberIsValid(r.regNum))
			{
				throw exception("Registration number must be 9 chars long and must be in valid format");
			}
		}
		catch (const exception & e)
		{
			cerr << e.what();
		}

		size_t strSize = strlen(r.regNum);

		this->regNum = new char[this->originalSize];

		for (size_t i = 0; i < this->currSize -1; i++)
		{
			this->regNum[i] = r.regNum[i];
		}

		this->regNum[this->currSize - 1] = '\0';
	}

	Registration& operator=(const char* str)
	{
		try
		{
			if (!this->checkIfNumberIsValid(str))
			{
				throw exception("Registration number must be 9 chars long and must be in valid format");
			}
		}
		catch (const exception & e)
		{
			cerr << e.what();
		}

		size_t strSize = strlen(str);

		this->regNum = new char[this->originalSize];

		for (size_t i = 0; i < this->currSize - 1; i++)
		{
			this->regNum[i] = str[i];
		}

		this->regNum[this->currSize - 1] = '\0';
	}

	bool operator==(const char* str) const
	{
		return strcmp(this->regNum, str);
	}

	const char* toString() const
	{
		return this->regNum;
	}

};

class Vehicle {

	char* reg = nullptr;
	string desc;

	Registration* rp = nullptr;

public:
	
	const Registration* regnum = nullptr;
	const string description = this->desc;

	Vehicle(const char* regnum, const char* description)
	{
		size_t strSize = strlen(regnum);

		delete[] this->reg;

		this->reg = new char[strSize + 1];

		for (size_t i = 0; i < strSize - 1; i++)
		{
			this->reg[i] = regnum[i];
		}

		this->reg[strSize - 1] = '\0';

		this->desc = description;

		Registration r = this->reg;

		this->regnum = &r;
	}
};

class VehicleList {
	size_t listCapacity;
	size_t currIndex = 0;
	Vehicle** collection = nullptr;

	bool hasTheSameRegNum(const char* regnum)
	{
		for (size_t i = 0; i < this->currIndex; i++)
		{
			int res = strcmp(this->collection[i]->regnum->toString(), regnum);

			if (res == 0)
			{
				return true;
			}
		}

		return false;
	}

public:
	VehicleList(size_t capacity)
	{
		this->listCapacity = capacity;

		delete[] this->collection;

		this->collection = new Vehicle*[capacity];
	}

	VehicleList(const VehicleList& vl)
	{
		(*this) = vl;
	}

	~VehicleList()
	{
		delete[] this->collection;
	}

	VehicleList& operator=(const VehicleList& vl)
	{
		this->listCapacity = vl.listCapacity;
		this->currIndex = vl.currIndex;
		delete[] this->collection;

		Vehicle** arr = new Vehicle * [vl.listCapacity];

		for (size_t i = 0; i < vl.currIndex; i++)
		{
			arr[i] = vl.collection[i];
		}

		this->collection = arr;

		return *this;
	}

	void insert(const char* regnum, const char* description)
	{
		try
		{
			if (this->listCapacity <= 0)
			{
				throw exception("Not enough space in Vehicle List");
			}

			if (this->hasTheSameRegNum(regnum))
			{
				throw exception("Vehicle with this regNum is already in this List");
			}
		}
		catch (const exception& e)
		{
			cerr << e.what() << endl;
		}

		Vehicle v(regnum, description);

		this->collection[this->currIndex] = &v;

		this->currIndex += 1;
		this->listCapacity -= 1;
	}

	const Vehicle& at(std::size_t index) const
	{
		try
		{
			if (index < 0 || index > this->currIndex)
			{
				throw out_of_range("Index is out of range");
			}
		}
		catch (const out_of_range& e)
		{
			cerr << e.what() << endl;
		}

		return *(this->collection[index]);
	}

	const Vehicle& operator[](std::size_t index) const
	{
		assert(index >= 0 || index < this->currIndex);

		return *(this->collection[index]);
	}

	bool empty() const
	{
		return this->currIndex == 0;
	}

	size_t capacity() const
	{
		return this->listCapacity;
	}

	size_t size() const
	{
		return this->currIndex;
	}

	const Vehicle* find(const char* regnum) const
	{
		if (this->currIndex == 0)
		{
			return nullptr;
		}

		for (size_t i = 0; i < this->currIndex; i++)
		{
			int res = strcmp(regnum, this->collection[i]->regnum->toString());

			if (res == 0)
			{
				return this->collection[i];
			}
		}

		return nullptr;
	}
};

int main()
{
	size_t n;

	cout << "Enter n: ";
	cin >> n;

	VehicleList vl(n);

	for (size_t i = 0; i < n; i++)
	{
		string regnum;
		string desc;

		cout << "Enter regnum: ";
		cin >> regnum;

		cout << "Enter description: ";
		cin >> desc;

		char* reg = &regnum[0];
		char* description = &desc[0];

		vl.insert(reg, description);
	}

	string regNumber;

	cout << "Insert regNumber to find: ";
	cin >> regNumber;

	char* regToFind = &regNumber[0];

	const Vehicle* vehicle = vl.find(regToFind);

	if (!vehicle)
	{
		cout << "Vehicle with regNumber " << regNumber << " is not in the Vehicle List";
	}
	else
	{
		cout << "Vehicle with regNumber " << regNumber << " is in the Vehicle List";
	}
	return 0;
}