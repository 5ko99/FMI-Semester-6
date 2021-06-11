#include "Vehicle.h"
#include "Person.h"


Vehicle::Vehicle(std::string& reg_str, std::string& desc_str) : UniRegNum(reg_str) ,Desc(desc_str), isTaken(false), Owner(nullptr) {}




Vehicle::Vehicle(const Vehicle& other) : UniRegNum(other.UniRegNum), Desc(other.Desc), isTaken(other.isTaken)
{
	this->Owner = other.Owner;
}



void Vehicle::SetOwner(Person& per)
{

	if (this->Owner != nullptr) { throw std::runtime_error("This vehicle already has an owner"); }
	if (this->Owner == &per) { throw std::runtime_error("This person is already owning this vehicle!"); }

	//stores the memory adress of the Person object
	this->Owner = &per;
	this->isTaken = true;
	
	this->Owner->AddVeh(*this);


}

void Vehicle::DisOwn()
{

	this->Owner->RemoveCar(*this);
	//since there isnt any owner the pointer Owner points to nullptr
	this->Owner = nullptr;

	this->isTaken = false;


	

}

bool Vehicle::Is_Taken()
{
	return this->isTaken;
}

std::string& Vehicle::GetUniRegNum()
{
	return this->UniRegNum.GetRegNum();
}

Person& Vehicle::GetOwner()
{
	return *Owner;
}

std::ostream& operator<<(std::ostream& out, const Vehicle& veh)
{
	    //Example for Output: AX1234ZX/"Very fast car"
	    //Printin all the registrated Vehicles in the database without their owners!
	    // if the user wants to see vehicle's owner he/she has to use the command  "SHOW  <id>"
	    out << veh.UniRegNum << "/" << veh.Desc << std::endl;

		return out;
}
std::ofstream& operator<<(std::ofstream& out, const Vehicle& veh)
{
	// "-" means thah the vehicle has its owner
	if (veh.isTaken) {
		out << "-" << veh.UniRegNum << "|" << veh.Desc <<std::endl;
	}
	// "p" means the user doesn't have owner
	else {
		out << "p" << veh.UniRegNum << "|" << veh.Desc << std::endl;;
	}

	return out;

}
bool Vehicle::operator==(const Vehicle& veh) {
	if (this->UniRegNum == veh.UniRegNum) return true;
	return false;
}

