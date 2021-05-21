// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Мартин Попов
// ФН: 82134
// Специалност: компютърни науки
// Курс: първи
// Административна група: 1
// Ден, в който се явявате на контролното:  15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#define fileErrorMessage "Could not open file"
#define fileError \
std::invalid_argument(fileErrorMessage);

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <fstream>
#include <stdexcept>

enum type {
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class Message {
	std::string description;
	int type;

public:
	Message(int type, std::string desc) : description(desc), type(type) {}

	std::string getType() const {
		std::string typeMsg;
		switch (type) {
		case INFO:
			typeMsg = "INFO";
			break;
		case WARNING:
			typeMsg = "WARNING";
			break;
		case ERROR:
			typeMsg = "ERROR";
			break;
		case CRITICAL:
		default:
			typeMsg = "CRITICAL";
			break;
		}
		return typeMsg;
	}

	const std::string& getDescription() const {
		return description;
	}

	friend std::ostream& operator<<(std::ostream& os, const Message& m);
};

//print message
std::ostream& operator<<(std::ostream& os, const Message& m) {
	switch (m.type) {
	case INFO:
		os << "INFO";
		break;
	case WARNING:
		os << "WARNING";
		break;
	case ERROR:
		os << "ERROR";
		break;
	case CRITICAL:
	default:
		os << "CRITICAL";
		break;
	}
	os << ": " << m.description;
	return os;
}

class Logger {
public:
	Logger() {}

	Logger& operator<<(const Message& m);
};

//config
class Configuration {
	std::string file;
	Logger log;

public:
	static Configuration& Get() {
		static Configuration confInstance;
		return confInstance;
	}

	void loadConfig(std::string path) {
		if (path == "") {
			std::ifstream logFile("config.txt");
			if (!logFile) {
				throw fileError;
			}
			std::getline(logFile, file);
		}
		else {
			std::ifstream logFile(path);
			if (!logFile) {
				std::ofstream myLogFile(path);
				if (!myLogFile) {
					throw fileError;
				}
			}
			file = path;
		}
	}

	void loadConfig() {
		loadConfig("");
	}

	const std::string& getLogFileName() {
		return file;
	}

};
Configuration& config = Configuration::Get();

//log in file
Logger& Logger::operator<<(const Message& m) {

	std::ofstream file(config.getLogFileName(), std::ios_base::app);
	if (!file) {
		throw fileError;
	}
	file << m.getType() << ": " << m.getDescription();
	file << "\n";

	return *this;
}

int inputMessage() {
	Logger log;

	while (true) {
		try {
			int type;
			std::cin >> type;
			if (!std::cin) {
				std::cin.clear();
				std::cin.ignore();
				throw std::invalid_argument("Please enter valid data");
			}

			std::cin.ignore();

			std::string desc;
			std::getline(std::cin, desc);

			Message m(type, desc);
			log << m;
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << "\n";
			if (e.what() == fileErrorMessage) {
				return 2;
			}
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {

	if (argc == 2) {
		try {
			config.loadConfig(argv[1]);
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what();
			return 1;
		}
	}
	else {
		config.loadConfig();
	}

	return inputMessage();
}