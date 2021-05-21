// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Константин Кондов
// ФН: 82128
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 5.15.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
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



#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum Mes {
	info,
	warning,
	error,
	critical
};



class Message {
private:

	Mes mes;
	std::string description;

public:
	Message(const char* error, const char* desc) : description(desc) {

		if (error != "error" || error != "warning" || error != "critical" || error != "info") {
			throw std::invalid_argument("You have entered invalid message");
		}

		if (error == "info") this->mes = Mes::info;

		if (error == "warning") this->mes = Mes::warning;

		if(error == "error") this->mes = Mes::error;

		if (error == "critical") this->mes = Mes::critical;
	


	}
	std::ostream& operator<<(std::ostream& out ,const Message& other) {


		if (this->mes == Mes::info)  out <<"INFO: " << this->description << std::endl;

		if (this->mes == Mes::warning) out << "WARNING: " << this->description << std::endl;
			
		if (this->mes == Mes::error) out << "ERROR: " << this->description << std::endl;

		if (this->mes == Mes::critical) out << "ERROR: " << this->description << std::endl;
		
		
	}
	

};

class Logger {
	std::ofstream log;
	unsigned int info_count;
	unsigned int warning_count;
	unsigned int error_count;
	unsigned int critical_count;

	Logger() : info_count(0), warning_count(0), error_count(0), critical_count(0) {
		std::ofstream log("log.txt");
		if (!log) {
			throw std::runtime_error("Log file didnt open succesfully");
		}
	}

	std::ostream& operator<<(const Logger& log ,const Message& other) {

		std::ofstream log("log.txt");
		log << other;
		log << "Number of info: " << info_count;
		log << "Number of warnigns: " << warning_count;
		log << "Number of error_count: " << error_count;
		log << "Number of critical_count: " << critical_count;

	}
};



int main(int arc , char** arcv)
{
	
	return 0;
}