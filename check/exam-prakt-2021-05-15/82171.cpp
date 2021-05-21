// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Иван Тодоров Иванов
// ФН: 82171
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 15/5/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: gcc
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum MessageType {
	info,
	warning,
	error,
	criticalError
};

class Message {
	private:
		MessageType type;
		std::string description;
	public:
		Message(MessageType type, std::string description) :
			type(type), description(description) {
				;
			}

		const MessageType getType() const {
			return type;
		}

		friend std::ostream& operator<<(std::ostream& os, const Message& message) {
			switch (message.type) {
				case 0: os << "Info: "; break;
				case 1: os << "Warning: "; break;
				case 2: os << "Error: "; break;
				case 3: os << "Critical Error: "; break;
			}
			os << message.description << std::endl;
			return os;
		}
};

class Logger {
	private:
		static unsigned int numInfo;
		static unsigned int numWarning;
		static unsigned int numError;
		static unsigned int numCError;

		std::string fileName;
	public:
		Logger () {
			;
		}

		Logger(std::string fileName) : fileName(fileName) {
			;
		}

		Logger (const Logger& logger) : fileName(logger.fileName) {
			;
		}

		Logger& operator=(const Logger& logger) {
			if (this == &logger) {
				return *this;
			}

			fileName = logger.fileName;

			return *this;
		}

		static const unsigned int getNumInfo() {
			return numInfo;
		}

		static const unsigned int getNumWarning() {
			return numWarning;
		}

		static const unsigned int getNumError() {
			return numError;
		}

		static const unsigned int getNumCError() {
			return numCError;
		}

		friend Logger& operator<<(Logger& logger, const Message& message) {
			std::fstream file(logger.fileName, std::ios::app);
			if(!file) {
				throw std::exception();
			}

			file << message;

			switch (message.getType()) {
				case 0: ++numInfo; break;
				case 1: ++numWarning; break;
				case 2: ++numError; break;
				case 3: ++numCError; break;
			}

			file.close();
			
			return logger;
		}

		~Logger() {
			;
		}
};

unsigned int Logger::numInfo = 0;
unsigned int Logger::numWarning = 0;
unsigned int Logger::numError = 0;
unsigned int Logger::numCError = 0;

class Configuration {
	private:
		Logger l;
		std::string configFileAddress;
		static bool created;
		Configuration(std::string configFileAddress) : configFileAddress(configFileAddress) {
		}

		void splitMessage(std::string message, std::string& typeAsString, std::string& description) {
			std::size_t spaceIndex;
			bool spaceFound = false;
			for (std::size_t i = 0; i < message.size(); ++i) {
				if(message[i] == ' ' && spaceFound == false) {
					if (i == 0) {
						throw std::exception();
					}

					spaceFound = true;
					typeAsString = message.substr(0, i);
					if (typeAsString == "Critical") {
						spaceFound = false; // continue searching for Error as the type is Critical Error
					}
				}
				if (spaceFound == true && message[i] != ' ') {
					description = message.substr(i, message.size() - i);
					break;
				}
			}
		}
	public:
		static void InitializeConfiguration(std::string address) {
			if (created == false) {
				created = true;

				Configuration c(address);
				try {
					c.setUpLogger();
				}
				catch (...) {
					std::cout << "cannot setup logger.";
					throw std::exception();
				}
				c.readInput();
			}
			else {
				throw std::exception();
			}
		}

		Configuration() = delete;
		Configuration(const Configuration& ) = delete;
		Configuration& operator=(const Configuration& ) = delete;

		void setUpLogger() {
			std::fstream file(configFileAddress, std::ios::in);
			if (!file) {
				throw std::exception();
			}

			std::string address;
			file >> address;

			if (address != "") {
				Logger sourceLogger(address);
				l = sourceLogger;
			}
			else {
				throw std::exception();
			}
		}

		void readInput() {
			std::string command = "";
			std::string typeAsString;
			std::string description;
			MessageType type;

			while (true) {
				std::cin >> command;
				
				if (command == "END") {
					break;
				}

				try {
					splitMessage(command, typeAsString, description);
					std::cout << command <<std::endl;
					std::cout << typeAsString <<std::endl;
					std::cout << description <<std::endl;
				}
				catch(...) {
					std::cout << "Command cannot begin with space, input a new one." << std::endl;
					continue;
				}

				if (typeAsString == "Info") {
					type = info;
				}
				else if (typeAsString == "Warning") {
					type = warning;
				}
				else if (typeAsString == "Error") {
					type = error;
				}
				else if (typeAsString == "Critical Error") {
					type = criticalError;
				}
				else {
					std::cout << "Invalid command. OnlyInfo/Warning/Error/Critical Error/END are supported). Enter a new one:" << std::endl;
					continue;
				}

				Message message(type, description);

				l << message;
			}
		}

		Configuration* operator*() {
			return this;
		}
};

bool Configuration::created = false;

int main(int argc, char* argv[])
{
	std::string address = "config.txt";
	if (argc > 1) {
		address = argv[1];
	}
	Configuration::InitializeConfiguration(address);

	return 0;
}