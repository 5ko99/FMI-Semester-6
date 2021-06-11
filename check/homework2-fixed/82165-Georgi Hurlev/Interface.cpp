#include "Interface.h"
#include <iostream>
#include  <limits> //numeric_limits for streamsize


const std::vector<Person*>* Interface::getPeoplePointer() const
{
	return &people;
}

const std::vector<Vehicle*>* Interface::getVehiclesPointer() const
{
	return &vehicles;
}

void Interface::executeCommand(std::string commandLine)
{
	command.processCommand(commandLine);

	switch (command.getCommand())
	{
	case CommandOption::acquire:
	{
		acquireVehicle();
		break;
	}
	case CommandOption::save:
	{
		saveToFile();
		break;
	}
	case CommandOption::person:
	{
		addPerson();
		break;
	}
	case CommandOption::release:
	{
		releaseVehicle();
		break;
	}
	case CommandOption::removed:
	{
		removeObject();
		break;
	}
	case CommandOption::show:
	{
		showObjects();
		break;
	}
	case CommandOption::vehicle:
	{
		addVehicle();
		break;
	}
	default:
		throw std::logic_error("Invalid command");
		break;
	}
}

void Interface::saveToFile()
{
	std::string savePath = command.getSavePath();

	if (savePath.size() >= 2 && savePath.front() == '"' && savePath.back() == '"') { //address is quoted for some reason?
		editAdress(savePath);
	}
	if (savePath.empty()) {
		throw std::logic_error("No file directory found.\n");
		
	}
	std::fstream file(savePath);
	if (file.good())//already exists
	{
		std::cout << "The file already exists. Saving there will erase it's current content.\n";
		int ans = 0;
		do {
			std::cout << "1.No, don't save .\n";
			std::cout << "2.Save and erase file content.\n";
			std::cout << "Input your choice:";
			std::cin >> ans;
			if (!std::cin) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				ans = 0;
			}

		} while (ans != 1 && ans != 2);
		if (ans == 1) {
			std::cout << "File was not saved.\n";
			return;
		}
	}
	file.close();

	file.open(savePath, std::fstream::out | std::fstream::trunc);
	if (!file.is_open())
	{
		throw std::logic_error(savePath + " could not be opened!\n");
	}
	//we add people and then vehs
	for (size_t i = 0; i < people.size(); i++) {
		people[i]->outputAsCommand(file);
	}
	for (size_t i = 0; i < vehicles.size(); i++) {
		vehicles[i]->outputAsCommand(file);
	}
	file.close();
	std::cout << "File successfully saved in " << savePath << std::endl;

}

void Interface::addVehicle()
{
	Vehicle* newVeh;
	try {
		//newVeh = new Vehicle(std::move(command.getParameters<Vehicle>()));
		newVeh = new Vehicle(std::move(command.getVehicleParameters()));
	}
	catch (const std::exception& e) {
		std::cerr << "Could not add a new Vehicle\n";
		return;
	}
	if (findVehIndexById(newVeh->getRegistration()) < 0)
	{
		vehicles.push_back(newVeh);
	}
}

void Interface::addPerson()
{
	Person* newPerson;
	try {
		newPerson = new Person(std::move(command.getPersonParameters()));
		if (findPersonIndexById(newPerson->getId()) >= 0) { //exists
			std::cout << "A person with such ID already exists . No new person was added.\n";
			delete newPerson;
			return;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Could not add a new Person. " << e.what() << std::endl;
		return;
	}
	if (findPersonIndexById(newPerson->getId()) < 0)
	{
		people.push_back(newPerson);
	}
}

void Interface::acquireVehicle()
{
	//std::tuple <unsigned int, std::string> param = command.getParameters<std::tuple <unsigned int, std::string> >();
	std::tuple <unsigned int, std::string> param = command.getAquireParameters();
	long long personIndex = findPersonIndexById(std::get<0>(param));
	long long vehIndex = findVehIndexById(std::get<1>(param));
	//Person* person = people[findPersonIndexById(std::get<0>(param))];
	//Vehicle* veh = vehicles[ findVehIndexById(std::get<1>(param))];
	if (personIndex >= 0) {
		if (vehIndex >= 0) {
			//people[personIndex]->addVehicle(*vehicles[vehIndex]);
			vehicles[vehIndex]->addOwner(*people[personIndex]);
		}
		else {
			std::cout << "No such vehicle exists in the data with registration : " << std::get<1>(param) << std::endl;
		}
	}
	else {
		std::cout << "No such person exists in the data with ID : " << std::get<0>(param) << std::endl;
	}
}

void Interface::releaseVehicle()
{
	//std::tuple <unsigned int, std::string> param = command.getParameters<std::tuple <unsigned int, std::string> >();
	std::tuple <unsigned int, std::string> param = command.getReleaseParameters();
	long long index = findPersonIndexById(std::get<0>(param));
	//Person* person = people[findPersonIndexById(std::get<0>(param))];
	if (index >= 0) {
		//people[index]->removeVehicle(std::get<1>(param));
		index = findVehIndexById(std::get<1>(param));
		if (index >= 0) {
			vehicles[index]->removeOwner();
		}
		else {
			std::cout << "No such vehicle found with registration " << std::get<1>(param) << std::endl;
		}
	}
	else {
		std::cout << "No such person exists in the data with ID : " << std::get<0>(param) << std::endl;
	}
}

void Interface::removeObject()
{
	//std::string id = command.getParameters<std::string>();
	std::string id = command.getRemoveParameter();
	if (id.empty()) {
		std::cout << "No remove parameter found.\n";
		return;
	}
	if (id.front() >= 'A' && id.front() <= 'Z') //should be a Registration
	{
		try {
			try {
				Registration reg(id);//checking if it's valid
			}
			catch (const int e)
			{
				if (e == -1)
				{
					std::cout << "Invalid registration " << id << std::endl;
				}
				return;
			}
			removeVehicle(id);
		}
		catch (const int e)
		{
			if (e == -1)
			{
				std::cerr << "Invalid input. No such vehicle or person found with " << id << std::endl;
			}
		}
	}
	else { //should be a person
		try {
			removePerson(std::stoi(id));
		}
		catch (const std::exception&) {
			std::cout << "No such object with id " << id << " found.\n";
		}
	}
}

bool Interface::doWants() const {
	short answer = 0;
	do {
		std::cout << "1.Yes, remove it anyway.\n";
		std::cout << "2.No, don't remove it.\n";
		std::cout << "Your choice:";
		std::cin >> answer;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.\n\n";
			answer = 0;
		}

	} while (answer != 1 && answer != 2);
	return answer == 1;
}

void Interface::editAdress(std::string& adress)
{
	//unsigned i = 0;
	if (adress.size() >= 2) {
		adress.erase(adress.begin(), adress.begin() + 1);
		adress.erase(adress.end() - 1, adress.end());
	}

}

void Interface::removePerson(unsigned const id)
{
	long long index = findPersonIndexById(id);
	//Person* person = people[index];
	if (index >= 0) {
		if (people[index]->getOwnedVehNum() > 0) {
			std::cout << "The person with id " << id << " owns " << people[index]->getOwnedVehNum() << " vehicle(s).\n";
			std::cout << "Do you want to remove it anyway?\n";
			if (!doWants()) {
				std::cout << "Person was not removed.\n";
				return;
			}
		}

		people[index]->removeAllVehicles();//removes car owners as well
		delete people[index];
		people.erase(people.begin() + index);
	}
	else {
		std::cout << "No such person exists in the data with ID : " << id << std::endl;
	}

}

void Interface::removeVehicle(std::string& id)
{
	long long index = findVehIndexById(id);
	//Person* person = people[index];
	if (index >= 0) {
		if (vehicles[index]->hasOwner()) {
			std::cout << "The vehicles with reg " << vehicles[index]->getRegistration() << " has an owner.\n";
			std::cout << "Do you want to remove it anyway?\n";
			if (!doWants()) {
				std::cout << "Vehicle was not removed.\n";
				return;
			}
		}
		vehicles[index]->removeOwner(true);//removes it's ownership from it's owner as well
		delete vehicles[index];
		vehicles.erase(vehicles.begin() + index);
	}
	else {
		std::cout << "No such vehicle exists in the data with Reg : " << id << std::endl;
	}
}

void Interface::showObjects()
{
	//std::string param = command.getParameters<std::string>();
	std::string param;
	try {
		param = command.getShowParameter();
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		return;
	}
	if (param.empty()) {
		//throw std::logic_error("No SHOW parameters found.\n");
		std::cout << "No SHOW parameters found.\n";
		return;
	}
	if (param == "PEOPLE") //all
	{
		for (unsigned i = 0; i < people.size(); i++)
		{
			people[i]->printFullInfo(std::cout);
			std::cout << std::endl;
		}
		if (people.empty()) {
			std::cout << "(None)\n";
		}
	}
	else if (param == "VEHICLES")//all
	{
		for (unsigned i = 0; i < vehicles.size(); i++)
		{
			vehicles[i]->printFullInfo(std::cout);
			std::cout << std::endl;
		}
		if (vehicles.empty()) {
			std::cout << "(None)\n";
		}
	}
	else if (param.front() >= 'A' && param.front() <= 'Z') //should be a Registration
	{
		try {
			Registration reg(param);//checking if it's valid
			long long index = findVehIndexById(param);
			//Vehicle* veh = vehicles[findVehIndexById(param)];
			if (index >= 0)
			{
				vehicles[index]->printFullInfo(std::cout);
			}
			else {
				std::cout << "No such vehicle exists in the data with registration : " << param << std::endl;
			}
		}
		catch (const int e)
		{
			if (e == -1)
			{
				std::cerr << "Invalid input. No such vehicle or person found with " << param << std::endl;
			}
		}
	}
	else { //should be a person
		long long index;
		try {
			index = findPersonIndexById(std::stoi(param));
		}
		catch (const std::exception&) {
			std::cout << "No such object exists in the data with ID : " << param << std::endl;
			return;
		}
		//Person* person = people[findPersonIndexById(std::stoi(param))];
		if (index >= 0) {
			people[index]->printFullInfo(std::cout);
		}
		else {
			std::cout << "No such person exists in the data with ID : " << param << std::endl;
		}
	}
}

long long Interface::findVehIndexById(std::string id)
{
	for (unsigned i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i]->getRegistration() == id) {
			return i;
		}
	}
	return -1;
}

//I've assumed that I wont have index > unsigned , but I need to return -1 if there is no such person so its long
long long Interface::findPersonIndexById(unsigned id)
{
	for (unsigned i = 0; i < people.size(); i++)
	{
		if (people[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}
