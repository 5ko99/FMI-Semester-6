// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Елизабет Великова Колева
// ФН: 82173
// Специалност: Компютърни науки
// Курс: 1-ви
// Административна група: 3-та
// Ден, в който се явявате на контролното: 29.05.2021 г.
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#pragma region info
// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// bin:  xxd -b file   hex: xxd file
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//	 tellp / seekp -> ofstream (put)
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//	 tellg / seekg -> ifstream (get)
//   включите съответните header файлове от стандартната
//   библиотека.


#define _CRT_SECURE_NO_WARNINGS 
#pragma endregion

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <iomanip>
#include <vector>

using std::cout; 
using std::cin; 
using std::endl;
using std::string; 
using std::exception;
using std::vector;
using std::ostream;
using std::ofstream;
using std::ifstream;

class Command {
private:
	string userCommand;
	string command;
	string offsetStr;
	string otherArgsStr;
	int offset;
	int otherArg;

	void getArgs(std::size_t numberOfArgs) {
		unsigned int i = 0;
		while (userCommand[i] != ' ' && i < userCommand.length()) {
			++i;
		}
		command = userCommand.substr(i, 4);

		if (numberOfArgs == 3) {
			while (userCommand[i] == ' ' && userCommand[i+1] != ' ' && i < userCommand.length()-1) {
				++i;
			}

			unsigned int endOfFirstArg = i+1;
			while (userCommand[endOfFirstArg] == ' ' && endOfFirstArg < userCommand.length()-1) {
				++endOfFirstArg;
			}

			offsetStr = userCommand.substr((i+1), (endOfFirstArg-i-1));
			offset = stoi(offsetStr);

			unsigned int secondArg = i+1;

			while (userCommand[secondArg] == ' ' && userCommand[secondArg+1] != ' ' && secondArg < userCommand.length()-1) {
				++secondArg;
			}

			otherArgsStr = userCommand.substr((i+1), (userCommand.length() - i - 1));
			otherArg = stoi(otherArgsStr);
		}
		else if (numberOfArgs < 1 || numberOfArgs > 4) {
			throw std::invalid_argument("");
		}
	}
// TODO: Capitalize
public:
	Command(const string& userCommand) 
		: userCommand(userCommand)
	{
		getArgs(size());
	}

	std::size_t size() const {
		unsigned int i = 0;
		std::size_t counter = 0;
		std::size_t countArgs = 0;

	// // TODO: see below
	// 	while (userCommand[i] != ' ' && i < userCommand.length()) {
	// 		++counter;
	// 		++i;
	// 	}

		unsigned int j = 0;
		while (j < userCommand.length()-1) {
			if (userCommand[j] == ' ' && userCommand[j+1] != ' ') {
				++countArgs;
			}
		}

		return countArgs;
	}

	string operator[](std::size_t pos) {
		if (pos < 0 || pos > size()) {
			throw std::out_of_range("");
		}
		else {
			switch (pos)
			{
			case 0:
				return command;
				break;
			
			case 1:
				return offsetStr;
				break;

			case 2:
				return otherArgsStr;
				break;
			}
		}
	}

	// int getFirstArg()

};

class Editor;

class Processor {
private:
	friend class Command;
	char* path;
	Editor userEdit(path);
public:
	bool is_valid(Command& usrCommand) {
		if (usrCommand.size() == 1) {
			// if(usrCommand[0] == "EXIT" || usrCommand[0] == "SIZE") {
			// 	return true;
			// }
			return usrCommand[0] == "EXIT" || usrCommand[0] == "SIZE";
		}
		else if (usrCommand.size() == 3) {
			return usrCommand[0] == "EDIT" || usrCommand[0] == "SHOW";
		}
		else {
			return false;
		}
	}

	void execute(Command& usrCommand) {
		if (!is_valid(usrCommand)) {
			throw std::invalid_argument("");
		}
		else {
			try {
				if (usrCommand[0] == "EXIT") {
					userEdit.close(userEdit.whichIsOpen());
				}
				else if (usrCommand[0] == "SIZE") {
					userEdit.getFileSize();
				}
				else if (usrCommand.size() == 3) {
					if (usrCommand[0] == "EDIT") {
						string offsetAsStr = usrCommand[1];
						int offset = stoi(offsetAsStr);

						string secondArgAsStr = usrCommand[2];
						int secondArg = stoi(secondArgAsStr);

						userEdit.edit(offset, secondArg);

					}
					else { //(usrCommand[0] == "SHOW") {
						string offsetAsStr = usrCommand[1];
						int offset = stoi(offsetAsStr);

						string secondArgAsStr = usrCommand[2];
						int secondArg = stoi(secondArgAsStr);

						userEdit.display(cout, offset, secondArg);
					}
				}
			}
			catch(const std::invalid_argument()) {
				cout << "Invalid args!" << endl;
				return;
			}
			catch (...) { // No time to catch invalid arg...
				cout << "Something went wrong!" << endl;
			}
		}

	}
};

class Editor {
private:
	ofstream fileWrite;
	ifstream fileRead;
	string userPath;
	char* path;
	bool isFileOpen;
	std::size_t fileSize;
public:
	// Editor(const string& filePath) 
	Editor(char*& pathU) 
		: path(pathU)
	{
		open(userPath, 0);
	}

	~Editor() {
		if (fileRead.is_open()) {
			fileRead.close();
		}
		else {
			fileWrite.close();
		}
	}

	bool whichIsOpen() const { // read 0, write 1
		return fileWrite.is_open();
	}

	void open(const string& userFile, bool readWrite) { // read 0, write 1
		if (!readWrite) {
			fileRead.open(userFile, std::ios::out | std::ios::binary | std::ios::in);
			if (!fileRead.is_open()) {
				isFileOpen = false;
				throw ("Couldn't open the file!");
			}
			else {
				isFileOpen = true;
				size_t currentPos = fileRead.tellg();
				fileRead.seekg(0, std::ios::end);
				fileSize = fileRead.tellg();
				fileRead.seekg(currentPos, std::ios::beg);

			}
		}
		else {
			fileWrite.open(userFile, std::ios::out | std::ios::binary | std::ios::in);
			if (!fileWrite.is_open()) {
				isFileOpen = false;
				throw ("Couldn't open the file!");
			}
			else {
				isFileOpen = true;
				size_t currentPos = fileWrite.tellp();
				fileWrite.seekp(0, std::ios::end);
				fileSize = fileWrite.tellp();
				fileWrite.seekp(currentPos, std::ios::beg);

			}
		}
	}

	size_t getFileSize() const {
		return fileSize;
	}

	void writeToFile(std::size_t offset, std::uint8_t value) {
		if (offset >= fileSize) {
				throw std::invalid_argument("");
			}
			else {
				fileWrite.seekp(offset, std::ios::beg);
				fileWrite.write((const char*)& value, sizeof(uint8_t));
			}

			if (fileWrite.good()) {
				cout << "OK" << endl;
			}
			else {
				cout << "Fail" << endl;
				close(1);
				// fileWrite.close();
				throw std::logic_error("");
			}
	}

	void edit(std::size_t offset, std::uint8_t value) {
		if (fileWrite.is_open()) {
			writeToFile(offset, value);
		}
		else if (fileRead.is_open()) {
			close(0);
			// fileRead.close();
			open(userPath, 1);
			writeToFile(offset, value);			
		}
		
	}

	void readFromFile(std::ostream& out, std::size_t offset, std::size_t limit) {
		fileRead.seekg(offset, std::ios::beg);
		uint8_t* arrN = new uint8_t[limit];
		fileRead.read((char*)& arrN, sizeof(uint8_t) * limit);
		out << std::setfill('0') << std::setw(8) << std::hex << offset << ' ';
		for (unsigned int i = 0; i < limit; ++i) {
			out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)arrN[i]  << ' ';
			if (i == 15) {
				out << endl;
				out << std::setfill('0') << std::setw(8) << std::hex << offset+15 << ' ';
			}
		}
		// for (unsigned i = 0; i < limit; ++i ) {
		// 	delete
		// }
		delete[] arrN;
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		if (fileWrite.is_open()) {
			if (offset >= fileSize) {
				throw std::invalid_argument("");
			}
			else {
				close(1);
				open(userPath, 0);

				readFromFile(out, offset, limit);
			}
			
		}
		else if (fileRead.is_open()) {
			if (offset >= fileSize) {
				throw std::invalid_argument("");
			}
			else {
				readFromFile(out, offset, limit);
			}
		}
	}

	void close(bool readOrWrite) { // read 0, write 1
		if (readOrWrite) {
			fileWrite.close();
		}
		else {
			fileRead.close();
		}
	}
};

int main(int argc, char* argv)
{ 
	if (argc != 2) {
		cout << "Invalid number of args!" << endl;
		return 1;
	}
	else {
		// string path = argv[1];
		// Editor edit(argv[1]);

	}

	return 0;
}