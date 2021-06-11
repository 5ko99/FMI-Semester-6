#include "KAT.h"

void KAT::registerVehicle(std::string registretionNumber, std::string description) {
	Result<RegistrationNumber> result = RegistrationNumber::isValid(registretionNumber);

	if (!result.isValid) {
		throw std::runtime_error("Invalid registration-id!");
	}

	if (!_checkIfVehicleIdIsUnique(result.result)) {
		throw std::runtime_error("The registration-id is already registred!");
	}

	Vehicle* newVehicle = new Vehicle(result.result, description);
	vehicles.push_back(newVehicle);
}

bool KAT::_checkIfVehicleIdIsUnique(RegistrationNumber regNumber) {
	for (Vehicle* vehicle : vehicles) {
		if (vehicle->getRegistrationNumber() == regNumber) {
			return false;
		}
	}

	return true;
}

void KAT::registerPerson(std::string name, size_t id) {
	if (!_checkIfIdIsUnique(id)) {
		throw std::runtime_error("The person-id is already registred!");
	}

	Person* newPerson = new Person(name, id);
	persons.push_back(newPerson);
}

bool KAT::_checkIfIdIsUnique(size_t id) {
	for (Person* person : persons) {
		if (person->getId() == id) {
			return false;
		}
	}

	return true;
}

void KAT::releaseByVehicleId(size_t id, std::string registretionNumber) {
	Result<RegistrationNumber> result = RegistrationNumber::isValid(registretionNumber);

	if (!result.isValid) {
		throw std::runtime_error("Invalid registration-id!");
	}

	if (_checkIfVehicleIdIsUnique(result.result)) {
		throw std::runtime_error("The registration-id is not registred!");
	}

	if (_checkIfIdIsUnique(id)) {
		throw std::runtime_error("The person-id is not registred!");
	}

	Result<Person*> resultPerson = _getPerson(id);
	Result<Vehicle*> resultVehicle = _getVehicle(registretionNumber);

	if (resultPerson.isValid && resultVehicle.isValid) {
		Person* person = resultPerson.result;
		Vehicle* vehicle = resultVehicle.result;

		person->removeVehicle(vehicle);
	}
}

void KAT::aquireByVehicleId(size_t id, std::string registretionNumber) {
	Result<RegistrationNumber> result = RegistrationNumber::isValid(registretionNumber);

	if (!result.isValid) {
		throw std::runtime_error("Invalid registration-id!");
	}

	if (_checkIfVehicleIdIsUnique(result.result)) {
		throw std::runtime_error("The registration-id is not registred!");
	}

	if (_checkIfIdIsUnique(id)) {
		throw std::runtime_error("The person-id is already registred!");
	}

	Result<Person*> resultPerson = _getPerson(id);
	Result<Vehicle*> resultVehicle = _getVehicle(registretionNumber);

	if (resultPerson.isValid && resultVehicle.isValid) {
		Person* person = resultPerson.result;
		Vehicle* vehicle = resultVehicle.result;

		Result<Person*> resultCurrentOwner = vehicle->getOwner();
		if (resultCurrentOwner.isValid) {
			resultCurrentOwner.result->removeVehicle(vehicle);
			vehicle->setOwner(nullptr);
		}

		person->addVehicle(vehicle);
	}
}

Result<Vehicle*> KAT::_getVehicle(std::string regNumber) {
	Result<RegistrationNumber> result = RegistrationNumber::isValid(regNumber);

	if (!result.isValid) {
		return Result<Vehicle*> { false };
	}

	for (Vehicle* vehicle : vehicles) {
		if (vehicle->getRegistrationNumber() == result.result) {
			return Result<Vehicle*> { true, vehicle };
		}
	}

	return Result<Vehicle*> { false };;
}

Result<Person*> KAT::_getPerson(size_t id) {
	for (Person* person : persons) {
		if (person->getId() == id) {
			return Result<Person*> { true, person };
		}
	}

	return Result<Person*> { false };
}

void KAT::removePerson(size_t id) {
	if (_checkIfIdIsUnique(id)) {
		throw std::runtime_error("The person-id does not exist!");
	}

	bool erase = false;
	size_t pos = 0;
	for (size_t i = 0; i < persons.size(); i++) {
		if (persons[i]->getId() == id) {
			erase = true;
			pos = i;
			break;
		}
	}

	if (erase) {
		Person* p = persons[pos];
		persons.push_back(p);
		delete p;
	}
}

void KAT::removeVehicle(std::string registretionNumber) {
	Result<RegistrationNumber> result = RegistrationNumber::isValid(registretionNumber);

	if (!result.isValid) {
		throw std::runtime_error("Invalid registration-id!");
	}

	if (_checkIfVehicleIdIsUnique(result.result)) {
		throw std::runtime_error("The registration-id is not registred!");
	}

	std::vector<Vehicle*>::iterator it = vehicles.begin();
	while (it != vehicles.end()) {
		RegistrationNumber number = (*it)->getRegistrationNumber();
		if (number.prefix + number.infix + number.suffix == registretionNumber) {
			break;
		}
		++it;
	}

	if (it != vehicles.end()) {
		Result<Vehicle*> resultVehicle = _getVehicle(registretionNumber);
		Vehicle* vehicle = resultVehicle.result;
		vehicles.erase(it);
		delete vehicle;
	}


}

void KAT::showPersons() {
	printElement("ID", 5);
	printElement("NAME", 20);
	printElement("VEHICLE COUNT", 20);
	std::cout << std::endl;

	for (Person* person : persons) {
		printElement(person->getId(), 5);
		printElement(person->getName(), 20);
		printElement(person->getVehiclesCount(), 20);
		std::cout << std::endl;
	}
}

void KAT::showVehicles() {
	printElement("ID", 10);
	printElement("OWNER NAME", 20);
	printElement("DESCRIPTION", 50);
	std::cout << std::endl;

	for (Vehicle* vehicle : vehicles) {
		printElement(vehicle->getRegistrationNumber(), 10);
		Result<Person*> ownerResult = vehicle->getOwner();
		if (ownerResult.isValid) {
			printElement(ownerResult.result->getName(), 20);
		}
		else {
			printElement("nullptr", 20);
		}
		printElement(vehicle->getDescription(), 50);
		std::cout << std::endl;
	}
}

void KAT::showPersonById(size_t id) {
	Result<Person*> personResult = _getPerson(id);
	if (personResult.isValid) {
		Person* person = personResult.result;
		person->show();
	}
}

void KAT::showVehicleById(std::string regNumber) {
	Result<Vehicle*> vehicleResult = _getVehicle(regNumber);
	if (vehicleResult.isValid) {
		Vehicle* vehicle = vehicleResult.result;
		vehicle->show();
	}
}

KAT::KAT() {
	vehicles = {};
	persons = {};
}
