#pragma once
#include "Person.cpp"
class Commands
{
private:
	std::fstream myFile;
	std::string filename;
	std::vector<Person> people;
	std::vector<Vehicle> koli;

public:

	void open(const std::string& filename);
	void help();
	void close();
	void save();
	void saveas(std::string filename);

	void VEHICLE(std::string, std::string);
	void PERSON(std::string, std::string);
	void ACQUIRE(std::string, std::string);
	void DROP(std::string , std::string );
	void RELEASE(std::string, std::string);
	void REMOVE(std::string);
	void SHOW(std::string, std::string);

	std::vector<Person> getPeople() const;
	std::vector<Vehicle> getKoli() const;
	void printPeople() const;
	void printKoli() const;
	void deleteVeh(int, std::vector<Vehicle>);
	void deletePerson(int, std::vector<Person>);
};
