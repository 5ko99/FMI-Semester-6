#include "Vehicle.h"

unsigned int Vehicle::s_vehiclesSerial = 0;

Vehicle::Vehicle() {
	m_vehiclesSerial = s_vehiclesSerial++;
	m_description = "";
	m_is_own = false;
}

Vehicle::Vehicle(const string& registration, const string& description) : Registration(registration) {
	this->m_vehiclesSerial = m_vehiclesSerial;
	m_description = description;

	int comand, owner;
	if (!m_is_own) {
		cout << "\nIs this vehicle will has owner? (If - YES - enter 1) ";
		cin >> comand;
		if (comand == 1) {
			cout << "\nEnter owner`s ID: ";
			cin >> owner;
			setOwner(owner);
			m_is_own = true;
		}
		else cout << "\nVehicle " << m_vehiclesSerial << "no has owner!";
		m_is_own = false;
	}
	else {
		cout << "\nVehicle " << m_vehiclesSerial << "yet has owner!";
	}
}

void Vehicle::setVehicleForPerson(Vehicle vehicle, int person_id) {
	string registration;
	string description;

	cout << "\nEnter registration for vehicle of person: " << endl;
	cin >> registration;
	setRegistration(registration);

	cout << "\nEnter description for vehicle of person: " << endl;
	cin >> description;
	setDescription(description);

	for (unsigned int j = 0; j < Person::getNumberOfPeoples(); ++j) {
		if (j == person_id) {
			if (m_is_own == false) {
				m_personsVehicles.push_back(vehicle);
			}
			else {
				cout << "\nThis vehicle has owner yet!";
				Vehicle newVehicle;
				setVehicleForPerson(newVehicle, person_id);
			}
		}
	}
}

void Vehicle::removeVehicleFromPerson(int person_id, int vehicle_id) {

	for (unsigned int j = 0; j < Person::getNumberOfPeoples(); ++j) {
		if (j == person_id) {
			for (unsigned int i = 0; i < m_personsVehicles.size(); ++i) {
				if (i == vehicle_id) {
					Vehicle temp = m_personsVehicles[i];
					m_personsVehicles[i] = m_personsVehicles[m_personsVehicles.size()];
					m_personsVehicles[m_personsVehicles.size()] = temp;
					m_personsVehicles.pop_back();
				}
			}
		}
	}
}

void Vehicle::printVehicle() const {
	printRegistration();
	cout << "\nDescription: " << m_description << endl;
	if (m_is_own == true) {
		cout << "\nOwner: " << m_owner << endl;
	}
}
