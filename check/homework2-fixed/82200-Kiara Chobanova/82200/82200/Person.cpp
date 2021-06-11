#include "Person.h"

unsigned int Person::s_personsIdentificator = 0;

Person::Person() {
	m_personsSerial = s_personsIdentificator++;
	m_name = "";
	m_numberOfVehicles = 0;
}


Person::Person(const string& name, const size_t numberOfVehicles) {
	this->m_personsSerial = m_personsSerial;
	m_name = name;
	m_numberOfVehicles = numberOfVehicles;
	for (unsigned int i = 0; i < m_numberOfVehicles; ++i) {
		Vehicle vehicle;
		vehicle.setVehicleForPerson(vehicle, m_personsSerial);
	}
}

void Person::printPerson() const {

	cout << "Name: " << m_name << endl;
	cout << "ID: " << m_personsSerial << endl;
	cout << "Number of " << m_personsSerial << " vehicles: " << m_numberOfVehicles << endl;
}

