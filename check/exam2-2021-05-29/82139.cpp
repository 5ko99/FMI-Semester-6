// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Иван Мишев Михов
// ФН:82139
// Специалност:КН
// Курс:1ви
// Административна група:1ва
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: <GCC>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
# include <stdexcept>
# include <cstddef>
# include <iomanip>
class Command {
protected :
	std::string str;
	std::string command1;
	std::string command2;
	std::size_t argumentsCount;
	
public :
	Command(std::string  str) : str(str),argumentsCount(0) {
		edit();
	};

	std::size_t sizeCount()const {
		return this->argumentsCount;
	}
	std::string operator[] (std::size_t i)const  {
		if (i == 0)
			return this->str;
		else if (i == 1 && i <= this->argumentsCount)
			return this->command1;
		else if (i == 2 && i <= this->argumentsCount)
			return this->command2;
		else
			throw std::invalid_argument("No such element found\n");
	}
private :
	void edit (){
		std::size_t itter1 = 0; //itterator 
		std::size_t itter2 = 0;
		std::size_t temp = str.size();
		for (std::size_t i = 0; i < temp - 1; i++) {
			if (str[i] == ' ' && str[i + 1] != ' ') {
				itter1 = i + 1;
				break;
			}
		}
		for (std::size_t i = itter1; i < temp - 1; i++) {
			if (str[i] == ' ' && str[i + 1] != ' ') {
				itter2 = i + 1;
				break;
			}
		}
		if (itter1 != 0) {
			argumentsCount++;
			std::string tempStr;
			if (itter2 != 0) {
				argumentsCount++;
				for (std::size_t i = itter2; i < temp; i++) {
					command2 += str[i];
				}
			}
			for (std::size_t i = itter1; i < temp; i++) {
				command1 += str[i];
			}
			for (std::size_t i = 0; i < itter1; i++) {

				tempStr += str[i];
			}
			str = tempStr;
		}
	}
};
class Editor {
private :
	std::string path;
	std::fstream file;
	std::size_t sizeOfFile;
public :

	void open() {
		
	}
};
class Processor  {
	
public:
	bool is_valid(const Command& c) {
		if (c[0] == "EXIT")
			return true;
		else if (c[0] == "SIZE")
			return true;
		else if (c[0] == "EDIT")
			return true;
		else if (c[0] == "SHOW")
			return true;
		else
			return false;
	}

};
int main()
{
	
	return 0;
}