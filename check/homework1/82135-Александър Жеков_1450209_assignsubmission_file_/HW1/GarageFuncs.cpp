#include "Garage.h"

// Constructors and destructor
Garage::Garage(std::size_t size) {
	numSpaces = size;
	occupiedSpaces = 0;
	numVehicles = 0;
	Vehicles = new Vehicle * [size];

	for (size_t i = 0; i < size; ++i) {
		Vehicles[i] = nullptr;
	}
}

Garage::Garage(const Garage* grg) {
	numSpaces = grg->numSpaces;
	occupiedSpaces = grg->occupiedSpaces;
	numVehicles = grg->numVehicles;
	Vehicles = new Vehicle * [numSpaces];

	for (size_t i = 0; i < grg->numVehicles; ++i) {
		Vehicle* tempVeh = new Vehicle( (grg->Vehicles[i])->registration(), 
										(grg->Vehicles[i])->description(), 
										(grg->Vehicles[i])->space());
		Vehicles[i] = tempVeh;
	}
}

Garage::~Garage() {
	delete Vehicles;
}

// Interface functions
void Garage::insert(Vehicle& v) {
	bool cancelInsert = false;

	if (this->isFull()) {
		throw "Garage full!";
		cancelInsert = true;
	}
	else if (occupiedSpaces + v.space() > numSpaces) {
		throw "Not enough space for vehicle!";
		cancelInsert = true;
	}

	for (size_t i = 0; i < numVehicles; ++i) {
		if (strcmp(v.registration(), Vehicles[i]->registration()) == 0) {
			throw "Car with same registration is in the garage!";
			cancelInsert = true;
		}
	}

	if (!cancelInsert) {
		Vehicles[numVehicles] = &v;
		occupiedSpaces += v.space();
		++numVehicles;
	}
}

void Garage::erase(const char* registration) {
	bool vehFound = false;

	for (size_t i = 0; i < numVehicles; ++i) {
		if (!strcmp(registration, Vehicles[i]->registration())) {
			if (numVehicles - 1 == i) {
				vehFound = true;
				occupiedSpaces -= Vehicles[i]->space();
				delete Vehicles[i];
				Vehicles[i] = nullptr;
				--numVehicles;
				break;
			}
			else {
				vehFound = true;
				occupiedSpaces -= Vehicles[i]->space();
				delete Vehicles[i];
				Vehicles[i] = Vehicles[numVehicles - 1];
				Vehicles[numVehicles - 1] = nullptr;
				--numVehicles;
				break;
			}
		}
	}

	if (!vehFound) {
		throw "No vehicle with such registration!";
	}
}

const Vehicle& Garage::at(std::size_t pos) const {
	return *(Vehicles[pos]);
}

bool Garage::empty() const {
	return (Vehicles == nullptr && occupiedSpaces == 0);
}

bool Garage::isFull() const {
	return (occupiedSpaces == numSpaces);
}

std::size_t Garage::size() const {
	return numVehicles;
}

void Garage::clear() {
	if (Vehicles != nullptr) {
		delete Vehicles;
	}
	Vehicles = nullptr;
	occupiedSpaces = 0;
	numVehicles = 0;
	numSpaces = 1;
}

const Vehicle* Garage::find(const char* registration) const {
	for (size_t i = 0; i < numVehicles; ++i) {
		if (!strcmp(Vehicles[i]->registration() , registration)) {
			return Vehicles[i];
		}
	}
	return nullptr;
}


// Operators
const Vehicle& Garage::operator[](std::size_t pos) const {
	return *(Vehicles[pos]);
}

Garage& Garage::operator=(const Garage& othergrg) {
	numSpaces = othergrg.numSpaces;
	occupiedSpaces = othergrg.occupiedSpaces;
	numVehicles = othergrg.numVehicles;
	Vehicles = new Vehicle * [numSpaces];

	for (size_t i = 0; i < othergrg.numVehicles; ++i) {
		Vehicle* tempVeh = new Vehicle(*(othergrg.Vehicles[i]));
		Vehicles[i] = tempVeh;
	}
	return *this;
}
