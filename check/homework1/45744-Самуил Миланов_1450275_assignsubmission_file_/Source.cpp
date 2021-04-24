#pragma once

#include "MyString.cpp"
#include "Garage.cpp"
#include "Vehicle.cpp"
#include <iostream>
#include <cstring>


void AddCar(Garage& Poe)
{
	std::cout << "Registration Number:";
	char* RegN = new char[20];
	std::cin >> RegN;
	std::cout << "Description of the Vehicle:";
	char* Descr = new char[20];
	std::cin >> Descr;
	std::cout << "How much space does the car take:";
	int Space;
	std::cin >> Space;
	Vehicle a(RegN, Descr, Space);
	Poe.insert(a);
	
}

void RemoveCar(Garage& Poe)
{
	std::cout << "Registration Number:";
	char* RegN = new char[20];
	std::cin >> RegN;
	Poe.erase(RegN);
}

void Print(Garage &Poe)
{
	size_t Size = Poe.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (&Poe.at(i + 1) != nullptr)
		{
			std::cout << "Vehicle Number " << i + 1 << std::endl;
			std::cout << "Registration Number :" << Poe.at(i + 1).registration() << std::endl;
			std::cout << "Description :" << Poe.at(i + 1).description() << std::endl;
			std::cout << "Space it takes: " << Poe.at(i + 1).space() << std::endl;
		}
	}
}

void Action(char* command, Garage &Poe)
{

	if (strcmp(command, "Add") == 0)
	{
		AddCar(Poe);
	}
	else if (strcmp(command, "Remove") == 0)
	{
	    RemoveCar(Poe);
	}
	else if (strcmp(command, "Print") == 0)
	{
		Print(Poe);
	}
	std::cout << "Next command?";
	std::cin >> command;
	if (strcmp(command, "Quit") != 0)
	{
		Action(command, Poe);
		return;
	}
	
	return;
}

int main()
{
	int n;
	std::cout << "How much space is needed for the garage?";
	std::cin >> n;
	Garage Poe(n);
	std::cout << "Possible commands: "<< std::endl;
	std::cout << "Add" << std::endl;
	std::cout << "Remove" << std::endl;
	std::cout << "Print" << std::endl;
	std::cout << "Quit" << std::endl;
	char* command = new char[20];
	std::cin >> command;
	/*Garage poe(50);
	Vehicle p("bp 1234", "kock", 4);
	poe.insert(p);
	std:: cout << poe.find("bp 1234")->registration();
	std::cout << poe.operator[](1).description();*/




















	Action(command, Poe);
	/*
	a.clear();
	std::cout << a.empty() << std::endl;
	char* command2 = new char[20];
	std::cin >> command2;
	MyString b(command2);
	b.push_back('c');
	std::cout << b.c_str() << std::endl;

	b = b.operator+=('c');
	std::cout << b.c_str() << std::endl;
	MyString c("Poec");
	
	std::cout << b.c_str();
	std:: cout<< b.operator==(c);*/

	return 0;
}

