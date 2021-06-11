#include "Console.h"

Console::Console(std::istream& in) : input(in) {
	kat = new KAT();
}

void Console::load() {
	std::string line;
	while (std::getline(input, line)) {
		if (parseCommand(line)) {
			memorry.push_back(line);
		}
	}
}

void Console::start() {
	std::string line;
	while (std::getline(std::cin, line)) {
		if (parseCommand(line)) {
			memorry.push_back(line);
		}
	}
}

bool Console::parseCommand(std::string line) {
	try {
		Result<std::string> commandResult = getWord(line);

		if (!commandResult.isValid) {
			return false;
		}

		std::string command = commandResult.result;
		for (auto& c : command) c = toupper(c);

		if (command == "VEHICLE") {
			handleVehicle(line);
		}
		else if (command == "PERSON") {
			handlePerson(line);
		}
		else if (command == "ACQUIRE") {
			handleQuire(line);
		}
		else if (command == "RELEASE") {
			handleRelease(line);
		}
		else if (command == "REMOVE") {
			handlerRemoveRandom(line);
		}
		else if (command == "SHOW") {
			handleShow(line);
		}
		else if (command == "SAVE") {
			handleSave(line);
		}
		else {
			throw std::runtime_error("Unknown command!");
		}

		return true;
	}
	catch (std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
		return false;
	}
}

void Console::handleVehicle(std::string line) {
	Result<std::string> regNumberResult = getWord(line),
		descriptionResult = getWord(line);

	if (!regNumberResult.isValid || !descriptionResult.isValid) {
		throw std::runtime_error("The syntax of the comand VEHICLE is: \n VEHICLE <vehicle-id> <string>");
	}

	std::string regNumber = regNumberResult.result,
		description = descriptionResult.result;

	kat->registerVehicle(regNumber, description);
}

void Console::handlePerson(std::string line) {
	Result<std::string> nameResult = getWord(line),
		idResult = getWord(line);

	if (!nameResult.isValid || !idResult.isValid) {
		throw std::runtime_error("The syntax of the comand PERSON is: \n PERSON <string> <person-id>");
	}

	std::string name = nameResult.result,
		id = idResult.result;

	bool isIdNumber = true;
	for (char ch : id) {
		isIdNumber = isIdNumber && isNumber(ch);
	}

	if (!isIdNumber) {
		throw std::runtime_error("The syntax of the comand PERSON is: \n PERSON <string> <person-id>");
	}

	kat->registerPerson(name, std::stoul(id, nullptr, 0));
}

void Console::handleQuire(std::string line) {
	Result<std::string> idResult = getWord(line),
		regNumberResult = getWord(line);

	if (!regNumberResult.isValid || !idResult.isValid) {
		throw std::runtime_error("The syntax of the comand ACQUIRE is: \n ACQUIRE <person-id> <vehicle-id>");
	}

	std::string regNumber = regNumberResult.result,
		id = idResult.result;

	bool isIdNumber = true;
	for (char ch : id) {
		isIdNumber = isIdNumber && isNumber(ch);
	}

	if (!isIdNumber) {
		throw std::runtime_error("The syntax of the comand ACQUIRE is: \n ACQUIRE <person-id> <vehicle-id>");
	}

	kat->aquireByVehicleId(std::stoul(id, nullptr, 0), regNumber);
}

void Console::handleRelease(std::string line) {
	Result<std::string> idResult = getWord(line),
		regNumberResult = getWord(line);

	if (!regNumberResult.isValid || !idResult.isValid) {
		throw std::runtime_error("The syntax of the comand RELEASE is: \n RELEASE <person-id> <vehicle-id>");
	}

	std::string regNumber = regNumberResult.result,
		id = idResult.result;

	bool isIdNumber = true;
	for (char ch : id) {
		isIdNumber = isIdNumber && isNumber(ch);
	}

	if (!isIdNumber) {
		throw std::runtime_error("The syntax of the comand RELEASE is: \n RELEASE <person-id> <vehicle-id>");
	}

	kat->releaseByVehicleId(std::stoul(id, nullptr, 0), regNumber);
}

void Console::handlerRemoveRandom(std::string line) {
	Result<std::string> randomResult = getWord(line);

	if (!randomResult.isValid) {
		throw std::runtime_error("The syntax of the comand REMOVE is: \n REMOVE <person-id>/<vehicle-id>");
	}

	std::string random = randomResult.result;

	bool isIdNumber = true;
	for (char ch : random) {
		isIdNumber = isIdNumber && isNumber(ch);
	}

	Result<RegistrationNumber> result = RegistrationNumber::isValid(random);

	if (isIdNumber) {
		kat->removePerson(std::stoul(random, nullptr, 0));
	}
	else if (result.isValid == true) {
		kat->removeVehicle(random);
	}
	else {
		throw std::runtime_error("The syntax of the comand REMOVE is: \n REMOVE <person-id>/<vehicle-id>");
	}
}

void Console::handleShow(std::string line) {
	Result<std::string> randomResult = getWord(line);

	if (!randomResult.isValid) {
		throw std::runtime_error("The syntax of the comand SHOW is: \n SHOW [PEOPLE|VEHICLES|<id>]");
	}

	std::string random = randomResult.result;
	for (auto& c : random) c = toupper(c);

	bool isIdNumber = true;
	for (char ch : random) {
		isIdNumber = isIdNumber && isNumber(ch);
	}

	Result<RegistrationNumber> result = RegistrationNumber::isValid(random);

	if (random == "PEOPLE") {
		kat->showPersons();
	}
	else if (random == "VEHICLES") {
		kat->showVehicles();
	}
	else if (isIdNumber) {
		kat->showPersonById(std::stoul(random, nullptr, 0));
	}
	else if (result.isValid == true) {
		kat->showVehicleById(random);
	}
	else {
		throw std::runtime_error("The syntax of the comand SHOW is: \n SHOW [PEOPLE|VEHICLES|<id>]");
	}
	std::cout << std::endl;
}

void Console::handleSave(std::string line) {
	Result<std::string> pathResult = getWord(line);
	std::string path = pathResult.result;
	std::ofstream saveFile;
	saveFile.open(path);

	for (std::string memor : memorry) {
		saveFile << memor << std::endl;
	}

	saveFile.close();

	std::cout << "SAVE IN:\n" << std::filesystem::current_path() << "/" << path << std::endl;
}
