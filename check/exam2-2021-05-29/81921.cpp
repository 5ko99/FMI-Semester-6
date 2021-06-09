// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име:
// ФН: 81921
// Специалност: Компютърни науки
// Курс:3
// Административна група:2 
// Ден, в който се явявате на контролното: 29.05.2021г. 
// Начален час на контролното: 9:05
// Кой компилатор използвате: Visual studio
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Command {
private:
	std::string command;
	std::string arrayOfStrings[3];
public:

	Command(std::string c) {
		this->command = c;
	}

	std::string getCommand() {
		return this->command;
	}

	int getArrayStorage() {
		return this->arrayOfStrings->size();
	}

	void commandDivider() {
		int k = 0;
		std::string commandName = "";
		for (int i = 0; i < command.size(); i++) {
			if (this->command[i] == ' ') {
				this->arrayOfStrings[k] = commandName;
				commandName = "";
				k++;
				continue;
			}
			else {
				commandName = commandName + this->command[i];
				continue;
			}
		}
		this->arrayOfStrings[2] = commandName;
	}

	std::size_t size() const {
		int counter = 0;
		for (int i = 0; i < this->command.size(); i++) {
			if (this->command[i] == ' ') {
				counter++;
			}
			else if (this->command[i] == '"') {
				counter++;
			}
		}
		return counter;
	}

	std::string operator[](std::size_t index) {
		if (index == 0) {
			return this->arrayOfStrings[0];
		}
		else if (index == 1) {
			return this->arrayOfStrings[1];
		}
		else if (index == 2) {
			return this->arrayOfStrings[2];
		}
		else {
			std::cout << "not available command" << std::endl;
		}
	}
};
class Editor {
private:
	std::fstream file;
	std::size_t sizeOfFile;
	const char* path;
public:
	Editor(const char* path, std::ios_base::openmode mode) : path(path) {
		this->file.open(path, mode);
	}
	void open() {
		this->file.open(this->path, std::ios_base::binary | std::ios_base::ate);
		if (!file) {
			throw "Couldn't open the file";
		}
		else {
			std::cout << "File opened successfully!" << std::endl;
		}
	}
	void close() {
		this->file.close();
	}

	size_t getFileSize() {
		file.seekp(0);
		
	}

	void edit(std::size_t offset, std::uint8_t value) {
		file.write();
	}

};

class Processor : public Editor {
public:
	bool is_valid(Command c) {
		if (c.getCommand() == "EXIT") {
			return true;
		}
		else if (c.getCommand() == "SIZE") {
			return true;
		}
		else if (c.getArrayStorage() == 3) {
			if (c.operator[](0) == "EDIT" || c.operator[](0) == "SHOW") {
				return true;
			}
		}
		else {
			return false;
		}
	}

	void execute(std::string name, std::string param1, std::string param2) {

	}

};



int main() {
	Command c("Edit 50 6");
	c.commandDivider();
	std::cout<< c.size() <<std::endl;
	std::cout << c.operator[](2) << std::endl;
	return 0;
}
