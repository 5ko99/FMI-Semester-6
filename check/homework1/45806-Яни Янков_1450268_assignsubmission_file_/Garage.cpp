#include "Garage.hpp"

Garage::Garage(size_t size)
{
	this->capacity = size;
	this->curr_capacity = size;
	this->vehicles=new Vehicle*[this->capacity];
	for (unsigned i = 0; i < size; i++)
	{
		vehicles[i] = nullptr;
	}
	this->num_vehicles = 0;
}

Garage::Garage(const Garage& copy) noexcept
{
	this->capacity = copy.capacity;
	this->curr_capacity = copy.curr_capacity;
	this->num_vehicles = copy.num_vehicles;
	this->vehicles = new Vehicle * [this->capacity];
	for (unsigned i = 0; i <this->capacity ; i++)
	{
		this->vehicles[i]=copy.vehicles[i];
	}
}

Garage& Garage::operator=(const Garage& copy) noexcept
{
	this->capacity = copy.capacity;
	this->curr_capacity = copy.curr_capacity;
	this->num_vehicles = copy.num_vehicles;
	this->vehicles = new Vehicle * [this->capacity];
	for (unsigned i = 0; i < this->capacity; i++)
	{
		this->vehicles[i] = copy.vehicles[i];
	}
	return *this;
}

void Garage::insert(Vehicle& v)
{
	if (this->curr_capacity < v.space())
	{
		throw std::out_of_range("There is no more space for this car!");
	}
	/*for (unsigned i = 0; i < this->num_vehicles; i++)
	{
		if (strcmp(vehicles[i]->registration(),v.registration())==0)
		{
			throw std::invalid_argument("This car has already been added!");
		}
	}*/
	if (this->find(v.registration()) != nullptr)
	{
		throw std::invalid_argument("This car has already been added!");
	}
	this->vehicles[this->num_vehicles] = &v;
	this->num_vehicles++;
	this->curr_capacity= this->curr_capacity - v.space();
}

void Garage::erase(const char* registration)
{
	for (unsigned i = 0; i < this->num_vehicles; i++)
	{
		if (strcmp(this->vehicles[i]->registration(), registration) == 0)
		{
			swap(this->vehicles[i], this->vehicles[this->num_vehicles - 1]);
			this->curr_capacity = this->curr_capacity + this->vehicles[this->num_vehicles - 1]->space();
			this->vehicles[this->num_vehicles - 1] = nullptr;
			this->num_vehicles--;
		}
	}
}

const Vehicle& Garage::at(std::size_t pos) const
{
	if (this->num_vehicles < pos)
	{
		throw std::out_of_range("Position is out of range!");
	}
	return *this->vehicles[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
	if (this->num_vehicles < pos)
	{
		throw std::out_of_range("Position is out of range!");
	}
	return *this->vehicles[pos];
}

bool Garage::empty() const
{
	if (this->num_vehicles == 0)
	{
		return true;
	}
	return false;
}

size_t Garage ::size() const
{
	return this->num_vehicles;
}

void Garage::clear()
{
	this->curr_capacity = 0;
	this->num_vehicles = 0;
	for (unsigned i = 0; i < this->capacity; i++)
	{
		this->vehicles[i] = nullptr;
	}
}

const Vehicle* Garage::find(const char* registration) const
{
	for (unsigned i = 0; i < this->num_vehicles; i++)
	{
		if (strcmp(this->vehicles[i]->registration(), registration) == 0)
		{
			return this->vehicles[i];
		}
	}
	return nullptr;
}

Garage::~Garage()
{
		delete[] this->vehicles;
}