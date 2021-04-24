#include <iostream>
using namespace std;

class MyString {
private:
	char* _str;
public:
	MyString();
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();
	const char* getString() const;
	void setString(const char* str) {
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	MyString(const char* str);
	char& at(size_t pos);
	const char& at(size_t pos) const;

	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;

	char& front();
	const char& front() const;
	char& back();
	const char& back() const;

	bool empty() const;
	size_t size() const;
	void clear();
	void push_back(char c);
	void pop_back();

	MyString& operator+=(char c);
	MyString& operator+=(const MyString& rhs);
	MyString operator+(char c) const;
	MyString operator+(const MyString& rhs) const;
	const char* c_str() const;
	bool operator==(const MyString &rhs) const;
	bool operator<(const MyString &rhs) const;

	char* getStringAdded(char c);
};

MyString::MyString(): _str(NULL){
	
}
MyString::MyString(const MyString& other) {
	_str = new char[strlen(other._str) + 1];
	strcpy(_str, other._str);
}
MyString& MyString:: operator=(const MyString& other) {
	if (this != &other) {
		delete[] _str;

		_str = new char[strlen(other._str) + 1];
		strcpy(_str, other._str);
	}
	return *this;
}
MyString::~MyString() {
	delete[] _str;
}
MyString::MyString(const char* str) {
	MyString myStringClass;
	myStringClass.setString(str);
}
const char* MyString::getString() const {
	return _str;
}
char& MyString::at(size_t pos) {
	if (pos < 0) throw out_of_range("Out of range");
	return _str[pos];
}
const char& MyString::at(size_t pos) const {
	if (pos < 0) throw out_of_range("Out of range");
	return _str[pos];
}

char& MyString::operator[](size_t pos) {
	return _str[pos];
}

const char& MyString::operator[](size_t pos) const {
	return _str[pos];
}

char & MyString::front() {
	return _str[0];
}

const char & MyString::front() const {
	return _str[0];
}

char& MyString::back() {
	int length = strlen(_str);
	return _str[length - 1];
}
const char& MyString::back() const {
	int length = strlen(_str);
	return _str[length - 1];
}

MyString& MyString::operator+=(char c) {
	this->push_back(c);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {
	char* new_string = rhs._str;

	for (int j = 0; j < size(); j++) {
		this->push_back(new_string[j]);
	}

	return *this;
}

MyString MyString::operator+(char c) const {
	return MyString() += c;
}

MyString MyString::operator+(const MyString& rhs) const {
	return MyString() += rhs;
}

const char* MyString::c_str() const {
	return _str;
}
bool MyString::operator==(const MyString &rhs) const {
	return _str == rhs._str;
}
bool MyString::operator<(const MyString &rhs) const {
	return _str < rhs._str;
}
bool MyString::empty() const {
	return _str == NULL;
}
size_t MyString::size() const {
	return strlen(_str);
}
void MyString::clear() {
	_str = NULL;
}
void MyString::push_back(char c) {
	char* new_str = getStringAdded(c);
	*this = MyString(new_str);
	delete[] new_str;
}

void MyString::pop_back() {
	int length = size();
	char* new_str = new char[length];

	for (int i = 0; i < length - 1; i++) {
		new_str[i] = _str[i];
	}
	new_str[length] = '\0';

	*this = MyString(new_str);

	delete[] new_str;
}

char* MyString::getStringAdded(char c) {
	int length = strlen(_str);
	char* new_string = new char[length + 2];

	for (int i = 0; i < length; i++) {
		new_string[i] = _str[i];
	}
	new_string[length] = c;
	new_string[length + 1] = '\0';

	return new_string;
}

//
//Vehicle Class

class Vehicle {
private:
	MyString _registration;
	MyString _description;
	size_t _space;
public:
	Vehicle(const char* registration, const char* description, size_t space);
	Vehicle(const Vehicle& other);

	const char* registration() const;
	const char* description() const;
	size_t space() const;
};
Vehicle::Vehicle(const char* registration, const char* description, size_t space) {
	_registration.setString(registration);
	_description.setString(description);
	_space = space;
}
const char* Vehicle::registration() const {
	return _registration.getString();
}
const char* Vehicle::description() const {
	return _description.getString();
}
size_t Vehicle::space() const {
	return _space;
}

Vehicle::Vehicle(const Vehicle& other) {
	_registration = other.registration();
	_description = other.description();
	_space = other._space;
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
	if (this != &other) {
		_registration = other.registration();
		_description = other.description();
		_space = other._space;
	}
	return *this;
}

//
// Garage Class

class Garage {
private:
	Vehicle* _v;
	size_t vehicle_count = 0;
	size_t _size;

public:
	Garage(size_t size);
	Garage(const Garage& other);
	Garage& operator=(const Garage& other);
	~Garage() {
		delete[] _v;
	}

	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(size_t pos) const;
	const Vehicle& operator[](size_t pos) const;
	bool empty() const;
	size_t size() const;
	void clear();
	const Vehicle* find(const char* registration);

	int getCurrentVicleSpaces() {
		int total_space_count = 0;
		for (int i = 0; i < vehicle_count; i++) {
			total_space_count += _v[i].space();
		}

		return total_space_count;
	}

	void displayAllVehicles() {
		for (int i = 0; i < vehicle_count; i++) {
			cout << at(i).registration() << " " << at(i).description() << " " << at(i).space() << "\n";
		}
	}
};
Garage::Garage(size_t size) {
	_size = size;
}
Garage::Garage(const Garage& other) {
	_v = other._v;
	
	_size = other._size;
}
Garage& Garage::operator=(const Garage& other) {
	if (this != &other) {
		_v = other._v;
		_size = other._size;

	}
	return *this;
}
const Vehicle& Garage::at(size_t pos) const {
	if (pos >= _size) throw out_of_range("Out of range");
	return _v[pos];
}
const Vehicle& Garage::operator[](size_t pos) const {
	return _v[pos];
}

bool Garage::empty() const {
	// return vehicle_count == 0;
	return _v == NULL;
}
size_t Garage::size() const {
	return vehicle_count;
}
void Garage::clear() {
	_v = NULL;
	vehicle_count = 0;
}

void Garage::insert(Vehicle& v) {
	if (v.space() + getCurrentVicleSpaces() > size()) {
		throw "Not enough space";
	}
	else if (find(v.registration()) != nullptr) {
		throw "Vehicle already inside";
	}
	else {
		vehicle_count++;
		_v[vehicle_count] = v;
	}
}
void Garage::erase(const char* registration) {
	const Vehicle* found_vehicle = find(registration);

	if (found_vehicle == nullptr) {
		throw "Vehicle not in garage";
	}
	else {
		_size -= found_vehicle->space();
		vehicle_count--;
	}
}
const Vehicle* Garage::find(const char* registration) {
	for (int i = 0; i < vehicle_count; i++) {
		if (_v[i].registration() == registration) {
			//return this->at(i);
			break;
		}
	}

	return nullptr;
}

int main() {
	int garage_size = 0;
	int chosen_option = -1;
	
	cout << "Enter garage size: ";
	cin >> garage_size;

	Garage my_garage = Garage(garage_size);

	cout << "For inserting vehicle press 1, \n For removing vehicle press 2, \n For viewing vehicles press 3";
	cin >> chosen_option;

	switch (chosen_option) {
	case 1: {
		char* registartion;
		char* description;
		size_t space;

		cout << "Enter registartion, description and space for your vehicle:";
		cin >> registartion >> description >> space;
		Vehicle new_vehicle = Vehicle(registartion, description, space);

		my_garage.insert(new_vehicle);

		break;
	}
	case 2:
		char* registartion;

		cout << "Enter registartion for your vehicle:";
		cin >> registartion;

		my_garage.erase(registartion);

		break;
	case 3:
		my_garage.displayAllVehicles();
		break;
	default:
		cout << "Wrong option selected";
	}

	return 0;
}