#include"Person.h"

Person::Person(const std::string name, const unsigned int id) : personVehicles() {
    this->personName = name;
    this->personId = id;
}

Person::~Person() {
    personVehicles.clear();
    personVehicles.shrink_to_fit();
}

Vehicle* Person::AddVehicleToPersonCollection(Vehicle* vehicle) {
    this->personVehicles.push_back(vehicle);
    vehicle->SetOwner(this);
    
    return vehicle;
}

Vehicle* Person::RemoveVehicleFromPersonCollection(Vehicle* vehicle) {
    for (size_t iterator = 0; iterator < this->personVehicles.size(); iterator++)
    {
        if(*this->personVehicles[iterator] == *vehicle) {
            this->personVehicles.erase(this->personVehicles.begin() + iterator);
            vehicle->RemoveOwner();

            return vehicle;
        }
    }

    std::cout << "No such vehicle was found in this person's vehicle collection!" << std::endl;

    return nullptr;
}

bool Person::IsOwner() {
    return this->personVehicles.size() > 0;
}

bool Person::operator ==(const Person& other) const {
    // PersonId check is enough because Id is a unique value
    return this->personId == other.personId;
}

std::string Person::ToString() {
    return std::to_string(this->personId) + " " + this->personName;
}
