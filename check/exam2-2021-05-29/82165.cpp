// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Георги Хърлев
// ФН: 82165
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include <cstdint> //std::uint


#pragma region header
class Command {
protected:
	std::string commands[3];
	short argNums = 0;

	void separateCom(std::string command);
public:
	Command()=default;
	Command(std::string _command);
	std::size_t size() const; //returns arg nums

	std::string operator[](std::size_t index);// from 0
	const std::string operator[](std::size_t index) const;// from 0

};


#pragma endregion _command

class Editor;
#pragma region header

class Processor {
private:
	Editor* editor=nullptr;

public:
	Processor(Editor* _editor);
	//Processor(s)
	bool is_valid(const Command& command);
	void execute(const Command& command);

};

#pragma endregion _processor

#pragma region header

class Editor: protected Command, protected Processor {
private:
	std::fstream file;
	std::size_t fileSize = 0;

public:
	Editor();
	Editor(std::string path);
	void open(std::string path);
	void close();
	std::size_t size() ;
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
	void executeCommand(std::string command);
};


#pragma endregion _editor


#pragma region sourcecode

Editor::Editor() :Processor(this) {

}

Editor::Editor(std::string path) : Command(path), Processor(*this) {
	open(path);

	//even if error is thrown we leave it in valid state
}
void Editor::open(std::string path) {
	file.open(path);
	if (!file.good()) {
		throw std::invalid_argument("No file exists in that path.");
	}
	file.close();
	file.open(path, std::ios::binary | std::ios::in | std::ios::out);
	if (!file.is_open()) {
		throw std::runtime_error("File could not be opened.");
	}
}

void Editor::close() {
	if (file.is_open()) {
		file.close();
	}
}

std::size_t Editor::size() {
	if (!file) {
		throw std::logic_error("No file is opened");
	}
	try {
		file.seekp(0, std::ios::end);
		return file.tellp();
	}
	catch (...) {
		throw std::runtime_error("Error getting size");
	}

}

void Editor::edit(std::size_t offset, std::uint8_t value) {
	if (!file) {
		throw std::logic_error("No file is opened");
	}
	if (offset > size()) {
		throw std::invalid_argument("Offset bigger than size");
	}
	try {
		file.seekp(offset, std::ios::beg);
		file.write((const char*)&value, 1);//uint size =1
	}
	catch (...) {
		throw std::runtime_error("Error setting new value");
	}
}


void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit) {
	if (!file) {
		throw std::logic_error("No file is opened");
	}
	std::size_t fsize = size();
	if (offset > fsize) {
		throw std::invalid_argument("Offset bigger than size");
	}
	if (limit > fsize - offset) {
		limit = fsize - offset;
	}
	file.seekg(offset, std::ios::beg);
	std::uint8_t byte;
	std::size_t i = 0;
	out << std::setfill('0') << std::setw(8) << std::hex << offset << " ";
	while (i < limit) {

		file.read((char*)&byte, 1);
		out << std::setfill('0') << std::setw(2) << std::hex << byte << " ";
		if ((i + 1) % 16 == 0) {
			out << std::endl << std::setfill('0') << std::setw(8) << offset + i << " ";
		}
		i++;
	}
	out << std::dec;//just in case

}

void Editor::executeCommand(std::string command) {
	Command newCommand(command);
	try {
		execute(newCommand);
	}
	catch (const char& e) {//exit
		if (file.is_open()) {
			file.close();
		}
		throw e;
	}
	catch (const std::logic_error& e) {
		e.what();
	}
	catch (const std::exception& e) { //comes from stoi probably
		std::cout << "Invalid command parameters.\n";
	}

}

#pragma endregion _editor



#pragma region sourcecode


Command::Command(std::string _command) {
	separateCom(_command);
}

void Command::separateCom(std::string command) {
	unsigned i = 0;
	unsigned commandStart = 0;
	//std::uint8_t commandNum = 0;
	while (i < command.size() && argNums<3) {
		while (i < command.size() && command[i] == ' ') {
			i++;//white spaces
		}
		commandStart = i; //command
		while (i < command.size() && command[i] != ' ') {
			i++;
		}
		commands[argNums++] = command.substr(commandStart, i - commandStart);
		//i++;
	}
	
}

std::string Command::operator[](std::size_t index) {
	if (index >= 3) {
		throw std::logic_error("Invalid index");
	}
	return commands[index];
}
const std::string Command::operator[](std::size_t index)const {
	if (index >= 3) {
		throw std::logic_error("Invalid index");
	}
	return commands[index];
}

std::size_t Command::size() const {
	return argNums;
}


#pragma endregion _command


#pragma region sourcecode

Processor::Processor(Editor* _editor) :editor(_editor) {

}
bool Processor::is_valid(const Command& command) {
	
	if ((command[0] == "EDIT" || command[0] == "SHOW") && command.size() < 3) {
		return false;
	}
	if (command[0] != "SHOW" && command[0] != "EDIT" && command[0] != "EXIT" && command[0] != "SIZE") {
		return false;
	}

}

void Processor::execute(const Command& command) {
	if (!is_valid(command)) {
		throw std::logic_error("Invalid command.");
	}
	if (command[0] == "EXIT") {
		char e = 'e';
		throw e;
	}
	else if (command[0] == "SHOW") {
		editor->display(std::cout,std::stoi(command[1]), std::stoi(command[2]));
	}//stoi may throw!!! catch later!
	else if (command[0] == "EDIT") {
		editor->edit(std::stoi(command[1]),command[2].front());
		std::cout << "Editing made . Effect will be visible after exiting.\n";
	}
	else if (command[0] == "SIZE") {
		std::cout<<"File size is:"<<editor->size();
	}
	
}

#pragma endregion _process




int main(int argc,char** argv)
{
	std::string commandText;
	Editor editor;
	if (argc > 1)
	{
		try {
			editor.open(argv[1]);
		}
		catch (const std::exception& e) {
			e.what();
			return -1;
		}
	}
	else {
		std::cout << "No path was found in the command line.\n";
			return 1;
	}
	std::cout << "Valid commands:\n";
	std::cout << "EXIT \n";
	std::cout << "SIZE \n";
	std::cout << "EDIT <offset> <byte>\n";
	std::cout << "SHOW <offset> <limit> \n";

	while (true) {

		std::cout << std::endl << ">";
		std::getline(std::cin, commandText);
		
		try {
			editor.executeCommand(commandText);
		}
		catch (const char& e) {//exit
			std::cout << "Exiting program.\n";
			return 1;
		}
		catch (const std::exception& e) {

			e.what();
		}
	}

	return 0;
}