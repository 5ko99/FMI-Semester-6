#include "Registration.h"

Registration::Registration(const string& registration) {
	setRegistration(registration);
}

Registration::Registration() {
	m_registration = "";
}

bool Registration::validation(const string& registration) {
	return regex_match(registration, std::regex("([A-Z]{2}[0-9]{4}[A-Z]{2}.)|([A-Z]{1}\\s*[0-9]{4}[A-Z]{2}.)"));
}

void Registration::printRegistration() const {
	cout << "\nRegistration: " << getRegistration() << endl;
}

void Registration::setRegistration(const string& registration) {
	string newRegistration;
	if (validation(registration)) {
		m_registration = registration;
	}
	else {
		throw std::invalid_argument("Inavild registration!");
		cout << "\nEnter new registration: ";
		cin >> newRegistration;
		setRegistration(newRegistration);
	}
}
