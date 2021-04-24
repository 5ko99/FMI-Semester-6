//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Теодор Тодоров
// ФН: 45834
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 08:00
// Кой компилатор използвате: Clang
//

// Define to stop asserts
//#define NDEBUG

#include <cassert>
#include <cstring>
#include <iostream>

#include <string>

#include <cctype>

class Registration {
	char str_[9];

	bool setInnerStr(const char * str) {
		if (str == nullptr) {
			return false;
		}

		const size_t strSize = strlen(str);
		if (strSize == 7) {
			// Format is similar to A1111AA
			bool r1 = isalpha(str[0]);
			bool r2 = isdigit(str[1]);
			bool r3 = isdigit(str[2]);
			bool r4 = isdigit(str[3]);
			bool r5 = isdigit(str[4]);
			bool r6 = isalpha(str[5]);
			bool r7 = isalpha(str[6]);

			if (r1 && r2 && r3 && r4 && r5 && r6 && r7) {
				for (std::size_t i = 0; i < strSize; i++) {
					str_[i] = str[i];
				}
				for (std::size_t i = strSize; i < 9; i++) {
					str_[i] = 0;
				}
				return true;
			}
			else {
				return false;
			}
		}
		else if (strSize == 8) {
			// Format is similar to AA1111AA
			bool r1 = isalpha(str[0]);
			bool r2 = isalpha(str[1]);
			bool r3 = isdigit(str[2]);
			bool r4 = isdigit(str[3]);
			bool r5 = isdigit(str[4]);
			bool r6 = isdigit(str[5]);
			bool r7 = isalpha(str[6]);
			bool r8 = isalpha(str[7]);

			if (r1 && r2 && r3 && r4 && r5 && r6 && r7 && r8) {
				for (std::size_t i = 0; i < strSize; i++) {
					str_[i] = str[i];
				}
				for (std::size_t i = strSize; i < 9; i++) {
					str_[i] = 0;
				}
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	void setInnerStringToZero() {
		for (std::size_t i = 0; i < 9; i++) {
			str_[i] = 0;
		}
	}

public:
	Registration(const char * str) {
		bool success = setInnerStr(str);
		if (!success) {
			setInnerStringToZero();
			throw std::exception();
		}
	}

	Registration & operator=(const char * str) {
		bool success = setInnerStr(str);
		if (!success) {
			setInnerStringToZero();
			throw std::exception();
		}
		return *this;
	}

	bool operator==(const char * str) const {
		if (str == nullptr) {
			return false;
		}

		const size_t otherStringLength = strlen(str);
//		const size_t thisStringLength = strlen(str_); // Used for debug purposes

		if (otherStringLength != 7 && otherStringLength != 8) {
			return false;
		}

		for (std::size_t i = 0; i < otherStringLength; i++) {
			if (str_[i] != str[i]) {
				//
				return false;
			}
		}
		return true;
	}

	const char * toString() const {
		return str_;
	}
};

class Vehicle {
public:
	Registration regnum;
	std::string description;

	Vehicle(const char * regnum, const char * description) : regnum(regnum) {
		this->description = description;
	}
};

class VehicleList {
	Vehicle ** vehicles_ = nullptr;
	std::size_t capacity_ = 0;
	std::size_t size_ = 0;

	bool operator==(const VehicleList & vehicleList) const {
		if (vehicles_ == vehicleList.vehicles_ && capacity_ == vehicleList.capacity_ && size_ == vehicleList.size_) {
			return true;
		}
		return false;
	}

	bool existsRegNum(const char * regnum) const {
		if (regnum == nullptr || vehicles_ == nullptr) {
			throw std::exception();
		}
		for (std::size_t i = 0; i < size_; i++) {
			if (vehicles_[i]->regnum == regnum) {
				return true;
			}
		}
		return false;
	}

	std::size_t getIndexOf(const char * regnum) const {
		if (regnum == nullptr || vehicles_ == nullptr) {
			throw std::exception();
		}
		for (std::size_t i = 0; i < size_; i++) {
			if (vehicles_[i]->regnum == regnum) {
				return i;
			}
		}
		throw std::exception();
	}

public:
	VehicleList(std::size_t capacity) {
		if (capacity == 0) {
			throw std::exception();
		}
		try {
			vehicles_ = new Vehicle * [capacity];
			capacity_ = capacity;
			size_ = 0;
		}
		catch (std::bad_alloc &) {
			// Probably not needed, but why not
			throw;
		}
	}

	VehicleList(VehicleList & vehicleList) {
		*this = vehicleList;
	}

	VehicleList & operator=(const VehicleList & vehicleList) {
		if (*this == vehicleList) {
			return *this;
		}

		Vehicle ** newVehicles;
		try {
			newVehicles = new Vehicle * [vehicleList.capacity_];
			for (std::size_t i = 0; i < vehicleList.size_; i++) {
				Vehicle * rhs = vehicleList.vehicles_[i];
				newVehicles[i] = new Vehicle(rhs->regnum.toString(), rhs->description.c_str());
			}
		}
		catch (std::exception &) {
			throw;
		}

		capacity_ = vehicleList.capacity_;
		size_ = vehicleList.size_;

		delete[] vehicles_;
		vehicles_ = newVehicles;
		return *this;
	}

	~VehicleList() {
		if (vehicles_ == nullptr) {
			return;
		}
		for (std::size_t i = 0; i < size_; i++) {
			delete vehicles_[i];
		}
		delete[] vehicles_;
	}

	void insert(const char * regnum, const char * description) {
		if (regnum == nullptr || description == nullptr) {
			throw std::exception();
		}

		// Check invalid state, pretty much a sanity check
		if (capacity_ == 0 || vehicles_ == nullptr) {
			throw std::exception();
		}

		// Check full
		if (size_ >= capacity_) {
			throw std::exception();
		}

		// Check already exists
		bool alreadyExists = existsRegNum(regnum);
		if (alreadyExists) {
			throw std::exception();
		}

		vehicles_[size_++] = new Vehicle(regnum, description);
	}

	const Vehicle & at(std::size_t index) const {
		if (index >= size_) {
			throw std::exception();
		}
		return *vehicles_[index];
	}

	const Vehicle & operator[](std::size_t index) const {
		assert(index < size_);
		return *vehicles_[index];
	}

	bool empty() const {
		return size_ == 0;
	}

	std::size_t capacity() const {
		return capacity_;
	}

	std::size_t size() const {
		return size_;
	}

	const Vehicle * find(const char * regnum) const {
		try {
			std::size_t vIndex = getIndexOf(regnum);
			Vehicle * v = vehicles_[vIndex];
			return v;
		}
		catch (std::exception &) {
			return nullptr;
		}
	}
};

int main() {
	using std::size_t;
	using std::cin;
	using std::cout;
	using std::endl;

	size_t n;
	cout << "Enter VehicleList capacity: ";
	cin >> n;
	cin.ignore();

	// If this fails, all we can do is kill the process,
	// so it isn't in a try-catch block
	VehicleList vehicleList(n);

	cout << "Successfully created a VehicleList with a capacity of " << n << endl;
	cout << "Please start entering " << n << " vehicles" << endl;

	for (size_t i = 0; i < n; i++) {
		// Limit is 63 characters,
		// which can be changed at any time.
		//
		// regnum should only have a 9 char array,
		// but leaving it like this allows for more user error,
		// which shows the code can handle it
		//
		// Make sure to change following cin.getline() params if so
		char regnum[64];
		char desc[64];

		try {
			// cin.ignore() and cin.getline() are here,
			// because they can probably throw an exception
			cout << "Enter vehicle registration number: ";
			cin.getline(regnum, 64);

			cout << "Enter vehicle description: ";
//			cin.ignore();
			cin.getline(desc, 64);

			vehicleList.insert(regnum, desc);
			cout << "Successfully created vehicle with registration number \""
				 << regnum << "\" and description \"" << desc << "\"" << endl << endl;
		}
		catch (std::exception &) {
			cout << "An error occurred, please try entering this vehicle again" << endl;
			i--; // If underflow, i++ in for loop would make it overflow, resetting it to 0
			continue;
		}
	}

	cout << "Completed inputting the VehicleList" << endl;

	int option;
	cout << "Check if a registration number exists? Enter 1 for \"yes\", 0 for \"no\"" << endl;
	cin >> option;

	if (option == 1) {
		char regnum[64];

		try {
			cin.ignore();
			cin.getline(regnum, 64);
		}
		catch (std::exception &) {
			cout << "An error occurred in reading cin" << endl;
			return 0;
		}

		const Vehicle * vehicle = vehicleList.find(regnum);

		if (vehicle != nullptr) {
			cout << "Found vehicle with registration number \"" << vehicle->regnum.toString() << "\"" << endl;
			cout << "The vehicle's description is: \"" << vehicle->description << "\"" << endl;
		}
		else {
			cout << "Could not find vehicle with registration number \"" << regnum << "\"" << endl;
		}
	}

	return 0;
}