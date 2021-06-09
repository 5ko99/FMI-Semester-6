// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Киара Чобанова
// ФН: 82200
// Специалност: КН
// Курс: първи
// Административна група: четвърта
// Ден, в който се явявате на контролното: 29.05.2021 
// Начален час на контролното: 9.00
// Кой компилатор използвате:  Visual C++
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
using std::string;


class Editor {
	size_t m_size;
protected:
	bool is_open = false;
	std::fstream m_file;

public:
	void openFile();
	void closeFile();
	void setSize() { m_size = m_file.tellg(); }
	size_t size() const { return m_size; };
	//Editor(std::fstream file);
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
};

void Editor::openFile() {
	if (is_open == false) {
		m_file.open("file.dat", std::ios::binary | std::ios::out | std::ios::in);
		if (!m_file.is_open()) {
			throw(std::_Xinvalid_argument);
			std::ofstream newFile;
			newFile.open("NewFile.dat", std::ios::binary | std::ios::out | std::ios::in);
		}
		is_open = true;
	}
}

void Editor::closeFile() {
	if (is_open) {
		m_file.close();
		is_open = false;
	}
}

void Editor::edit(std::size_t offset, std::uint8_t value) {
	if (is_open) {
		if (offset < m_size) {
			m_file.seekg(offset, std::ios::beg);
			m_file.write(reinterpret_cast<char*>(&value), sizeof(uint8_t));
			std::cout << "\nOk!";
		}
		else {
			std::cout << "\nFail!";
			std::cout << "\nSize of file is: " << size();
			throw(std::_Xinvalid_argument);
		}
	}
	else {
		throw(std::_Xinvalid_argument);
		std::ofstream newFile;
		newFile.open("NewFile.dat", std::ios::binary | std::ios::out | std::ios::in);
	}
}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit) {
	if (is_open) {
		edit(offset, reinterpret_cast<uint8_t> (&out));
		size_t size = m_file.tellg();
		for (size_t i = size; i < limit; i += m_file.tellg()) {
			m_file.write(reinterpret_cast<char*>(&out), sizeof(offset));
		}
	}
}



class Command : public Editor {
	string m_commandText;
	int m_numberOfArguments;
	string m_name;
	std::vector <string> m_arguments;
	int m_command;
public:
	Command() {};
	Command(string commandText, string name, int numberOfArguments, std::vector <string> arguments);
	
	void setName(const string name) { m_name = name; };
	string getName() const { return m_name; };

	void setNumberOfArguments(int numberOfArguments) {m_numberOfArguments = numberOfArguments; };
	int getNumberOfArguments() const { return m_numberOfArguments; };
	
	bool validate();

	void runCommand();

	string operator[](size_t index);

};

Command::Command(string commandText, string name, int numberOfArguments, std::vector <string> arguments){
	m_name = name;
	m_numberOfArguments = m_numberOfArguments;
	for (int i = 0; i < m_numberOfArguments; ++i) {
		m_arguments[i] = arguments[i];
	}
	m_commandText += name;
	for (int i = 0; i < m_numberOfArguments; ++i) {
		m_commandText += m_arguments[i];
	}
}

string Command::operator[](size_t index) {
	return m_arguments[index];
}

bool Command::validate() {
	return!((m_commandText.size() != m_numberOfArguments + 1) || m_command > 4);
}

void Command::runCommand() {
	openFile();
	if (is_open == true) {
		std::cout << "Enter command: ";
		std::cin >> m_command;
		if (m_command == 1) {
			closeFile();
		}
		else if (m_command == 2) {
			size();
		}

		else if (m_command == 3) {
			std::size_t offset;
			std::uint8_t byte;
			std::cout << "\nEnter a position: ";
			std::cin >> offset;

			std::cout << "\nEnter value: ";
			std::cin >> byte;

			edit(offset, byte);

			closeFile();
		}

		else if (m_command == 4) {
			std::ostream& out = m_file;
			std::size_t offset;
			std::size_t limit;

			std::cout << "\nEnter a position: ";
			std::cin >> offset;

			std::cout << "\nEnter limit: ";
			std::cin >> limit;

			display(out, offset, limit);
		}
	}
	closeFile();
}



class Processor : public Editor {


public:
	bool is_valid(Command command) { return (command.validate()); };
	void execute(Command command);
};

void Processor::execute(Command command) {
	if (command.validate()) {
		command.runCommand();
	}
};

//
//Editor::Editor(std::fstream myFile) {
//	openFile(myFile);
//	setSize(m_file);
//}


int main()
{
	Editor e;
	std::fstream file;
	e.openFile();

	return 0;
}
