// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Петър Стоянов Овчаров
// ФН: 45805
// Специалност: информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <8:00>
// Кой компилатор използвате: <Visual C++>
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
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
const char MAX_BUFFER_SIZE = 10000;
void copyStr(char* dest, const char* src, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

class Registration
{
private:
	char registrationStr[9] = "\0";
	bool isLetter(const char c)
	{
		if (c >= 'A' && c <= 'Z')
		{
			return true;
		}
		if (c >= 'a' && c <= 'z')
		{
			return true;
		}
		return false;
	}
	bool isDigit(const char c)
	{
		if (c >= '1' && c <= '9')
		{
			return true;
		}
		if (c == '0')
		{
			return true;

		}
		return false;
	}
	bool strIsValidRegistration(const char* str)
	{

		bool first2ElementsAreLetters = isLetter(str[0]) && isLetter(str[1]);
		bool mid4ElementsAreValid = isDigit(str[2]) && isDigit(str[3]) && isDigit(str[4]) && isDigit(str[5]);
		bool last2ElementsAreValid = isLetter(str[6]) && isLetter(str[7]);

		bool firstElementIsLetterSecondIsDigit = isLetter(str[0]) && isDigit(str[1]);
		bool mid3ElementsAreValid = isDigit(str[2]) && isDigit(str[3]) && isDigit(str[4]);
		bool last2ElementsAreValidv2 = isLetter(str[5]) && isLetter(str[6]);

		return (first2ElementsAreLetters && mid4ElementsAreValid && last2ElementsAreValid)
			|| (firstElementIsLetterSecondIsDigit && mid3ElementsAreValid && last2ElementsAreValidv2);
	}
public:
	Registration(const char* str)
	{
		if (!strIsValidRegistration(str))
		{
			throw std::exception("The reristration string is not valid!");
		}
		size_t len = strlen(str);
		copyStr(this->registrationStr, str, len);
	}

	~Registration() {}
	Registration(const Registration& r)
	{
		if (!strIsValidRegistration(r.registrationStr))
		{
			throw std::exception("The reristration string is not valid!");
		}
		size_t len = strlen(r.registrationStr);
		copyStr(this->registrationStr, r.registrationStr, len);
	}
	Registration& operator=(const Registration& r)
	{
		if (this != &r)
		{
			size_t len = strlen(r.registrationStr);
			copyStr(this->registrationStr, r.registrationStr, len);
		}
		return *this;
	}
	Registration& operator=(const char* str)
	{
		if (!strIsValidRegistration(str))
		{
			throw std::exception("The reristration string is not valid!");
		}
		size_t len = strlen(str);
		copyStr(this->registrationStr, str, len);
		return *this;
	}

	bool operator==(const char* str) const
	{
		size_t len = strlen(str);
		if (len > 9 || len < strlen(this->registrationStr))
		{
			return false;
		}
		for (size_t i = 0; i < len; i++)
		{
			if (this->registrationStr[i] != str[i])
			{
				return false;
			}
		}
		return true;
	}
	const char* toString() const
	{
		return this->registrationStr;
	}
};

class Vehicle
{
public:
	const Registration regnum;
	const std::string description;
	Vehicle(const char* regnum, const char* description)
		:regnum(regnum),
		description(description)

	{
	}
	~Vehicle() {}

	Vehicle(const Vehicle& v)
		:regnum(v.regnum),
		description(v.description)
	{
	}
};

class VehicleList
{
private:
	std::size_t maxCapacity = 0;
	size_t numberOfVehicles = 0;
	Vehicle** vehicles = nullptr;
	bool regNumMatch(const char* r1, const char* r2)
	{
		size_t len = strlen(r1);
		if (len != strlen(r2))
		{
			return false;
		}
		for (size_t i = 0; i < len; i++)
		{
			if (r1[i] != r2[i])
			{
				return false;
			}
		}
		return true;
	}
public:
	VehicleList(std::size_t capacity)
		:maxCapacity(capacity),
		numberOfVehicles(0)
	{
		this->vehicles = new Vehicle * [capacity];
		for (size_t i = 0; i < capacity; i++)
		{
			this->vehicles[i] = nullptr;
		}
	}
	~VehicleList()
	{
		for (size_t i = 0; i < this->numberOfVehicles; i++)
		{
			delete this->vehicles[i];
		}
		delete[] this->vehicles;
	}
	VehicleList(const VehicleList& vl)
		:maxCapacity(vl.maxCapacity),
		numberOfVehicles(vl.numberOfVehicles)
	{
		for (size_t i = 0; i < this->numberOfVehicles; i++)
		{
			this->vehicles[i] = new Vehicle(vl.vehicles[i]->regnum.toString(), vl.vehicles[i]->description.c_str());
		}
	}
	VehicleList& operator=(const VehicleList& vl)
	{
		if (this != &vl)
		{
			try
			{
				for (size_t i = 0; i < this->numberOfVehicles; i++)
				{
					delete this->vehicles[i];
				}
				delete[] this->vehicles;

				this->maxCapacity = vl.maxCapacity;
				this->numberOfVehicles = vl.numberOfVehicles;
				for (size_t i = 0; i < this->numberOfVehicles; i++)
				{
					this->vehicles[i] = new Vehicle(vl.vehicles[i]->regnum.toString(), vl.vehicles[i]->description.c_str());
				}
			}
			catch (const std::exception& ex)
			{
				throw ex;
			}

		}
		return *this;
	}

	//добавя превозното средство с регистрационен номер regnum и описание description в списъка. 
	//Ако операцията не успее (например няма повече място, регистрационният номер е невалиден, такъв регистрационен номер вече се съдържа в списъка),
	//да се хвърля изключение от тип std::exception. Операцията да дава strong exception guarantee.
	void insert(const char* regnum, const char* description)
	{
		if (this->numberOfVehicles == this->maxCapacity)
		{
			throw std::exception("The VehicleList is already full!");
		}
		for (size_t i = 0; i < this->numberOfVehicles; i++)
		{
			if (this->vehicles[i]->regnum == regnum)
			{
				throw std::exception("There is already a vehicle with this registration number in VehicleList!");
			}
		}
		try
		{
			this->vehicles[this->numberOfVehicles] = new Vehicle(regnum, description);
			this->numberOfVehicles++;
		}
		catch (const std::exception& ex)
		{
			throw std::exception("Invalid registration number");
		}
	}

	//достъп до елемента намиращ се на позиция index. Ако такъв няма, да се хвърля изключение std::out_of_range.
	const Vehicle& at(std::size_t index) const
	{
		if (index >= this->numberOfVehicles)
		{
			throw std::out_of_range("Invalid index!");
		}
		return *this->vehicles[index];
	}

	//достъп до елемента намиращ се на позиция index.
	//Функцията да не прави проверка за коректност дали index е валидна позиция. (В debug режим assert-вайте дали index е валидна позиция).
	const Vehicle& operator[](std::size_t index) const
	{
		assert(index < this->numberOfVehicles);
		return *this->vehicles[index];
	}

	//Проверява дали списъка е празен (т.е. в него не е било добавено нито едно добавено превозно средство).
	bool empty() const { return !(this->numberOfVehicles); }

	//капацитет на списъка.
	std::size_t capacity() const { return this->maxCapacity; }

	//брой превозни средства добавени в списъка.
	std::size_t size() const { return this->numberOfVehicles; }

	//намира и връща превозното средство с регистрационен номер regnum. Ако такова няма, да се върне nullptr.
	const Vehicle* find(const char* regnum) const
	{
		for (size_t i = 0; i < this->numberOfVehicles; i++)
		{
			if (vehicles[i]->regnum == regnum)
			{
				return this->vehicles[i];
			}
		}
		return nullptr;
	}
};

int main()
{
	size_t N = 0;
	cout << "Enter the size of the VehicleList: " << endl;

	cin >> N;
	VehicleList vl(N);
	for (size_t i = 0; i < N; i++)
	{
		char regnum[MAX_BUFFER_SIZE];
		char description[MAX_BUFFER_SIZE];
		cout << "To register vehicle number " << i + 1 << ":" << endl;
		cout << "Enter the registration number of the vehicle: " << endl;
		cin >> regnum;

		cout << "Enter the description of the vehicle: " << endl;
		cin >> description;
		try
		{
			vl.insert(regnum, description);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			i--;
		}
	}
	char cmd = '\0';
	do {
		cout << "If you want to quit - type 'q' ." << endl;
		cout << "If you want to find a vehicle - type 'f' ." << endl;
		cin >> cmd;
		if (cmd == 'f')
		{
			cout << "Enter the registration number of the vehicle you want to find: " << endl;
			char regnum[MAX_BUFFER_SIZE];
			cin >> regnum;
			const Vehicle* found = vl.find(regnum);
			if (found == nullptr)
			{
				cout << "There is no such vehicle" << endl;
			}
			else
			{
				cout << "Found a vehicle:" << endl;
				cout << "Registration number: " << found->regnum.toString() << endl;
				cout << "Description: " << found->description << endl;
			}
		}
	} while (cmd != 'q');
	return 0;
}