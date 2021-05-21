// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име:Иван
// ФН:82139
// Специалност:КН
// Курс:1ви
// Административна група:1ва
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: < GCC >
//


#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
# include <fstream>
# include <stdexcept>
enum Type {
	INFO,
	WARNING,
	ERROR,
	CRITICAL
}; 
class Message {
private :
	Type e;
	std::string description;
public :
	Message(const Type& e, std::string description) : e(e), description(description) {};
	friend std::ostream& operator<<(std::ostream &os, const Message&);
	Type getType()const { return this->e; }
	std::string getDescription()const{ return this->description; }
};

std::ostream& operator<<(std::ostream& os, const Message& m) {
	std::string temp;

	
	switch (m.e) {
	case INFO: temp = "INFO"; break;
	case WARNING: temp = "WARNING"; break;
	case ERROR: temp = "ERROR"; break;
	case CRITICAL: temp = "CRITICAL"; break;
	}
	os << temp << ": "<< m.description;
	return os;
}
class Logger {
private :
	static unsigned int  countInfo ;
	static unsigned int  countWarninig;
	static unsigned int  countError;
	static unsigned int  countCritical;
	
	std::string file;
public :
	Logger(const std::string & s) : file(s) {
		if (s.empty())
			throw std::invalid_argument("Can not input file with no name");
		
		this->countInfo = 0;
		  countWarninig=0;
		  countError = 0;
		  countCritical = 0;
	}
	void setFile(const std::string &file) {
		this->file = file;
	}
	friend std::ofstream& operator<<(const Logger&,const Message &);
	
 };
std::ofstream& operator<<(const Logger& a, const Message& b) {
	std::ofstream OU(a.file);
	std::string temp;

	if (!OU) {
		throw std::runtime_error("Could not open file");
	}
	switch (b.getType()) {
	case INFO: temp = "INFO", a.countInfo++; break;
	case WARNING: temp = "WARNING",a.countWarninig++; break;
	case ERROR: temp = "ERROR",a.countError++; break;
	case CRITICAL: temp = "CRITICAL",a.countCritical++; break;
	}
	OU << temp << b.getDescription();
	OU.close();
	
}
class Configuration {
private :
	std::string file;
	Logger t;
public :
	Configuration(const std::string& file, const Logger& t) : file(file), t(t) {
		std::ifstream in(file);
		if (!in) {
			throw std::runtime_error("Could not open file");
		}
		std::string temp;
		in >> temp;
		this->t.setFile(temp);
	}
	
	friend std::istream& operator>>(std::istream& is, const Configuration&);
};

int main()
{
	
	return 0;
}