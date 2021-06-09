// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Йоанна Милкова Гичева
// ФН: 45761
// Специалност: Информатика
// Курс: Първи курс
// Административна група: гр. 2
// Ден, в който се явявате на контролното: 29.05.2021г.
// Начален час на контролното: <тук попълнете часа за вашата група>
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
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class command {
	char* text;
	std::vector<std::string> commandAndArguments;

public:
	~command() {
		this->commandAndArguments.clear();
	}
	command(char* textInput) {
		this->tokenizeCommandString(textInput);
	}

	void setNewCommand(char* textInput) {
		this->commandAndArguments.clear();
		this->tokenizeCommandString(textInput);
	}
	std::size_t size() const {
		return this->commandAndArguments.size();
	}

	std::string  operator[](std::size_t index) {
		return this->commandAndArguments.at(index);
	}

	void tokenizeCommandString(std::string str) {
		char delimiter = ' ';
		std::string currentString;

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == delimiter) {
				this->commandAndArguments.push_back(currentString);
			}
			else {
				currentString += str[i];
			}
		}
	}
};

class editor {
	std::size_t fileSize;
	std::ifstream inFile;
	std::ofstream outFile;

public:
	editor() {

	}
	void open(std::string path) {
		this->inFile = std::ifstream(path);
	}

	void close() {
		this->outFile.close();
	}

	std::size_t size() {
		this->inFile.seekg(0, this->inFile.end);
		size_t size = this->inFile.tellg();

		return size;
	}
	void edit(std::size_t offset, std::uint8_t value) {
		if(offset > this->size()){
			throw std::invalid_argument("Invalid argument for edit command!");
		}

		//outFile.write(value, offset);
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		if (offset > this->size()) {
			throw std::invalid_argument("Invalid argument for display command!");
		}

		for (int i = offset; i < limit; i++) {

			out << this->outFile.seekp(i);
		}
	}
};

class processor {
	editor* m_editor;

public:

	processor(editor* editor) {
		m_editor = editor;
	}

	bool isValid(command& command) {
		if (command[0] != "EXIT" && command[0] != "SIZE" && command[0] != "EDIT" && command[0] != "SHOW") {
			return false;
		}

		return true;
	}

	std::string execute(command& command) {

		if (!isValid(command)) {
			throw std::invalid_argument("The command is invalid!");
		}

		if (command[0] == "EXIT") {
			this->m_editor->close();
		}
		else if (command[0] == "SIZE") {
			this->m_editor->size();
		}
		else if (command[0] == "EDIT") {
			std::size_t offset = stoi(command[1]);
			std::uint8_t byte = stoi(command[2]);

			this->m_editor->edit(offset, byte);
		}
		else if (command[0] == "SHOW") {
			std::size_t offset = stoi(command[1]);
			std::size_t limit = stoi(command[2]);
			std::ostream stream;

			this->m_editor->display(stream, offset, limit);
		}
	}
};

	int main()
	{
		char* input;
		std::cin >> input;

		editor* commandEditor = new editor();
		try 
		{
			commandEditor->open(input);
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error has occured: " << ex.what() << std::endl;
		}

		processor* commandProcessor = new processor(commandEditor);
		
		std::cin >> input;
		command currentCommand(input);
		while (input != "EXIT") {
			try 
			{
				commandProcessor->execute(currentCommand);
				std::cin >> input;
				currentCommand.setNewCommand(input);
			}
			catch (const std::exception& ex)
			{
				std::cout << "Error has occured: " << ex.what() << std::endl;
			}

		}

	    commandProcessor->execute(currentCommand);

		return 0;
	}



