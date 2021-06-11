#include <string> 
#include <iostream>
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
Person::Person()
{
	cin >> name;
	cin >> id;
	cin >> veh;
}
void Person::printP()
{
	cout << name << " " << id << " " << veh;

}
