// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Александър Жеков
// ФН: 82135
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 29/5/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const std::size_t MAX_NUM_ARGS = 3;
const std::size_t MAX_COMMAND_SIZE = 10;

class Command {
private:
	int numArguments;
	std::string arguments[MAX_NUM_ARGS];

public:
	Command(const char* command);

	std::size_t size() const;
	std::string operator[](const size_t index);
};

Command::Command(const char* command) {
	char buffer[MAX_COMMAND_SIZE];
	int i = 0;
	numArguments = 0;

	while (i < strlen(command)) {
		if (command[i] != ' ' && command[i] != '\0') {
			buffer[i] = command[i];
			++i;
		}
		else if(command[i] == ' ') {
			if (numArguments == MAX_NUM_ARGS) {
				break;
			}
			else {
				buffer[i] = '\0';
				arguments[numArguments] = buffer;
				++numArguments;
				++i;
				strcpy(buffer, " ");
			}
		}
	}
	buffer[i] = '\0';
	arguments[numArguments] = buffer;
	++numArguments;
}

std::size_t Command::size() const{
	return numArguments;
}

std::string Command::operator[](const size_t index) {
	return arguments[numArguments - 1];
}

class processor {
	private:

	public:
		bool is_valid(Command& comm) const;
		void execute(Command& comm);
};

bool processor::is_valid(Command& comm) const {
	if (comm[0] == "EXIT" || comm[0] == "SIZE") {
		return true;
	}

	if (comm[0] == "SHOW") {
		return false;
	}

	if (comm[0] == "EDIT") {
		return false;
	}

	return false;
}

void processor::execute(Command& comm) {
	if (comm[0] == "EXIT") {
	
	}

	if (comm[0] == "SIZE") {
		
	}

	if (comm[0] == "SHOW") {
		
	}

	if (comm[0] == "EDIT") {
		
	}
}

class editor {
	private:
		std::string dir;
		std::fstream file;

	public:
		editor(std::string directory) : dir(directory) 
		{
			open();
		}
		~editor();

		void open();
		void close();
		std::size_t size() const;
		void edit(std::size_t offset, std::uint8_t value);
		void display(std::ostream& out, std::size_t offset, std::size_t limit) const;
};

void editor::open() {
	file.open(dir, std::ios::binary);
	if (!file.is_open()) {
		throw "File could not be opened!";
	}
}

void editor::close() {
	if (file.is_open()) {
		file.close();
	}
}

std::size_t editor::size() const {
	return 10;
}


void editor::edit(std::size_t offset, std::uint8_t value) {

}

void editor::display(std::ostream& out, std::size_t offset, std::size_t limit) const {

}

editor::~editor() {
	if (file.is_open()) {
		file.close();
	}
}

int main()
{
	Command comm("one two three");
	std::cout << comm.size();
	return 0;
}