
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//  
// Име: Боян Валентинов Тодоров
// ФН: 45809
// Специалност: Информатика
// Курс: Първи
// Административна група: 5
// Ден, в който се явявате на контролното:  29.05.2021г
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
using namespace std;

class Command {
private:
	vector<string>commands;

	size_t argument_counter = 0;

public:

	Command(string text) {

		size_t start = 0;
		for (size_t i = 0; i < text.size(); i++) {
			if (text[i] == ' ') {
				char word[20];
				for (size_t j = start; j < i; j++) {
					word[j] = text[j];
				}
				word[i] = '\0';

				start = i + 1;


				commands.push_back(word);

				if (commands.size() > 1) {
					argument_counter++;
				}
			}
		}
	}


	size_t size()const {
		return argument_counter;
	}

	string operator[](size_t j) {
		if (j >= commands.size()) {
			throw std::invalid_argument("Invalid input");
		}
		return commands[j];
	}


};

class Processor {
private:
public:
	bool is_valid();

};

class Editor {
private:
	fstream file;
public:

	Editor(string filePath) {
		if (filePath.size() == 0) {
			throw exception("Invalid File Path");
		}

		else {
			this->file.open(filePath, ios_base::binary);
		}

		if (!file.is_open()) {
			throw exception("File could not open, sorry");
		}
	}

	void open(string FilePath) {
		if (FilePath.size() == 0) {
			throw exception("Invalid File Path");
		}
		else {
			this->file.open(FilePath, ios_base::binary);
		}

		if (!file.is_open()) {
			throw exception("File could not open, sorry");
		}
	}

	void close() {
		this->file.close();
	}

	~Editor() {
		this->file.close();
	}



};

int main(size_t argc, char* argv[])
{
	if (argc > 1) {
		string FileDirectory = argv[1];
		fstream File(FileDirectory);
		if (!File.is_open()) {
			throw exception("Couldn't open the file");
		}

	}


	return 0;
}

