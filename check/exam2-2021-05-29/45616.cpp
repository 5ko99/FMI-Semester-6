// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Галя Додова
// ФН: 45616
// Специалност: Информатика
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 29.5.2021г.
// Начален час на контролното: <9:00>
// Кой компилатор използвате: < Visual C++>
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
#include <vector>
#include <fstream>
int main()
{
	
	std::string file;
	std::cout << "Enter the name of the file: ";
	std::cin >> file;
	editor edd(file);
	std::ofstream File(file);
	edd.open();
	if (!File.is_open()) {
		std::cout << "Could not open the file!";
		return -1;
	} std::string command;
	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
		Command com(command);
		com.separate();
		processor pro;
		pro.execute(com.getCom());
	} while (command == "EXIT");
	edd.close();
	return 0;
}

class Command {
public:
	Command(std::string command) {
		this->command = command;
	} Command() {
		command = " ";
	}
	void separate() {
		for (size_t i = 0; i < command.size(); ++i) {
			while (command[i] != ' ') {
				com[i] = command[i];
			} ++i;
			for (size_t j = 0; command.size() - i; ++j) {
				while (command[i] != ' ') {
					arg[j] = command[i];
				}
			}
		}
	}
	std::string getCom() const {
		return com;
	}
	std::size_t size() const {
		return arg.size();
	}
	Command& operator[](std::size_t size) {
		if (size == 0) {
			&this->com;
		}	else {
			&this->arg[size - 1];
		}
		return *this;
	}
private:
	std::string command;

	std::string com;
	std::vector <std::string> arg;
};


class processor:public editor  {
public:
	processor() {

	}
	bool is_valid(std::string command) {
		int size = 0;
		for (size_t i = 0; i < command.size(); ++i) {
			if (isalpha(command[i])==true) {
				++size;
			}
		} if (size == command.size()) {
			return true;
}
		return false;
	}
	void execute(std::string command) {
		try {
			if (is_valid(command) == true) {	
					if (command == "SIZE") {
						std::cout << size();
					}
					else if (command == "EDIT") {
						std::cout << "Enter possition and information to write in file: ";
						size_t possition;
						std::cin >> possition;
						std::uint8_t offset;
						std::cin >> offset;
						edit(possition,offset);
					}
					else if (command == "SHOW") {
						std::cout << "Where to save your information?";
						std::string filepath;
						std::cin >> filepath;
						std::ofstream outFile(filepath);
						std::cout << "Enter possition and limmit";
						std::uint8_t offset;
						std::cin >> offset;
						size_t limmit;
						std::cin >> limmit;
						display(outFile, offset,limmit);
					}
					else {
						std::cout << "There is no such a command!";
					}
			}	else {
				throw command;
			}
		}
		catch(std::string command){
			std::cout << "Your command is incorrect.";
		}
	}
private:

};

class editor {
public:
	editor(std::string path) {
		this->path = path;
	}
	editor() {
		path = " ";
	}
	void open() {
		newFile.open(path, std::ios::binary);
		fileSize=newFile.width();
	}
	void close() {
		newFile.close();
	}
protected:
	std::size_t size() const {
		return fileSize;
	}
	void edit(std::size_t offset, std::uint8_t value) {
		if (fileSize <= offset) {
			newFile.write((char*)value, offset);
		}	else {
			std::invalid_argument("Invalid argument!");
		}
	}
	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		if (fileSize <= offset) {
			for (size_t i = offset; i < limit; ++i) {
				newFile.seekp(i);
			}
		}	else {
			std::invalid_argument("Invalid argument!");
		}
	}

private:
	std::string path;
	std::size_t fileSize;
	std::ofstream newFile;
};