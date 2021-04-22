#include "Header.h"


Garage::Garage(std::size_t size) {

	capacity = size;
	availabe_capacity = size;
	cars_inside = 0;
	vehicles = nullptr;
}

Garage::Garage(const Garage& other) {

	capacity = other.capacity;
	availabe_capacity = other.availabe_capacity;
	cars_inside = other.cars_inside;
	vehicles = new (std::nothrow) Vehicle * [cars_inside];
	if (vehicles != nullptr) {
		for (unsigned i = 0; i < cars_inside; i++) {
			vehicles[i] = other.vehicles[i];
		}
	}

}

Garage& Garage::operator=(const Garage& other) {

	if (this != &other) {
		capacity = other.capacity;
		availabe_capacity = other.availabe_capacity;
		cars_inside = other.cars_inside;
		delete[] vehicles;
		vehicles = new (std::nothrow) Vehicle * [cars_inside];
		if (vehicles != nullptr) {
			for (unsigned i = 0; i < cars_inside; i++) {
				vehicles[i] = other.vehicles[i];
			}
		}
	}

	return *this;
}

Garage::~Garage() {

	delete[] vehicles;

}

void Garage::insert(Vehicle& v) {

	if (availabe_capacity >= v.space()) { //checks if capacity is available
		bool flag = false;

		MyString reg_number(v.registration());
		for (unsigned i = 0; i < cars_inside; i++) {  //checks if the regplate is allready in garage

			MyString reg_to_compare(vehicles[i]->registration());
			if (reg_number == reg_to_compare) {
				flag = true;

				break;
			}
		}

		if (flag == false) {

			Vehicle** temp = new(std::nothrow) Vehicle * [cars_inside + 1];
			for (unsigned i = 0; i < cars_inside; i++) {
				temp[i] = vehicles[i];

			}

			temp[cars_inside] = &v;
			delete[] vehicles;
			vehicles = temp;
			cars_inside++;
			availabe_capacity -= v.space();
		}
	}
}

void Garage::erase(const char* registration) {

	MyString reg_number(registration);
	for (unsigned i = 0; i < cars_inside; i++) {
		MyString reg_to_compare(vehicles[i]->registration());

		if (reg_number == reg_to_compare) {
			unsigned match_index = i;

			Vehicle** temp = new(std::nothrow) Vehicle * [cars_inside - 1];
			if (temp != nullptr) {
				unsigned index = 0;
				for (unsigned p = 0; p < cars_inside; p++) {
					if (p != match_index) {
						temp[index] = vehicles[i];
						index++;
					}
				}

				cars_inside -= 1;
				availabe_capacity += vehicles[match_index]->space();

				delete[] vehicles;
				vehicles = temp;
			}
			break;
		}
	}
}

const Vehicle& Garage::at(std::size_t pos) const {
	try {
		if (pos <= cars_inside) {
			return *vehicles[pos];
		}
		else {
			throw std::out_of_range("Index is out of range!");
		}
	}
	catch (std::out_of_range& e) {

	}
	
}

const Vehicle& Garage::operator[](std::size_t pos) const {
#ifdef _DEBUG
	assert(pos<=cars_inside-1);
#endif

	return *vehicles[pos];

}

bool Garage::empty() const {
	if (cars_inside == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Garage::clear() {
	availabe_capacity = capacity;
	cars_inside = 0;
	delete[] vehicles;
	vehicles = nullptr;
}

std::size_t Garage::size() const {

	return cars_inside;
}


const Vehicle* Garage::find(const char* registration) const {
	MyString registr(registration);
	for (unsigned i = 0; i < cars_inside; i++) {
		MyString to_compare(vehicles[i]->registration());
			if (registr == to_compare) {
				return vehicles[i];
				break;
		}
	}
}


void Garage::printContent() const{

	std::cout << "Number of cars inside: " << this->size() << "\n";
	std::cout << "Availabe space: " << availabe_capacity << "\n";
	for (unsigned i = 0; i < cars_inside; i++) {
		std::cout << "Car [" <<i<< "] - " << vehicles[i]->registration() << "\n";
		std::cout << "Description: " << vehicles[i]->description() << "\n";
		std::cout << "___________________________________________________ \n";
	}
}
