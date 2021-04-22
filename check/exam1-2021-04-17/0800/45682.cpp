// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Ангел Щупалов
// ФН: 45682
// Специалност: Информатика
// Курс:1
// Административна група:5
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//


#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <string>
#include<iostream>
using namespace std; 


class Registration
{
public:

	Registration Registrations(const char* str)
	{
		std::string RegistrationNumber = str;



		if (RegistrationNumber == "") {
			throw new std::exception;
			std::cout << "There is no registration number.";
		}

		

	}
	char toString[9];



};

class Vehicle
{



public:
	Vehicle Vehicles(const char* regnum, const char* description)
	{

		std::string description = description;

	}
};

class VehicleList
{
public:
	size_t Capacity;


private:
	VehicleList(size_t Capacity)
	{


	}
};



int main()
{

	int numberOfVehicles;
	cout << "Enter vehicles: ";
	cin >> numberOfVehicles;

	

	for (int i = 0; i < numberOfVehicles; i++)
	{
		
	}
	


	return 0;
}