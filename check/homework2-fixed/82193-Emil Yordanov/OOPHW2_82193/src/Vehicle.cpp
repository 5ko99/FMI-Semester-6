#include"Vehicle.h"

// The Regular expression is '[A-Z]{1,2}[0-9]{4}[A-Z]{2}' (AB1234CD is valid)
bool registrationIsValid(std::string registration) {
    std::regex registrationRegex("[A-Z]{1,2}[0-9]{4}[A-Z]{2}");

    return std::regex_match(registration, registrationRegex);
}

Vehicle::Vehicle(const std::string registration, const std::string description, Person* owner) : vehicleOwner(owner){
    if(!registrationIsValid(registration)) {
        throw std::invalid_argument("The registration does not match the requirements!");
    }

    this->vehicleRegistration = registration;
    this->vehicleDescription = description;
}

Vehicle::Vehicle(const std::string registration, const std::string description) : vehicleOwner(nullptr) {
    if(!registrationIsValid(registration)) {
        throw std::invalid_argument("The registration does not match the requirements!");
    }

    this->vehicleRegistration = registration;
    this->vehicleDescription = description;
}

Vehicle::~Vehicle() {
    this->vehicleOwner = nullptr;
}

Person* Vehicle::SetOwner(Person* newOwner) {
    if(&this->vehicleOwner != nullptr) {
        std::cout << "This vehicle already has an owner!" << std::endl;
        
        return nullptr;
    }
    else {
        this->vehicleOwner = newOwner;

        return newOwner;
    }
}

Person* Vehicle::RemoveOwner() {
    if(&this->vehicleOwner != nullptr) {
        std::cout << "This vehicle already has no owner!" << std::endl;

        return nullptr;
    }
    else {
        this->vehicleOwner = nullptr;

        // Actually returns nullptr too because we set it to null above ;)
        return this->vehicleOwner;
    }
}

std::string Vehicle::ToString() {
    return this->vehicleRegistration + " (" + this->vehicleOwner->ToString() + ") " + this->vehicleDescription;
}

bool Vehicle::operator ==(const Vehicle& other) const {
    // VehicleRegistration check is enough because Registration is a unique value
    return this->vehicleRegistration == other.vehicleRegistration;
}
