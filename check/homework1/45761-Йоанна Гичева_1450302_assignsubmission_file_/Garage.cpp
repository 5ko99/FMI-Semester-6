#include "Garage.hpp"
#include "Vehicle.hpp"
#include <iostream>

bool equalRegistrationNumbers(const char* a, const char* b);


Garage::Garage(std::size_t size) {
	this->initialCapacity = size;
	this->capacity = size;
	this->vehicles = new Vehicle * [size];
	this->counter = 0;
}

Garage::~Garage() {
	delete[] this->vehicles;
}

Garage::Garage(const Garage& other)
	: Garage(other.initialCapacity)
{}

void Garage::insert(Vehicle& v) {
	if (v.space() > this->capacity) {
		throw std::out_of_range("There is not enough space! Please, try to add another vehicle!");
	}
	else if (this->find(v.registration()) != nullptr) {
		throw std::out_of_range("There is already such vehicle!");
	}

	vehicles[this->counter] = &v;
	this->counter++;
	this->capacity -= v.space();
}

const Vehicle* Garage::find(const char* registration) const {
	for (int i = 0; i < this->counter; i++) {
		Vehicle vehicle = *this->vehicles[i];
		if (equalRegistrationNumbers(vehicle.registration(), registration)) {
			return vehicles[i];
		}
	}

	return nullptr;
}

void Garage::erase(const char* registration) {
	for (int i = 0; i < this->counter; i++) {
		if (equalRegistrationNumbers(this->vehicles[i]->registration(), registration)) {
			this->vehicles[i] = this->vehicles[this->counter - 1];
			this->vehicles[this->counter - 1] = nullptr;
			this->counter = this->counter --;
			break;
		}
	}
}




const Vehicle& Garage::at(std::size_t pos) const {
	if (pos < 0 || pos >= this->initialCapacity) {
		throw std::out_of_range("There is no such position in array!");
	}

	return *this->vehicles[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const {
	return *this->vehicles[pos];
}

bool Garage::empty() const {
	if (this->counter == 0) {
		return true;
	}
	return false;
}

std::size_t Garage::size() const {
	return this->counter;
}

void Garage::clear() {
	for (int i = 0; i < this->counter; i++) {
		this->vehicles[i] =  nullptr;
	}
	this->capacity = this->initialCapacity;
	this->counter = 0;
}

void Garage::print() {
	std::cout << "YOUR GARAGE CHARACTERISTICS" << std::endl;
	std::cout << "Garage capacity: " << this->initialCapacity << std::endl;
	unsigned int available = this->initialCapacity - this->capacity;
	std::cout << "Garage available spaces: " << available << std::endl;
	std::size_t size = this->size();

	if (size > 0) {
		std::cout << "List of vehicles: " << std::endl;

		for (int i = 0; i < size; i++) {
			std::cout << "#Vehicle N" << i + 1 << std::endl;
			this->vehicles[i]->print();
		}
	}

	std::cout << "###################################\n";

}

bool equalRegistrationNumbers(const char* a, const char* b) {
	int la = strlen(a);
	int lb = strlen(b);
	if (la != lb) return false;
	for (lb = 0; lb < la; lb++)
	{
		if (a[lb] != b[lb]) {
			return false;
		}
	}
	return true;

}