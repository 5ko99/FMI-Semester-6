#include "Homework1.h"

void MyString::copy(const MyString& other)
{
	length = other.length;
	string = new char[length + 1];
	strcpy_s(string, length + 1, other.string);
}

void MyString::clear()
{
	delete[] string;
}

void MyString::print() const
{
	std::cout << string << '\n';
}

void MyString::push_back(char element)
{
	char* temp = new char[length + 2];
	for (int i = 0; string[i] != '\0'; i++)
	{
		temp[i] = string[i];
	}
	temp[length] = element;
	temp[length + 1] = '\0';
	clear();
	string = temp;
	length++;
}

void MyString::pop_back()
{
	char* temp = new char[length];
	for (int i = 0; i < length; i++)
	{
		temp[i] = string[i];
	}
	temp[length - 1] = '\0';
	clear();
	string = temp;
	length--;
}

MyString::MyString()
{
	string = new char[8];
	strcpy_s(string, 8, "default");
	length = 7;
}

MyString::MyString(const char* str)
{
	length = strlen(str);
	string = new char[length + 1];
	strcpy_s(string, length + 1, str);
}

MyString::MyString(const MyString& other)
{
	copy(other);
}

MyString::~MyString()
{
	clear();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	
	return *this;
}

MyString& MyString::operator+=(char c)
{
	push_back(c);
	
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	for (int i = 0; i < rhs.length; i++) 
	{
		push_back(rhs.at(i));
	}
	
	return *this;
}

MyString MyString::operator+(char c) const
{
	MyString result(string);
    result.push_back(c);
	
	return result;
}

MyString MyString::operator+(const MyString& rhs) const
{
	MyString result(string);
	result += rhs;

	return result;
}

bool MyString::empty() const
{
	return !strlen(string);
}

bool MyString::operator==(const MyString& rhs) const
{
	return !strcmp(string, rhs.string);
}

bool MyString::operator<(const MyString& rhs) const
{
	if (strcmp(string, rhs.string) < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

char& MyString::at(std::size_t pos) 
{
	try
	{
		if (pos >= strlen(string))
		{
			throw std::out_of_range("No such element");
		}
	}
	catch (const std::out_of_range& oor) 
	{
		std::cerr << "Out of Range error: " << oor.what() << '\n';		
	}
	return string[pos];
}

const char& MyString::at(std::size_t pos) const
{
	if (pos > strlen(string))
	{
		throw std::out_of_range("Element does not exist");
	}
	
	return string[pos];
}

char& MyString::operator[](std::size_t pos)
{
	return at(pos);
}

const char& MyString::operator[](std::size_t pos) const
{
	return at(pos);
}

char& MyString::front()
{
	return at(0);
}

const char& MyString::front() const
{
	return at(0);
}

char& MyString::back()
{
	return at(strlen(string) - 1);
}

const char& MyString::back() const
{
	return at(strlen(string) - 1);
}

const char* MyString::c_str() const
{
	return string;
}

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
	reg = registration;
    desc = description;
	size = space;
}

const char* Vehicle::registration() const
{
	return reg.c_str();
}

const char* Vehicle::description() const
{
	return desc.c_str();
}

std::size_t Vehicle::space() const
{
	return size;
}


void Garage::copy(const Garage& other)
{
	capacity = other.capacity;
	used = other.used;
	vehicleCount = other.vehicleCount;
	vehicleArray = new Vehicle * [capacity];
	for (unsigned int i = 0; i < capacity; i++)
	{
		vehicleArray[i] = other.vehicleArray[i];
	}
}

//throws exception
void Garage::insert(Vehicle& v)
{
	try
	{
		if (used + v.space() > capacity)
		{
			throw std::out_of_range("Not enough space");
		}
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}

	try
	{
		for (unsigned int i = 0; i < capacity; i++)
		{
			Vehicle currentVehicle = *vehicleArray[i];
			if (currentVehicle.registration() == v.registration())
			{
				throw std::out_of_range("A car with the same registration is already in the garage");
			}
		}
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}

	try {
		Vehicle** temp = new Vehicle * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			temp[i] = vehicleArray[i];
		}
        used++;
		temp[used] = &v;
		clear();
		vehicleArray = temp;
		vehicleCount++;

	}
	catch (...)
	{
		std::cerr << "Not enough memory";
	}
}

void Garage::erase(const char* registration)
{
	for (unsigned int i = 0; i < capacity; i++)
	{
		Vehicle currentVehicle = *vehicleArray[i];
		if (currentVehicle.registration() == registration)
		{
			vehicleArray[i] = vehicleArray[used - 1];
			vehicleArray[used - 1] = 0;
			used -= currentVehicle.space();
			vehicleCount--;
		}
	}
}

void Garage::clear()
{
	for (unsigned int i = 0; i < capacity; i++)
	{
		delete vehicleArray[i];
	}
	delete[] vehicleArray;
	used = 0;
	vehicleCount = 0;
}

Garage::Garage()
{
	capacity = 10;
	used = 0;
	vehicleCount = 0;
	vehicleArray = new Vehicle * [10];
	for (unsigned int i = 0; i < capacity; i++)
	{
		vehicleArray[i] = new Vehicle("parking", "spot", 0);
	}
}

Garage::Garage(std::size_t size)
{
	capacity = size;
	used = 0;
	vehicleCount = 0;
	vehicleArray = new Vehicle* [size];
	for (unsigned int i = 0; i < capacity; i++)
	{
		vehicleArray[i] = new Vehicle("parking","spot",0);
	}
}

Garage::Garage(const Garage& other)
{
	copy(other);
}

Garage::~Garage()
{
	for (unsigned int i = 0; i < capacity; i++)
	{
		delete vehicleArray[i];
	}
	delete[] vehicleArray;
}

Garage& Garage::operator=(const Garage& other) 
{
	if (this != &other)
	{
		for (unsigned int i = 0; i < capacity; i++)
		{
			delete vehicleArray[i];
		}
		delete[] vehicleArray;
		copy(other);
	}

	return *this;
}

bool Garage::empty() const
{
	return !vehicleCount;
}

const Vehicle& Garage::at(std::size_t pos) const
{
	if (pos >= capacity)
	{
		throw std::out_of_range("Car does not exist");
	}

	return *vehicleArray[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
	return *vehicleArray[pos];
}

const Vehicle* Garage::find(const char* registration) const
{
	for (int i = 0; i = used - 1; i++)
	{
		Vehicle currentVehicle = *vehicleArray[i];
		if (currentVehicle.registration() == registration)
		{
			return vehicleArray[i];
		}
	}
	return nullptr;
}

std::size_t Garage::size() const
{
	return vehicleCount;
}












