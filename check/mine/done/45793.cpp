// Kala
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

enum msgType {
	info,
	warning,
	error,
	criticalError
};

class Message {
public:
	Message(msgType typ, std::string des) : type(typ), description(des) {}
	
	friend std::ostream& operator<<(std::ostream& out, const Message& msg) 
	{
		if (msg.type == info) {
			out << "INFO: " << msg.description;
		}
		if (msg.type == warning) {
			out << "WARNING: " << msg.description;
		}
		if (msg.type == error) {
			out << "ERROR: " << msg.description;
		}
		if (msg.type == criticalError) {
			out << "CRITICAL ERROR: " << msg.description;
		}
		return out;
	}
	msgType getType() const 
	{
		return type;
	}

private:
	const msgType type;
	const std::string description;
};

class Logger {
public:
	Logger() {
		outputFileName = "logs.txt";
		info_cnt = 0;
		warning_cnt = 0;
		error_cnt = 0;
		criticalError_cnt = 0;
	}
	Logger(std::string outputFileName) 
	{
		this->outputFileName = outputFileName;
		info_cnt = 0;
		warning_cnt = 0;
		error_cnt = 0;
		criticalError_cnt = 0;
	}

	Logger& operator<<(const Message& msg) 
	{
		std::ofstream oFile(outputFileName, std::ios_base::app);
		if (!oFile) {
			std::cerr << "Cannot open file";
			return *this;
		}
		oFile << msg << "\n";
		oFile.close();

		if (msg.getType() == info) {
			info_cnt++;
		}
		if (msg.getType() == warning) {
			warning_cnt++;
		}
		if (msg.getType() == error) {
			error_cnt++;
		}
		if (msg.getType() == criticalError) {
			criticalError_cnt++;
		}
		return *this;
	}

	void printMsgCnt() 
	{
		std::ofstream oFile(outputFileName, std::ios_base::app);
		if (!oFile) {
			std::cerr << "Cannot open file";
			return;
		}
		oFile <<"\nMessage count:\n"
			  << "Infos: " << info_cnt << "\n"
		      << "Warnings: " << warning_cnt << "\n"
			  << "Errors: " << error_cnt << "\n"
		      << "Critical errors: " << criticalError_cnt << "\n\n";
		oFile.close();
	}

private:
	std::string outputFileName;
	unsigned info_cnt;
	unsigned warning_cnt;
	unsigned error_cnt;
	unsigned criticalError_cnt;
};

class Configuration {
public:
	Configuration(std::string configPath) {
		config.open(configPath);
		if (!config) {
			std::cerr << "Couldn't open file\n";
			throw 1;
		}

		std::string temp;
		config >> temp;
		log = Logger(temp);
		config.close();
	}
	
private:
	std::ifstream config;
	Logger log;
};

int main(const int& argc, const char* argv)
{
	//Message bruh(info, "bruh");
	//std::cout << bruh;
	//Logger log("smth.txt");
	//Message a(info, "something");
	//Message b(warning, "chilling");
	//log << a << b;
	//log.printMsgCnt();
	//log << b << a;
	//log.printMsgCnt();
	//if (!argc) {
	//	try {
	//		Configuration("config.txt");
	//	}
	//	catch (...) {
	//	
	//	}
	//}
	//else {
	//	try {
	//		Configuration(argv);
	//	}
	//	catch (...) {
	//	
	//	}

	

	return 0;
}