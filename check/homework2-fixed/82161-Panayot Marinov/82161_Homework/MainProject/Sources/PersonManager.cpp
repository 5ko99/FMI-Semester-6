#include "../Headers/PersonManager.h"
#include <iostream>
#include <stdexcept>

void PersonManager::addPerson(const string& name) {
	//Person* personToAdd = new Person(name);
	try{
		people.push_back(new Person(name));
	}
	catch(std::bad_alloc e) {
		std::cerr<<"Memory error!"<<std::endl;
		throw e;
	}
}

void PersonManager::removePerson(size_t id) {
	for (size_t i = 0; i < people.size(); i++) {
		if(people[i]->getId() == id) {
			people.erase(people.begin() + i);
			return;
		}
	}
	
	throw std::invalid_argument("There is no person with that ID");
}

void PersonManager::removePerson(const string& id) {
	return removePerson(std::stoi(id));
}

Person* PersonManager::findPerson(size_t id) {
    for (size_t i = 0; i < this->people.size(); i++) {
        if(people[i]->getId() == id)
            return people[i];
    }
    
    throw std::invalid_argument("There is no person with that ID");
}

Person* PersonManager::findPerson(const string& id) {
    return findPerson(std::stoi(id));
}

Person& PersonManager::at(size_t pos) {
	return *(people.at(pos));
}

const Person& PersonManager::at(size_t pos) const {
	return *(people.at(pos));
}

Person& PersonManager::operator[](size_t pos) {
	return *(people[pos]);
}

const Person& PersonManager::operator[](size_t pos) const {
	return *(people[pos]);
}

size_t PersonManager::getNumberOfPeople() const {
	return people.size();
}

void PersonManager::showAllPeople(std::ostream& out) {
	for (size_t i = 0; i < people.size(); i++) {
		out<<*(people[i])<<'\n';
	}
}

void PersonManager::showAllPeopleDetailed(std::ostream& out) {
	for (size_t i = 0; i < people.size(); i++) {
		people[i]->printDetailedInformation(out);
		out<<'\n';
	}
}
