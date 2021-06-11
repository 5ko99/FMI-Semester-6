#include "Person.h"
#include "Vehicle.h"



Person::Person(std::string Name_str, unsigned int UniNum)
{

	this->Name = Name_str;
	this->UniNum = UniNum;

}

Person::Person(const Person& other) : Name(other.Name), UniNum(other.UniNum) {

	this->OwnVehs = other.OwnVehs;
}

void Person::AddVeh(Vehicle& veh)
{
	OwnVehs.push_back(&veh);
}

void Person::RemoveCar(Vehicle& veh)
{
	if (this->OwnVehs.size() == 0) {
		throw std::runtime_error("There is nothing to remove!");
	}

	for (std::size_t i = 0; i < this->OwnVehs.size(); i++) {

		if (veh == *OwnVehs.at(i)) {
			this->OwnVehs.erase(this->OwnVehs.begin() + i);
			break;
		}


	}
}

std::string& Person::GetName()
{
	return this->Name;
}

unsigned int& Person::GetUniNum()  {
	return this->UniNum;
}

std::vector<Vehicle*> Person::GetOwnVehs() {
	return OwnVehs;
}

std::ostream& operator<<(std::ostream& out, const Person& per)
{
	//Example for Output: Spider Man/12392
	//Printin all the registrated Person in the database without their owned cars!
	// if the user wants to see Person's vehicles he/she has to use the command  "SHOW  <id>"
	out << per.Name << "/" << per.UniNum << std::endl;
	return out;
}

std::ofstream& operator<<(std::ofstream& out, const Person& per)
{
	// outputs those who dont own a car, "p" means person
	if (per.OwnVehs.size() == 0) {
		out << "p" << per.Name << "|" << per.UniNum   << std::endl;
	}

	// add those who do own cars, "p" means person
	if (per.OwnVehs.size() > 0) {
		out << "p" << per.Name << "|" << per.UniNum <<  std::endl;
		for (std::size_t i = 0; i < per.OwnVehs.size(); i++) {
			out <<	per.OwnVehs[i];
		}
	}

	return out;
}
