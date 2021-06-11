#pragma once
#include <string>
#include <vector>

using namespace std;

class Vehicle;

class Person
{
	string name;
	unsigned int id;
	vector<Vehicle*> vehicles{};
public:
	Person(const string& name, unsigned int id);
	void acquire(Vehicle& vehicle);
	void add(Vehicle& vehicle);
	void releaseVehicle(Vehicle& vehicle);
	void remove(Vehicle& vehicle);
	string toString() const;
	string toStringOwnedVehicles() const;
	string getName() const;
	unsigned int getId() const;
	vector<Vehicle*>* getVectorOfVehicles();
	bool operator==(const Person& person) const;
};

class  Registration
{
	string reg;
public:
	Registration(string reg);
	bool operator==(const Registration& registration) const;
	string getReg() const;
};

class  Vehicle
{
public:
	Person* owner;
	Registration registration;
	string description;
public:
	Vehicle(const Registration& registration, const string& description);
	void addOwner(Person& person);

	void releaseOwner();
	bool operator==(const Vehicle& vehicle) const;
	string toString() const;
	string toStringOwner() const;
	string getStringReg() const;
	Registration getReg() const;
	string getDes() const;
	Person* getOwner() const;
};

enum class id_type { id_invalid, id_person, id_reg };

class PeopleVehicles
{
	vector<Vehicle> vehicles{};
	vector<Person> people{};

	bool isPersonIdInDatabase(unsigned int personId) const;
	bool isVehicleRegInDatabase(const Registration& reg) const;
public:
	void createPerson(const string& name, unsigned int id);
	void createVehicle(const Registration& registration, const string& description);

	string toStringPeople() const;
	string toStringVehicles() const;
	Vehicle* findVehicle(const Registration& reg);
	Person* findPerson(unsigned int id);
	id_type getFormatType(const string& id);
	void removePerson(unsigned int id);
	bool removeVehicle(const Registration& reg);

	vector<Vehicle>* getVectorOfVehicles();
};
