// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Филип Карастоянов
// ФН: 45757
// Специалност: Информатика
// Курс:1
// Административна група:2
// Ден, в който се явявате на контролното:15.05 
// Начален час на контролното: 9:00
// Кой компилатор използвате:  Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
enum MessageTypes
{
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};
class Message
{
public:
	Message() = default;
	Message(MessageTypes _info, std::string _description)
	{
		info = _info;
		description = _description;

	}
	friend std::ostream& operator << (std::ostream& out , Message txt)
	{
		switch (txt.info)
		{
		case INFO: out << "INFO: " << txt.description; break;
		case WARNING:out << "WARNING: " << txt.description; break;
		case ERROR: out << "ERROR: " << txt.description; break;
		case CRITICAL:out << "CRITICAL: " << txt.description; break;
		}
		return out;
	}
	
private:
     MessageTypes info;
	std::string description;
};
class Logger
{
public:
	Logger(std::string _fileAddress)
	{
		
		fileAddress = _fileAddress;
		
		workingFile.open(fileAddress, std::ios::app);
		if (!workingFile.is_open())
		{
			throw std::exception("Error loading file");
		}
		
	}
	friend Logger& operator << (Logger& log , Message txt)
	{
		log.workingFile << txt << '\n';
		return log;
    }
	~Logger()
	{
		workingFile.close();
	}
	void getAddress(std::string _address)
	{
		fileAddress = _address;

	}
	

private:
	std::fstream workingFile;
	std::string fileAddress;
	
};

class Configuration // not finished
{
	Configuration(Configuration& other) = delete;
	Configuration operator =(Configuration& other) = delete;
	Configuration getInstance()
	{
		Configuration config();
		fileName.open("config.txt", std::ios::in);
		if (!fileName.is_open())
		{
			throw std::exception("Error loading file");
		}
		std::string address;
		std::getline(fileName, address);
		log.getAddress(address);
		
	}

private:
	Configuration() = default;
	~Configuration()
	{
		fileName.close();
	}
	std::ifstream fileName;
	static Logger log;
 };
int main()
{
	Message msg(INFO, "log info");
	Message msg1(WARNING, "warning");
	std::cout << msg << std::endl;
	try
	{
		Logger log("log.txt");
		log << msg << msg1;
	}
	catch (std::exception)
	{
		std::cout << "Error loading files!";
	}
	
	
	
	
	return 0;
}