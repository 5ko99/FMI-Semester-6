// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Карина Христова
// ФН: 82133
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: MSVC (Visual C++)
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
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Command
{
	std::string text;
	std::string commandName = "";
	std::vector<std::string> arguments;
	std::size_t argumentsCount = 0;

	void breakDownCommandText(std::string text)
	{
		std::string currString;
		std::size_t wordCount = 0;
		std::size_t stringLen = text.length();
		bool foundACharacter = false;
		
		for (size_t pos = 0; pos < stringLen; pos++)
		{
			if (text[pos] == ' ') {
				if (wordCount == 0) {
					commandName = currString;
				}
				else {
					arguments.push_back(currString);
				}

				if (foundACharacter != false) {
					wordCount++;
					currString = "";
				}
				
				pos++;
				continue;
			}
			else {
				foundACharacter = true;
				currString += text[pos];
			}
		}

		this->argumentsCount = wordCount;
	}
public:
	Command(std::string text) : text(text)
	{
		breakDownCommandText(text);
	}

	std::size_t size() const
	{
		return argumentsCount;
	}

	std::string operator[](std::size_t size)
	{
		if (size == 0) {
			return commandName;
		}
		else {
			return arguments[size - 1];
		}
	}

	std::string showCommandName()
	{
		return this->commandName;
	}

};

class Editor
{
private:
	std::size_t fileSize;
	std::fstream myFile;
public:
	Editor(std::string path) //should open the file 
	{
		open(path);
	}

	~Editor()
	{
		if (myFile.is_open())
			close();
	}

	void open(std::string path)
	{
		myFile.open(path, std::ios_base::binary);
		if (!myFile) {
			throw std::exception("Could not open file!\n");
		}

		std::size_t size = myFile.tellg();
		this->fileSize = size;
	}

	void close()
	{
		myFile.close();
	}

	std::size_t size()
	{
		return this->fileSize;
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		if (offset > this->fileSize)
			throw std::invalid_argument("Offset position is after the end of the file!");

		myFile.seekp(offset, std::ios_base::beg);
		char s = (char)value;
		const char* cp = &s;

		myFile.write(cp, offset);

		std::size_t size = myFile.tellg(); //find the new size
		this->fileSize = size;
	}

	std::ostream& display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (offset > this->fileSize)
			throw std::invalid_argument("File size is: " + this->fileSize);

		int printedCount = 0;
		char * toShow;

		while (myFile) {
			if (printedCount == limit)
				break;
			myFile.read(toShow,offset);
			printedCount++;
			out << std::setfill('0') << std::setw(8) << std::hex << toShow;
		}

		return out;
	}
};

class Processor
{
	//EXIT / SIZE  / EDIT <offset> <byte> / SHOW <offset> <limit> 
	bool is_valid(Command command)
	{
		std::string name = command.showCommandName();
		if (name == "EXIT" || name == "SIZE" || name == "EDIT" || name == "SHOW") {
			if (name == "EDIT" && command.size() != 2) {
				return false;
			}
			else if (name == "SHOW" && command.size() != 2) {
				return false;
			}
			return true;
		}
		else {
			return false;
		}
	}
public:
	void execute(Command command, Editor myEditor)
	{
		if (is_valid(command)) {
			std::string name = command.showCommandName();

			if (command.showCommandName() == "EXIT") {
				myEditor.close();
			}
			else if (command.showCommandName() == "SIZE") {
				myEditor.size();
			}
			else if (command.showCommandName() == "EDIT") {
				try {
					const char* p = command[0].c_str();
					size_t offset = atoi(p);
					myEditor.edit(offset, command[1]);
				}
				catch (const std::exception& e) {
					std::cout << "Fail\n";
				}
			}
			else if (command.showCommandName() == "SHOW") {
				try {
					//myEditor.display(command[0], command[1]);
					const char* p = command[0].c_str();
					size_t offset = atoi(p);

					const char* pp = command[0].c_str();
					size_t limit = atoi(pp);
					myEditor.display(std::cout, offset, limit);
				}
				catch (const std::exception& e) {
					std::cout << e.what();
				}
			}
		}
		else {
			std::cerr << "Command is not valid!\n";
		}
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		throw std::exception("Invalid number of arguments");
		return 1;
	}

	try {
		Editor myEditor(argv[1]);
		Processor myProcessor();

		std::string commandText;
		while (true)
		{
			std::cin >> commandText;
			Command myCommand(commandText);
			myProcessor.execute(myCommand, myEditor);
			if (myCommand.showCommandName() == "EXIT") {
				return 0;
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";
		return 1;
	}
	return 0;
}