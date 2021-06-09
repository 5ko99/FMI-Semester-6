// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Костадин Недлечев Костадинов
// ФН: 45789
// Специалност: Информатика
// Курс: 1ви
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Command {
private:
	std::string command;
	std::vector<std::string> arguments;
	void splitCommand();
public:
	Command() = delete;
	Command(const std::string);
	std::size_t size() const;
	Command operator[](const std::size_t index) const;
};

void Command::splitCommand() {
	size_t index = 0;
	std::string buffer;
	while (command[index] != '\0') {
		if(command[index] = ' ') {
			if(command[index + 1] != ' ') {
				arguments.push_back(buffer);
				buffer.clear();
			}
		}
		buffer.push_back(command[index]);
	}
	if (!buffer.empty()) {
		arguments.push_back(buffer);
		buffer.clear();
	}
}

Command::Command(const std::string command) {
	this->command = command;
	splitCommand();
}

std::size_t Command::size() const {
	return arguments.size();
}

Command Command::operator[](const std::size_t index) const{
	return arguments[index];
}
class Editor {
	std::fstream file;
	size_t file_size;
public:
	Editor();
	Editor(const std::string path);
	void open(const std::string path);
	void close();
	size_t size() const;
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
};

Editor::Editor() {
	file_size = 0;
}

Editor::Editor(const std::string path) {
	open(path);
	file.seekg(std::ios::end);
	file_size = file.tellg();
	file.seekg(std::ios::beg);
}

void Editor::open(const std::string path) {
	if (file) close();
	file.open(path, std::ios::binary);
	if (!file) throw std::invalid_argument("File couldn't be opened!");
}

void Editor::close() {
	if (!file) throw std::invalid_argument("No file opened!");
	file.close();
	file_size = 0;
}

size_t Editor::size() const {
	return file_size;
}

void Editor::edit(std::size_t offset, std::uint8_t value) {
	if(offset >= file_size) throw std::invalid_argument("Invalid offset");
	file.seekp(offset*sizeof(value), std::ios::beg);
	file.write((const char*)&value, sizeof(value));
}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit) {
	if(offset >= file_size || offset + limit >= file_size) throw std::invalid_argument("Invalid offset");
	file.seekg(offset*sizeof(std::uint8_t), std::ios::beg);
	char* content = new char[limit+1];
	content[limit] = '\0';
	file.read(content,limit);
	out << content;
	delete[] content;
}

class Processor {
	Editor document;
	bool isEqual(std::string str_1, std::string str_2);
public:
	Processor() = delete;
	Processor(const std::string path);
	bool isValid(const Command command);
	bool execute(const Command command);
	void run();
};

bool Processor::isEqual(std::string str_1, std::string str_2) {
	if (str_1 == str_2) return true;
	if (str_1.size() != str_2.size()) return false;
	size_t size = str_1.size();
	for(size_t i = 0; i < size; i++) {
		if (str_1[i] != str_2[i]) return false;
	}
	return true;
}

size_t strToSize_T(std::string str) {
	size_t size = str.size();
	size_t buffer = 0;
	for(size_t i = 0; i < size; i++) {
		buffer *= 10;
		buffer += (str[i] + '0');
	}
	return buffer;
}

uint8_t strToUnt8_T(std::string str) {
	size_t size = str.size();
	uint8_t buffer = 0;
	for(size_t i = 0; i < size; i++) {
		buffer *= 10;
		buffer += (str[i] + '0');
	}
	return buffer;
}

Processor::Processor(const std::string path) {
	document.open(path);
}

bool Processor::isValid(const Command command) {
	if (isEqual(command[0], "SIZE")) {
		if(command.size() == 1) return true;
	} else if (isEqual(command[0], "EDIT")) {
		if(command.size() == 3) return true;
	} else if (isEqual(command[0], "SHOW")) {
		if(command.size() == 3) return true;
	} else if (isEqual(command[0], "EXIT")) {
		if(command.size() == 1) return true;
	}
	return false;
}

bool Processor::execute(const Command command) {
	if (!strcmp(command[0], "EXIT")) {
		return false;

	} else if (!strcmp(command[0], "SIZE")) {
		std::cout << document.size();

	} else if (!strcmp(command[0], "EDIT")) {
		try {
			document.edit(strToSize_T(command[1]), strToUnt8_T(command[2]));
		} catch (std::exception &e) {
			std::cerr << e.what() << '\n';
		}
		

	} else if (!strcmp(command[0], "SHOW")) {
		try {
			document.display(std::cout, strToSize_T(command[1]), strToSize_T(command[2]));
		} catch (std::exception &e) {
			std::cerr << e.what() << '\n';
		}
	}
	return true;
}

void Processor::run() {
	std::string input;
	bool isRunning = 1;
	do {
		getline(std::cin, input);
		Command command(input);
		if (isValid(command)) {
			isRunning = execute(command);
		}
	} while (isRunning);
}


int main(int argc, char* argv[]) {
	if(argc <= 1) {
		std::cerr << "Not enough arguments!\nMust include path to file!";
		return 1;
	}
	try {
		Processor pro(argv[1]);
		pro.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << '\n';
		return 2;
	}
	return 0;
}