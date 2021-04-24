#include <iostream>
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"
#include<stdexcept>
using namespace std;

void Print(Garage* garage)
{
	for (size_t i = 0; i < garage->size(); i++)
		cout << garage->at(i).registration() << " " << garage->at(i).description() << endl;
}

int main()
{
	Vehicle car1("EN5549 A", "beatle sin", 1);
	Vehicle car2("EN5549 B", "beatle sin", 4);
	Vehicle car3("EN5549 C", "beatle sin", 3);
	Garage garage(10);
	garage.insert(car1);
	garage.insert(car3);
	garage.insert(car2);
	Print(&garage);
}