#include"Person_Header.h"


Person::Person(const std::string name, const unsigned int id) {

	this->name = name;
	this->id = id;
	

}

void Person::assign_vehicle(Vehicle* car) {
	vehicles.push_back(car);
	car->set_owner(this->get_name());
}

void Person::remove_vehicle(Vehicle* car) {
	std::vector<Vehicle*>::iterator index = std::find(vehicles.begin(), vehicles.end(),car);
	if (index != vehicles.end()) {
		vehicles.erase(index);
		car->set_owner("");
	}
	else {
		throw std::exception ("Car does not belong to this person!");
	}
	
}

std::string Person::get_name() const {
	return name;
}

unsigned int Person::get_id() const {
	return id;
}

unsigned int Person::number_of_cars() const
{
	return vehicles.size();
}

bool Person::operator==(const Person& other) const
{
	if (this->get_id() == other.get_id()) {
		return true;
	}
	return false;
}
std::ostream& operator<<(std::ostream& out, const Person& person)
{
	out << "-----------------------\n";
	out << "Name: "        << person.name << "\n";
	out << "ID: " << person.id << "\n";
	out << "# of vehicles: " << person.vehicles.size() << "\n";
	for (unsigned i = 0; i < person.vehicles.size(); i++) {
		out << "Vehicle # " << i + 1 << " [" << person.vehicles[i]->registration() <<"]" << "\n";
		out << "Description: " << person.vehicles[i]->descr() << "\n";
	}
	
	out << "-----------------------\n";

	return out;
}

