#include "Garage.h"

Garage::Garage(size_t size) : takenSpace(0), capacity(size), numOfVehicles(0)
{
	allVehicles = new (nothrow) Vehicle*[capacity];
}

Garage::Garage() : allVehicles(nullptr), capacity(0), takenSpace(0), numOfVehicles(0)
{
}

Garage::Garage(const Garage& other)
{
	allVehicles = new (nothrow) Vehicle * [other.numOfVehicles];
	for (int i = 0; i < other.numOfVehicles; i++)
	{
		allVehicles[i] = new Vehicle(other.allVehicles[i]->registration(), other.allVehicles[i]->description(), other.allVehicles[i]->space());
	}
	capacity = other.capacity;
	takenSpace = other.takenSpace;
	numOfVehicles = other.numOfVehicles;
}

Garage& Garage::operator=(const Garage& other)
{
	if (this != &other)
	{
		clear();
		allVehicles = new (nothrow) Vehicle * [other.numOfVehicles];
		for (int i = 0; i < other.numOfVehicles; i++)
		{
			allVehicles[i] = new Vehicle(other.allVehicles[i]->registration(), other.allVehicles[i]->description(), other.allVehicles[i]->space());
		}
		capacity = other.capacity;
		takenSpace = other.takenSpace;
		numOfVehicles = other.numOfVehicles;
	}
	return *this;
}

Garage::~Garage()
{
	clear();
}

void Garage::clear()
{
	for (int i = 0; i < numOfVehicles; i++)
	{
		delete allVehicles[i];
	}
	delete[] allVehicles;
	allVehicles = nullptr;
	capacity = 0;
}

void Garage::insert(Vehicle& newV)
{
	bool checkreg = false;
	for (int i = 0; i < takenSpace; i++)
	{
		if (newV.registration() == allVehicles[i]->registration())
		{
			checkreg = true;
		}
	}

	if (takenSpace + newV.space() <= capacity && !checkreg)
	{
		Vehicle** newVehicles = new Vehicle*[numOfVehicles + 1];
		for (int i = 0; i < numOfVehicles; i++)
		{
			newVehicles[i] = allVehicles[i];
		}
		newVehicles[numOfVehicles] = new Vehicle(newV);
		takenSpace += newV.space();
		numOfVehicles++;
		delete[] allVehicles;
		allVehicles = newVehicles;

	}
	else
	{
		if (checkreg)
		{
			throw invalid_argument(" reg ");
		}
		else
		{
			throw invalid_argument("no space");
		}
	}
}

void Garage::erase(const char* registration)
{
	for (int i = 0; i < numOfVehicles; i++)
	{
		if (strcmp(allVehicles[i]->registration(), registration) == 0)
		{
			swap(allVehicles[i], allVehicles[numOfVehicles - 1]);
			numOfVehicles--;
			return;
		}
	}
}

const Vehicle& Garage::at(size_t pos) const
{
	return *allVehicles[pos];
}

const Vehicle& Garage::operator[](size_t pos) const
{
	return *allVehicles[pos];
}

bool Garage::empty() const
{
	return numOfVehicles == 0;
}

size_t Garage::size() const
{
	return this->numOfVehicles;
}

const Vehicle* Garage::find(const char* registration) const
{
	for (int i = 0; i < numOfVehicles; i++)
	{
		if (strcmp(allVehicles[i]->registration(), registration) == 0)
		{
			return allVehicles[i];
		}
	}
	return nullptr;
}

