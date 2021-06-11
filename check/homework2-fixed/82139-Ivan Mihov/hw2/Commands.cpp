

#include "Commands.h"
# include <stdexcept>
# include <fstream>
# include <iostream>
void Commands::newVehicle(const Registration& reg, const std::string& str) {
	try {
		Vehicle v(reg, str);
		for (std::size_t i = 0; i < this->vehicles.size(); i++) {
			if (vehicles[i].getRegistration() == v.getRegistration()) {
				throw std::invalid_argument("Can not have two Vehicles with the same registration");
			}
		}
		this->vehicles.push_back(v);
	}
	catch (...) {
		throw;
	}
	
}
void Commands::newPerson(const std::string& str, unsigned int id) {
	
	try {
		Person p(str, id);
		for (std::size_t i = 0; i < this->person.size(); i++) {
			if (this->person[i].getId() == p.getId()) {
				throw std::invalid_argument("Can not have two persons with the same Id");
			}
		}
		this->person.push_back(p);
	}
	catch (...) {
		throw;
	}
}
void Commands::Aquire(unsigned int id, const Registration& reg) {
	bool notAquired = true; // a bool flag that shows if a vehicle exist to be aquired
	std::size_t sizePeople = this->person.size();
	std::size_t sizeVehicles = this->vehicles.size();
	for (std::size_t i = 0; i < sizePeople; i++) {
		if (this->person[i].getId() == id) {
			for (std :: size_t j = 0; j < sizeVehicles; j++) {
				if (this->vehicles[j].getRegistration() == reg.getRegistration()) {
					notAquired=false;
					if (this->vehicles[j].isItOwned()) {
						this->vehicles[j].getOwner()->eraseAt(vehicles[j].getRegistration());
					}
					this->vehicles[j].setOwner(&person[i]);
					this->person[i].addVehicle(&vehicles[j]);
				}
			}
		}
	}
	if (notAquired)
		throw std::runtime_error("No such vehicle found ");
}
void Commands::Release(unsigned int id, const Registration& reg) {
	bool notReleased = true; // a bool flag that shows if a vehicle exist to be aquired
	std::size_t sizePeople = this->person.size();
	for (std::size_t i = 0; i < sizePeople; i++) {
		if (this->person[i].getId() == id) {
			notReleased = false;
			try {
				person[i].eraseAt(reg.getRegistration());
			}
			catch (...) {
				throw;
			}
			
		
			
		}

	}
	if (notReleased)
		throw std::runtime_error("No such person found ");
}
void Commands::remove(unsigned int id) {
	bool notRemoved = true;
	std::size_t personSize = this->person.size();
	for (std::size_t i = 0; i < personSize; i++) {
		if (this->person[i].getId() == id) {
			notRemoved = false;
			person[i].removeVehicles();
			std::swap(person[i], person[personSize - 1]);
			person.pop_back();
			break;
		}
	}
	if (notRemoved)
		throw std::runtime_error("No such person found");
}
void Commands::remove(const Registration& reg) {
	bool notRemoved = true;
	std::size_t size = this->vehicles.size();
	for (std::size_t i = 0; i < size; i++) {
		if (this->vehicles[i].getRegistration() == reg.getRegistration()) {
			notRemoved = false;
			if (this->vehicles[i].isItOwned()) {
				this->vehicles[i].getOwner()->eraseAt(vehicles[i].getRegistration());
				this->vehicles[i].eraseOwner();
				std::swap(vehicles[i], vehicles[size - 1]);
				vehicles.pop_back();
				break;
			}
			else {
				std::swap(vehicles[i], vehicles[size - 1]);
				vehicles.pop_back();
				break;
			}
		}
	}
	if (notRemoved) {
		throw std::runtime_error("No such vehicle found");
	}
}
void Commands::Save(const std::string& path)const {
	std::ofstream out;
	out.open(path);
	std::size_t sizeP = this->person.size();
	std::size_t sizeV = this->vehicles.size();
	for (std::size_t i = 0; i < sizeP; i++) {
		out << this->person[i].getName() << " " << person[i].getId() << " " << std::endl;

	}
	
	for (std::size_t j = 0; j < sizeV; j++) {
		
			out << this->vehicles[j].getRegistration() << " " << this->vehicles[j].getDescription() << std::endl;
		
	}
	out.close();
}
void Commands::display(const std::string& str)const {
	if (str == "PEOPLE") {
	std:: size_t size = this->person.size();
	for (std::size_t i = 0; i < size; i++) {
		std::cout << this->person[i].getName() << " " << person[i].getId() << "\n";
		std::size_t sizeO = person[i].vehicleCount();
		//prints persons and the vehicles assosiated with them 
		for (std::size_t t = 0; t < sizeO; t++) {
			std::cout << this->person[i].getVehicleAt(t)->getRegistration() << " " << this->person[i].getVehicleAt(t)->getDescription() << std::endl;
		}
	}
	}else if (str == "VEHICLES") {
		std::size_t size = this->vehicles.size();
		for (std::size_t i = 0; i < size; i++) {
			std::cout << this->vehicles[i].getRegistration()
				<< " " << vehicles[i].getDescription() << "\n";

		}
	}
	
}
void Commands::display(unsigned int id)const {
	bool notFound = true;
std:: size_t size = this->person.size();
	for (std::size_t i = 0; i < size; i++) {
		if (this->person[i].getId() == id) {
			notFound = false;
			std::size_t sizeCars = person[i].vehicleCount();
			for (std::size_t j = 0; j < sizeCars; j++) {
				std::cout << person[i].getVehicleAt(j)->getRegistration()
					<< " " << person[i].getVehicleAt(j)->getDescription() << std::endl;
			}
		}
	}
	if (notFound) {
		throw std::runtime_error("no such person found");
	}
}
Person Commands::getPersonAt(unsigned int i)const {
	if (i >= this->person.size())
		throw std::invalid_argument("Not enough elements");
	return this->person[i];
}
Vehicle Commands::getVehicleAt(unsigned int i)const {
	if (i >= this->vehicles.size())
		throw std::invalid_argument("Not enough elements");
	return this->vehicles[i];
}
