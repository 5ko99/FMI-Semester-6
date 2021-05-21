// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Мартин Конов
// ФН: 45804
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: <Visual C++>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Message {
	private:
		string type;
		string description;
	public:
		Message(const string description) {
			
			this->description = description;
		}
		const string operator << (const string type) {
			if (type == "CRITICAL" || type == "INFO" || type == "WARNING" || type == "ERROR") {
				this->type = type;
				return this->type + ':' + ' ' + this->description;
			}
			else {
				throw ;
			}
		}
		const string tp() {
			return this->type;
		}
		const string descr() {
			return this->description;
		}
	};

class Logger {
	static fstream file;
	static size_t critical_count;
	static size_t info_count;
	static size_t warning_count;
	static size_t error_count;
public:
	Logger() {
		file.open("File.txt");
		this->critical_count = 0;
		this->info_count = 0;
		this->warning_count = 0;
		this->error_count = 0;
	}
	void operator << (Message a) {
		this->file.eof();
		this->file.write((a<<a.tp()) + '\n', 1);

		if (a.tp() == "CRITICAL") {
			critical_count += 1;
		}
		else if (a.tp() == "INFO") {
			info_count += 1;
		}
		else if (a.tp() == "WARNING") {
			warning_count += 1;
		}
		else if (a.tp() == "ERROR") {
			this->error_count += 1; 
		}

	}
};

int main()
{


	return 0;
}