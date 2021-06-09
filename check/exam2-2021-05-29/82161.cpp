// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Панайот Маринов
// ФН: 82161
// Специалност: Компютърни науки
// Курс: Първи
// Административна група: Втора
// Ден, в който се явявате на контролното: 29.05.2021 
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
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

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::hex;
using std::setw;
using std::setfill;

const size_t MAX_COMMAND_LENGTH = 1000;

class Command {
	string commandName;
	string* commandArguments;
	size_t numberOfArguments;

public:
	Command(string commandStr) {
		numberOfArguments = 0;
		commandName = "";
		parseCommand(commandStr);
	}

	~Command() {
		delete[] commandArguments;
	}

	size_t size() const {
		return numberOfArguments;
	}

	const string& operator[](size_t index) const {
		if(index == 0) {
			return commandName;
		}
		else {
			return commandArguments[index-1];
		}
	}

	const string& getCommandName() const {
		return commandName;
	}

private:
	void parseCommand(const string& commandStr) {
		size_t startIndex = 0;
		size_t endIndex = 0;

		while(commandStr[endIndex] != ' ' && commandStr[endIndex] != '\0') {
			endIndex++;
		}

		const char* commandNameArr = subStr(commandStr, startIndex, endIndex);
		commandName = commandNameArr;
		delete[] commandNameArr;
		commandNameArr = nullptr;

		size_t commandNameEndIndex = endIndex;
 
		//Count numberOfArguments
		while(commandStr[endIndex] != '\0') {
			//ignore all spaces
			while(commandStr[endIndex] == ' ' && commandStr[endIndex] != '\0') {
				endIndex++;
			}
			startIndex = endIndex;

			//Find nextArgument end
			while(commandStr[endIndex] != ' ' && commandStr[endIndex] != '\0') {
				endIndex++;
			}			
			numberOfArguments++;
		}

		if(numberOfArguments > 0) {
			endIndex = commandNameEndIndex;
			startIndex = endIndex;

			//Save numberOfArguments arguments
			size_t argumentIndex = 0;
			const char* commandArgumentArr;
			commandArguments = new string[numberOfArguments];
			if(commandArguments == nullptr) {
				throw std::invalid_argument("Memory error!");
			}

			while(commandStr[endIndex] != '\0') {
				//ignore all spaces
				while(commandStr[endIndex] == ' ' && commandStr[endIndex] != '\0') {
					endIndex++;
				}
				startIndex = endIndex;

				//Find nextArgument end
				while(commandStr[endIndex] != ' ' && commandStr[endIndex] != '\0') {
					endIndex++;
				}
				
				commandArgumentArr = subStr(commandStr, startIndex, endIndex);
				
				commandArguments[argumentIndex] = commandArgumentArr;
				delete[] commandArgumentArr;
				commandArgumentArr = nullptr;
				argumentIndex++;
			}
		}
	}

	const char* subStr(const string& commandStr, size_t start, size_t end) {
		char* resultArr = new char[end-start+10];
		if(resultArr == nullptr) {
			throw std::invalid_argument("Memory error!");
		}

		for (size_t i = start; i < end; i++) {
			resultArr[i-start] = commandStr[i];
		}
		resultArr[end] = '\0';

		return resultArr;
	}
};

class Editor {
	fstream file;
	bool isOpen = false;
	size_t fileSize;
public:
	Editor(const string& path) {
		open(path);
		isOpen = true;
	}

	~Editor() {
		file.close();
	}

	void open(const string& path) {
		file.open(path, std::ios::binary | std::ios::out);
		if(!file.good()) {
			throw std::logic_error("File cannot be opened");
		}

		file.seekg(std::ios::end);
		fileSize = file.tellg();
		file.seekg(0);

		isOpen = true;
	}

	void close() {
		file.close();
	}

	size_t size() const {
		return this->fileSize;
	}

	void edit(size_t offset, uint8_t value) {
		if(offset > fileSize) {
			throw std::invalid_argument("Offset value too large.");
		}

		file.seekp(offset);
		file.write((char*)&value, sizeof(uint8_t));
		fileSize += sizeof(uint8_t);
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		if(offset > fileSize) {
			throw std::invalid_argument("Offset value too large.");
		}

		size_t bytesSend = 0;
		char currentValue;
		while(!file.eof() && bytesSend < limit) {
			file.read(&currentValue, sizeof(char));
			out<<currentValue;
			if(bytesSend % 16 == 0) {
				out<<'\n';
			}
			bytesSend++;
		}
	}

	
};

class Processor {
	Editor* editor;
	bool isEnd;

public:
	Processor(Editor* e) :
		editor(e) {
			isEnd = false;
		}

	bool end() const {
		return isEnd;
	}

	bool is_valid(const Command& command) {
		bool validName = false;
		if(	command.getCommandName() == "EXIT" ||
			command.getCommandName() == "SIZE" ||
			command.getCommandName() == "EDIT" ||
			command.getCommandName() == "SHOW") {
				validName = true;
			}
		bool validNumArguments = true;
		if(command.getCommandName() == "EXIT" && command.size() != 0) {
			validNumArguments = false;
		}
		else if(command.getCommandName() == "SIZE" && command.size() != 0) {
			validNumArguments = false;
		}
		else if(command.getCommandName() == "EDIT" && command.size() != 2) {
			validNumArguments = false;
		}
		else if(command.getCommandName() == "SHOW" && command.size() != 2) {
			validNumArguments = false;
		}

		bool validArguments = true;
		size_t j;
		for (size_t i = 0; i < command.size(); i++) {
			j = 0;
			while(j < command[i+1].length()) {
				if(command[i+1].at(j) < '0' || command[i+1].at(j) > '9') {
					validArguments = false;
					break;
				}
				j++;
			}
		}
		

		return (validName && validNumArguments && validArguments);
	}

	void execute(const Command& command) {
		if(command.getCommandName() == "EXIT") {
			editor->close();
			isEnd = true;
			return;
		}
		else if(command.getCommandName() == "SIZE") {
			std::cout<<editor->size()<<std::endl;;
		}
		else if(command.getCommandName() == "EDIT") {
			editor->edit(std::stoi(command[1]), std::stoi(command[2]));
		}
		else if(command.getCommandName() == "SHOW") {
			editor->display(std::cout, std::stoi(command[1]), std::stoi(command[2]));
		}
	}

	
};

int main(int argc, char* argv[])
{	
	if(argc != 2) {
		std::cout<<"Please enter <filename>.exe <fileToOpen>.txt"<<endl;
		return 1;
	}

	try {
		const char* filePath = argv[1];
		Editor editor(filePath);
		Processor processor(&editor);

		char* currentCommand = new char[MAX_COMMAND_LENGTH];
		if(currentCommand == nullptr) {
			throw std::invalid_argument("Memory error!");
		}
		while(!processor.end()) {
			cin.getline(currentCommand, MAX_COMMAND_LENGTH);
			Command cm(currentCommand);
			if(!processor.is_valid(cm)) {
				throw std::invalid_argument("Invalid command");
			}

			processor.execute(cm);
		}
	}
	catch(std::invalid_argument e) {
		std::cerr<<e.what()<<endl;
	}
	catch(std::logic_error e) {
		std::cerr<<e.what()<<endl;
	}
	
	
	return 0;
}