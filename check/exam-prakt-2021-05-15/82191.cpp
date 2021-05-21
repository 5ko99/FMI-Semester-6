// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Божидар Иванов
// ФН: 82191
// Специалност: КН
// Курс: Първи
// Административна група: Трета
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: clang
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum class MessageType
{
	INFO,
	WARNING,
	ERROR,
	CRITICAL,
};

class Message
{
public:
	Message(MessageType type, const std::string& message) : m_MessageType(type), m_MessageDescription(message) {}
public:
	static std::string MessageTypeToString(MessageType type)
	{
		switch(type)
		{
			case (MessageType::INFO):     return "INFO";
			case (MessageType::WARNING):  return "WARNING";
			case (MessageType::ERROR):    return "ERROR";
			case (MessageType::CRITICAL): return "CRITICAL";
		}
		return std::string();
	}
	
	static MessageType MessageTypeFromString(const std::string& type)
	{
		if (type == "info") 	return MessageType::INFO;
		if (type == "warn") 	return MessageType::WARNING;
		if (type == "error")    return MessageType::ERROR;
		if (type == "critical") return MessageType::CRITICAL;
		
		std::cout << "Unknown message type. Using default info type." << std::endl;
		return MessageType::INFO;
	}
	
	const std::string& GetMessage() const { return m_MessageDescription; }
	MessageType GetType() const { return m_MessageType; }
	
private:
	friend std::ostream& operator<<(std::ostream& stream, const Message& message);
	std::string m_MessageDescription;
	MessageType m_MessageType;
};

class ioexception : public std::exception
{
public:
	ioexception(const std::string& message) : m_Message(message) { }

    virtual const char* what() const noexcept { return m_Message.c_str(); };
private:
	std::string m_Message;
};

class Logger
{
public:
	Logger(const std::string& filepath)
	{
		m_Stream = std::ofstream(filepath, std::ios::app);
		if (!m_Stream.is_open()) throw ioexception("Unable to open logger");
	}
	
	~Logger() { m_Stream.close(); }
	
public:
	static uint64_t GetMessageCount() {
		return s_MessageCounts[(uint32_t)MessageType::INFO] +
			   s_MessageCounts[(uint32_t)MessageType::WARNING] +
			   s_MessageCounts[(uint32_t)MessageType::ERROR] +
			   s_MessageCounts[(uint32_t)MessageType::CRITICAL];  }
	static uint64_t GetMessageCount(MessageType type) { return s_MessageCounts[(uint32_t)type]; }
	
private:
	friend Logger& operator<<(Logger& logger, const Message& message);
	std::ofstream m_Stream;
	static uint64_t s_MessageCounts[4];
};

uint64_t Logger::s_MessageCounts[4] = { 0, 0, 0, 0 };

class Configuration
{
public:
	Configuration() = default;
	~Configuration() { delete m_Logger; }
	Configuration(const Configuration& other) = delete;
	Configuration& operator=(const Configuration& other) = delete;
	
	void LoadConfig(const std::string& filepath)
	{
		std::ifstream in(filepath);
		if (!in.is_open()) throw ioexception("Unable to open config.");
		std::string logPath;
		in >> logPath;
		in.close();
		m_Logger = new Logger(logPath);
	}
	
public:
	static Configuration& Get()
	{
		static Configuration s_Instance;
		return s_Instance;
	}
	
	Logger& GetLogger() { return *m_Logger; }
	const std::string& GetConfigPath() const { return m_ConfigPath; }
private:
	std::string m_ConfigPath;
	Logger* m_Logger;
};

#define LOG(type, message) Configuration::Get().GetLogger() << Message(type, message);

std::ostream& operator<<(std::ostream& stream, const Message& message)
{
	stream << Message::MessageTypeToString(message.m_MessageType) << ": " << message.m_MessageDescription;
	return stream;
}

Logger& operator<<(Logger& logger, const Message& message)
{
	Logger::s_MessageCounts[(uint32_t)message.GetType()]++;
	logger.m_Stream << message << "\n";
	return logger;
}

int main(int argc, const char** argv)
{
	std::string path = "config.txt";
	if (argc > 1)
		path = argv[1];
	
	try
	{
		Configuration::Get().LoadConfig(path);
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		return 0;
	}

	std::cout << "==============================================================" << std::endl;
	std::cout << "     quit - Exit application " << std::endl;
	std::cout << "     <MessageType> <Message> - log a message " << std::endl;
	std::cout << "     valid message types are: info, warn, error, critical" << std::endl;
	std::string messageType, message;
	while (true)
	{
		std::cin >> messageType;
		if (messageType == "quit") break;
		MessageType type = Message::MessageTypeFromString(messageType);
		std::cin >> message;
		LOG(type, message);
	}
	return 0;
}

