#include "Garage.h"
#include <new>
#include <stdexcept>
#include <cassert>

Garage::Garage(std::size_t size)
{
	this->capacity = size;
	this->availableSpots = size;
	this->storedVehiclesCount = 0;
	this->vehicleData = new (std::nothrow) Vehicle * [1];
	if (vehicleData == nullptr)
		throw std::exception("Could not allocate enough memory for the garage!");
}

Garage::Garage(const Garage& otherGarage)
{
	this->capacity = otherGarage.capacity;
	this->availableSpots = otherGarage.availableSpots;
	this->storedVehiclesCount = otherGarage.storedVehiclesCount;
	this->vehicleData = otherGarage.vehicleData;
}

Garage::~Garage()
{
	this->capacity = 0;
	this->availableSpots = 0;
	this->storedVehiclesCount = 0;
	delete[] this->vehicleData;
}

//In insertion: 1) Check garage capacity and storedVehicles
//              2)No vehicles with same registrationNumber
void Garage::insert(Vehicle& v)
{
	bool alreadyExists = false; //Check if the car is already in the garage
	if (this->storedVehiclesCount != 0) {
		MyString vRegistration = MyString(v.registration());

		for (int i = 0; i < storedVehiclesCount; i++)
		{
			MyString currCarRegistration = MyString(this->vehicleData[i]->registration());
			bool carsHaveSameRegistration = (currCarRegistration == vRegistration);
			if (carsHaveSameRegistration)
				alreadyExists = true;
		}
	}

	if (alreadyExists == false) {

		size_t spaceNeeded = v.space();
		Vehicle myV = Vehicle(v.registration(), v.description(), v.space());
		Vehicle* p = &myV;

		int spotsLeft = this->availableSpots - spaceNeeded; //Check if there is enough space in the garage
		//Vehicle* p = &v;

		if (spotsLeft >= 0 && (storedVehiclesCount + 1 <= this->capacity)) {
			Vehicle** newVehicleData = new (std::nothrow) Vehicle * [storedVehiclesCount + 1];

			if (newVehicleData == nullptr) //Throw an exception if there is not enough memory
				throw std::exception("Not enough space to park in the garage!");

			for (size_t i = 0; i < storedVehiclesCount; i++) //Copy the existing data
				newVehicleData[i] = this->vehicleData[i];

			newVehicleData[storedVehiclesCount] = p; //Adding the new vehicle

			delete[] this->vehicleData;
			this->vehicleData = newVehicleData;
			this->storedVehiclesCount++;
			this->availableSpots -= spaceNeeded;
		}
		else
			throw std::exception("Not enough space to park in the garage!");
	}
	else
		throw std::exception("There is already a car with this registration number in the garage");
}

void Garage::erase(const char* registration)
{
	int pos = -1;
	MyString searchedRegistration = MyString(registration);
	for (int i = 0; i < this->storedVehiclesCount; i++) {
		MyString currCarRegistration = MyString(this->vehicleData[i]->registration());
		if (searchedRegistration == currCarRegistration) {
			pos = i;
			break;
		}
	}

	if (pos != -1) {
		int spaceFreed = this->vehicleData[pos]->space();

		Vehicle** newVehicleData = new (std::nothrow) Vehicle * [storedVehiclesCount - 1];

		if (newVehicleData != nullptr) {
			for (size_t i = 0; i < pos; i++) //Copy the data until spot on position 'pos'
				newVehicleData[i] = this->vehicleData[i];

			for (int i = pos; i < storedVehiclesCount; i++) //Reordering the cars
				newVehicleData[i] == this->vehicleData[i + 1];

			delete[] this->vehicleData;
			this->vehicleData = newVehicleData;
			this->availableSpots += spaceFreed;
			this->storedVehiclesCount--;
		}
	}
}

const Vehicle& Garage::at(std::size_t pos) const
{
	if (this->storedVehiclesCount == 0 || pos < 0 || pos >= this->storedVehiclesCount)
		throw std::out_of_range("Element our of range!");

	const Vehicle& p = *(this->vehicleData[pos]);
	return p;
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
	assert(pos >= 0 && pos < this->storedVehiclesCount); //Assert that position os valid
	const Vehicle& p = *(this->vehicleData[pos]);
	return p;
}

bool Garage::empty() const
{
	return this->storedVehiclesCount == 0;
}

std::size_t Garage::size() const
{
	return this->storedVehiclesCount;
}

void Garage::clear()
{
	//delete[] this->vehicleData;
	//this->vehicleData = new (std::nothrow) Vehicle * [1];

	for (int i = 0; i < storedVehiclesCount; i++)
		this->vehicleData[i] = nullptr;
	this->availableSpots = this->capacity;
	this->storedVehiclesCount = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
	Vehicle* p = nullptr;
	MyString searchedReg = MyString(registration);
	for (int i = 0; i < this->storedVehiclesCount; i++) {
		MyString currCarRegistration = MyString(this->vehicleData[i]->registration());
		if (searchedReg == currCarRegistration)
			p = this->vehicleData[i];
	}
	return p;
}
