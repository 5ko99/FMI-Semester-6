// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Александър Жеков
// ФН: 82135
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 15/5/2021
// Начален час на контролното: 9
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <cstring>
#include <fstream>

class Message {
	private:
		std::string type;
		std::string description;

	public:
		Message(std::string Type, std::string Desc) {
			type = Type;
			description = Desc;
		}

		std::string getType() const{
			return type;
		}

		std::string getDesc() const{
			return description;
		}
};

class Logger {
	private:
		std::string logFile;
		unsigned int numInfo = 0;
		unsigned int numWarning = 0;
		unsigned int numError = 0;
		unsigned int numCritical = 0;

	public:
		void set_LogFile(const std::string file) {
			logFile = file;
		}

		void operator<<(const Message msg) {
			std::fstream logFile(logFile, std::ios::out, std::ios::app);
			if (!logFile.is_open()) {
				if (strcmp(msg.getType().c_str(), "info")) {
					++numInfo;
					logFile << "INFO:" << msg.getDesc() << '\n';
				}
				else if (msg.getType().c_str() == "warning") {
					++numWarning;
					logFile << "WARNING:" << msg.getDesc() << '\n';
				}
				else if (msg.getType().c_str() == "error") {
					++numError;
					logFile << "ERROR:" << msg.getDesc() << '\n';
				}
				else if (msg.getType().c_str() == "critical error") {
					++numCritical;
					logFile << "CRITICAL:" << msg.getDesc() << '\n';
				}
				else {
					std::cerr << "Message can only be info|warning|error|critical error!\n";
					std::cerr << "Please enter a valid message!\n";
				}
			}
			else {
				throw "File could not be opened";
			}
		}

		void printMessages() {
			std::cout << "There have been " << numInfo << " information messages!\n";
			std::cout << "There have been " << numWarning << " warning messages!\n";
			std::cout << "There have been " << numError << " error messages!\n";
			std::cout << "There have been " << numCritical << " critical error messages!\n";
		}
};

class Configuration {
	private:
		std::string dest;
		Logger log;

	public:
		Configuration(std::string destination) {
			dest = destination;
			log.set_LogFile(dest);
		}

		Logger getLog() const {
			return log;
		}
};

int main(int argc, char* argv[])
{
	std::string logFileDest;
	if (argc == 1) {
		logFileDest = "logs.txt";
	}
	else if (argc == 2) {
		logFileDest = argv[1];
	}
	else {
		std::cerr << "Too many arguments!\n";
		return 1;
	}

	Configuration config(logFileDest);
	bool exitFlag = false;
	std::string typeMsg;
	std::string descMsg;

	std::cout << "All messages you enter will be counted and saved in the file you specified!\n";
	std::cout << "Write num_msg for number of all messages by type!\n";
	std::cout << "Write exit to leave the application!\n";

	while (!exitFlag) {
		std::cin >> typeMsg;
		if (typeMsg == "exit") {
			exitFlag = true;
		}
		else if (typeMsg == "num_msg") {
			config.getLog().printMessages();
		}
		else {
			std::cin >> descMsg;
			Message buffer(typeMsg, descMsg);
			try {
				config.getLog() << buffer;
			}
			catch (const char* error) {
				std::cerr << "The message could not be logged!\n";
				exitFlag = true;
			}
		}
	}
	return 0;
}