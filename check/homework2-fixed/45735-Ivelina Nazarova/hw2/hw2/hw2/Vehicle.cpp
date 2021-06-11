#include <string> 
#include "Registration.h"
#include "Person.h"
#include <iostream>
Vehicle::Vehicle()
{
	Registration();
	cin >> description;
	cin >> owner;
}
void Vehicle::printV()
{
	cout << registration<<" "<<description<<" "<<owner;

}
