#include "pch.h"
#include <iostream>
#include <fstream> 
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
int main()
{
	ofstream out("base.txt", ios::out);

	Person *person=new Person[];
	Vehicle *v=new Vehicle[];


	try {
		char command[32];
		do {
			cin >> command;
			if (!strcmp(command, "VEHICLE")) {
				*v = Vehicle();
				out << v;
			}
			else if (!strcmp(command, "PERSON")) {
				*person = Person();
				out << person;
			}
			else if (!strcmp(command, "ACQUIRE")) {

			}
			else if (!strcmp(command, "RELEASE")) {

			}
			else if (!strcmp(command, "REMOVE")) {

			}
			else if (!strcmp(command, "SAVE")) {

			}
			else if (!strcmp(command, "SHOW")) {
				if (!strcmp(command, "SHOW VEHICLES"))
				{
					printV();
				}
				else if (!strcmp(command, "SHOW PERSON"))
				{
					printP();
				}
				else
				{
					cout << "Wrong command!";
				}
			}
		} while (strcmp(command, "EXIT") != 0);
	}

}


