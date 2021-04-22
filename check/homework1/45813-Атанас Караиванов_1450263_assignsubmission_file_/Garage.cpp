#include "Garage.hpp"

Garage::Garage(size_t size) {
	this->capacity = size;
	this->sizeOfVehicles = 0;
	this->numOfVehicles = 0;
	this->vehicles = new Vehicle * [size];

	for (size_t i = 0; i < size; i++) {
		this->vehicles[i] = nullptr;
	}
}

Garage& Garage::operator=(const Garage& other) {
	if (this != &other) {
		clear();
		delete[] vehicles;

		copyFrom(other);
	}

	return *this;
}

void Garage::copyFrom(const Garage& other) {
	this->capacity = other.capacity;
	this->sizeOfVehicles = other.sizeOfVehicles;
	this->numOfVehicles = other.numOfVehicles;
	this->vehicles = new Vehicle * [this->capacity];

	for (size_t i = 0; i < this->numOfVehicles; i++) {
		this->vehicles[i] = other.vehicles[i];
	}
}

Garage::Garage(const Garage& other) {
	copyFrom(other);
}

void Garage::insert(Vehicle& v) {
	this->sizeOfVehicles += v.space();

	if (this->sizeOfVehicles > this->capacity) {
		this->sizeOfVehicles -= v.space();
		throw exception("Not enough space!");
	}

	for (size_t i = 0; i < this->numOfVehicles; i++) {
		if (strcmp(v.registration(), this->vehicles[i]->registration()) == 0) {
			this->sizeOfVehicles -= v.space();
			throw exception("That car is already in the garage!");
		}
	}

	vehicles[this->numOfVehicles] = new Vehicle(v);
	this->numOfVehicles++;
}

void Garage::erase(const char* registration) {
	if (strcmp(registration, this->vehicles[numOfVehicles - 1]->registration()) == 0) {
		this->sizeOfVehicles -= this->vehicles[numOfVehicles - 1]->space();

		delete this->vehicles[numOfVehicles - 1];
		this->vehicles[numOfVehicles - 1] = nullptr;

		this->numOfVehicles--;
		return;
	}

	for (size_t i = 0; i < this->numOfVehicles - 1; i++) {
		if (strcmp(registration, this->vehicles[i]->registration()) == 0) {
			this->sizeOfVehicles -= this->vehicles[i]->space();

			this->vehicles[i] = new Vehicle(this->vehicles[numOfVehicles - 1]->registration(),
				this->vehicles[numOfVehicles - 1]->description(), this->vehicles[numOfVehicles - 1]->space());

			delete this->vehicles[numOfVehicles - 1];
			this->vehicles[numOfVehicles - 1] = nullptr;

			this->numOfVehicles--;
			return;
		}
	}
}

const Vehicle& Garage::at(size_t pos) const {
	if (pos >= numOfVehicles || pos < 0) {
		throw out_of_range("Position is out of range!");
	}

	return *this->vehicles[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const {
	return at(pos);
}

bool Garage::empty() const {
	if (this->numOfVehicles == 0 && this->sizeOfVehicles == 0) {
		return true;
	}
	else {
		return false;
	}
}

size_t Garage::size() const {
	return this->numOfVehicles;
}

void Garage::clear() {
	for (size_t i = 0; i < this->numOfVehicles; i++) {
		delete this->vehicles[i];
		this->vehicles[i] = nullptr;
	}
	this->numOfVehicles = 0;
	this->sizeOfVehicles = 0;
}

const Vehicle* Garage::find(const char* registration) const {
	for (size_t i = 0; i < this->numOfVehicles; i++) {
		if (strcmp(registration, this->vehicles[i]->registration()) == 0) {
			return this->vehicles[i];
		}
	}

	return nullptr;
}

Garage::~Garage() {
	clear();

	delete[] vehicles;
}