//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Теодор Тодоров
// ФН: 45834
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 15-05-2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: Clang
//

#include <cassert>
#include <iostream>
#include <string>
#include <fstream>

class Message {
public:
	enum Type {
		INFO, WARNING, ERROR, CRITICAL
	};

private:
	const Type type;
	const std::string description;

	const char * typeToString() const {
		switch (type) {
			case INFO:
				return "INFO";

			case WARNING:
				return "WARNING";

			case ERROR:
				return "ERROR";

			case CRITICAL:
				return "CRITICAL";
		}
		throw std::invalid_argument("Invalid arg in typeToString()");
	}

public:
	explicit Message(Type type, const std::string & description) :
		type(type), description(description) {

	}

	const Type getType() const {
		return type;
	}

	const std::string & getDescription() const {
		return description;
	}

	friend std::ostream & operator<<(std::ostream & out, const Message & message) {
		return out << message.typeToString() << ": " << message.description;
	}
};

class Logger {
	std::string filePath;

	static std::size_t * getMessageTypeCount() {
		static std::size_t messageTypeCount[4] {0, 0, 0, 0};
		return messageTypeCount;
	}

	static void incrementMessageTypeCount(Message::Type type) {
		getMessageTypeCount()[type]++;
	}

public:
	Logger() = default;

	explicit Logger(const std::string & filePath) {
		this->filePath = filePath;

		std::ofstream file;
		file.open(filePath, std::ios::app);
		if (!file.is_open()) {
			throw std::invalid_argument("Could not access specified file path");
		}
		file.close();
	}

	const std::string & getFilePath() const {
		return filePath;
	}

	void setFilePath(const std::string & filePath) {
		this->filePath = filePath;
	}

	friend Logger & operator<<(Logger & log, const Message & message) {
		std::ofstream file(log.filePath, std::ios::out | std::ios::app | std::ios::ate);
		if (!file.is_open()) {
			throw std::invalid_argument("Could not open logger file");
		}

		try {
			file << message << '\n';
			incrementMessageTypeCount(message.getType());
		}
		catch (std::exception & e) {
			throw std::runtime_error("Could not write to logger file");
		}

		try {
			file.close();
		}
		catch (std::exception & e) {
			throw std::runtime_error("Could not close logger file");
		}

		return log;
	}

	static std::size_t getMessageTypeCount(Message::Type type) {
		// Sanity check
		if (type >= 4) {
			throw std::invalid_argument("Message::Type enum has been changed, please change code accordingly");
		}

		return getMessageTypeCount()[type];
	}
};

class Configuration {
	bool ready = false;
	std::string filePath;
	Logger logger;

	Configuration() = default;
	~Configuration() = default;

	static Configuration & getInstancePrivate() {
		static Configuration configuration;
		return configuration;
	}

public:
	Configuration(const Configuration & other) = delete;
	Configuration(Configuration && other) = delete;

	Configuration & operator=(const Configuration & other) = delete;
	Configuration & operator=(Configuration && other) = delete;

	const std::string & getFilePath() const {
		return filePath;
	}

	Logger & getLogger() {
		return logger;
	}

	static Configuration & getInstance() {
		if (isLoaded()) {
			return getInstancePrivate();
		}
		throw std::runtime_error("Configuration must be loaded first, use Configuration::load()");
	}

	static bool isLoaded() {
		return getInstancePrivate().ready;
	}

	static void load(const std::string & configFilePath) {
		std::fstream file(configFilePath);
		if (!file.is_open()) {
			throw std::runtime_error("Could not open config file");
		}

		char c;
		std::string fileContents;
		while (true) {
			file.read((char *) &c, sizeof(char));
			if (file.eof()) {
				break;
			}

			fileContents += c;
		}

//		std::cout << "fileContents = " << fileContents << std::endl;

		getInstancePrivate().filePath = configFilePath;
		try {
			getInstancePrivate().logger = Logger(fileContents);
		}
		catch (std::exception &) {
			getInstancePrivate().ready = false; // Just in case it was true before
			throw;
		}
		getInstancePrivate().ready = true;
	}
};

int main(int argc, char ** argv) {

	std::string configFile;
	if (argc == 1) {
		configFile = "config.txt";
	}
	else if (argc == 2) {
		configFile = argv[1];
	}
	else {
		std::cout << "Too many arguments, please pass either 0 or 1\n";
		std::cout << "Process is stopping" << std::endl;
		return 1;
	}

	try {
		Configuration::load(configFile);
	}
	catch (std::exception &) {
		std::cout << "Could not load configuration from file: \"" << configFile << "\"\n";
		std::cout << "Process is stopping" << std::endl;
		return 2;
	}

	// Sanity check
	if (!Configuration::isLoaded()) {
		std::cout << "Configuration was loaded, but somehow is not ready.\n";
		std::cout << "Process is stopping" << std::endl;
		return 3;
	}
	std::cout << "Configuration loaded successfully!" << std::endl;

	std::string cmd;
	while (true) {
		std::cout << "\nAvailable commands: " << '\n';
		std::cout << "\tinfo <message>" << '\n';
		std::cout << "\twarning <message>" << '\n';
		std::cout << "\terror <message>" << '\n';
		std::cout << "\tcritical <message>" << '\n';
		std::cout << "\tstats" << '\n';
		std::cout << "\texit" << '\n';

		std::cin >> cmd; // Don't skip over whitespace

		if (cmd == "stats") {
			std::cout << "INFO: " << Logger::getMessageTypeCount(Message::Type::INFO) << '\n';
			std::cout << "WARNING: " << Logger::getMessageTypeCount(Message::Type::WARNING) << '\n';
			std::cout << "ERROR: " << Logger::getMessageTypeCount(Message::Type::ERROR) << '\n';
			std::cout << "CRITICAL: " << Logger::getMessageTypeCount(Message::Type::CRITICAL) << '\n';
		}
		else if (cmd == "exit") {
			break;
		}

		try {
//			INFO, WARNING, ERROR, CRITICAL
			std::string args;
			if (cmd == "info") {
				std::getline(std::cin, args);

				Message msg(Message::Type::INFO, args);
				Configuration::getInstance().getLogger() << msg;
			}
			else if (cmd == "warning") {
				std::getline(std::cin, args);

				Message msg(Message::Type::WARNING, args);
				Configuration::getInstance().getLogger() << msg;
			}
			else if (cmd == "error") {
				std::getline(std::cin, args);

				Message msg(Message::Type::ERROR, args);
				Configuration::getInstance().getLogger() << msg;
			}
			else if (cmd == "critical") {
				std::getline(std::cin, args);

				Message msg(Message::Type::CRITICAL, args);
				Configuration::getInstance().getLogger() << msg;
			}
		}
		catch (std::exception &) {
			std::cout << "Could not process command due to an exception, please try again" << std::endl;
		}
	}

	return 0;
}