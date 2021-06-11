#include "../Headers/VehicleManager.h"
#include "../Headers/Registration.h"
#include <stdexcept>

void VehicleManager::addVehicle(const string& registration,
    const string& description) {
	if(registrationAlreadyExist(registration))
		throw std::invalid_argument("Duplication of registration plates!");
	try{
		vehicles.push_back(new Vehicle(registration, description));
	}
	catch(std::bad_alloc e) {
		std::cerr<<"Memory error!"<<std::endl;
		throw e;
	}
}

Vehicle* VehicleManager::findVehicle(const Registration& registration) {
	for (size_t i = 0; i < vehicles.size(); i++) {
		if(vehicles[i]->getRegistration() == registration)
			return vehicles[i];
	}
	
	throw std::invalid_argument("There is no vehicle with that reg. plate");
}

Vehicle* VehicleManager::findVehicle(const string& registration) {
	return findVehicle(Registration(registration));
}

void VehicleManager::removeVehicle(const string& registration) {
	for (size_t i = 0; i < vehicles.size(); i++) {
		if(vehicles[i]->getRegistration() == registration) {
			vehicles.erase(vehicles.begin() + i);
			return;
		}
	}
	
	throw std::invalid_argument("There is no vehicle with that reg. plate");
}

Vehicle& VehicleManager::at(size_t pos) {
	return *(vehicles.at(pos));
}

const Vehicle& VehicleManager::at(size_t pos) const {
	return *(vehicles.at(pos));
}

Vehicle& VehicleManager::operator[](size_t pos) {
	return *(vehicles[pos]);
}

const Vehicle& VehicleManager::operator[](size_t pos) const {
	return *(vehicles[pos]);
}

size_t VehicleManager::getNumberOfVehicles() const {
	return vehicles.size();
}

bool VehicleManager::registrationAlreadyExist(const string& registration) const {
	for (size_t i = 0; i < getNumberOfVehicles(); i++) {
		if (vehicles[i]->getRegistration() == registration) {
			return true;
		}
	}

	return false;
}

void VehicleManager::showAllVehicles(std::ostream& out) {
	for (size_t i = 0; i < vehicles.size(); i++) {
		out<<*(vehicles[i])<<'\n';
	}
}

void VehicleManager::showAllVehiclesDetailed(std::ostream& out) {
	for (size_t i = 0; i < vehicles.size(); i++) {
		vehicles[i]->printDetailedInformation(out);
		out<<'\n';
	}
}
