// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Константин Кондов
// ФН: 82128
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual studio c++
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


#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Command {

private:

	string command;
	string arg1;
	string arg2;

public:

	Command(string& com, string& arg1, string& arg2)  {
	
		if (com != "SIZE" && com != "SHOW" && com != "EXIT" && com != "EDIT") {

			this->arg1 = "none";
			this->arg2 = "none";

	    }

		this->command = com;

		if (this->command == "Exit") {

			this->arg1 = "none";
			this->arg2 = "none";

		
		
		}
		if (this->command == "SIZE") {

			this->arg1 = "none";
			this->arg2 = "none";

		}
		if (this->command == "SHOW") {

			this->arg1 = arg1;
			this->arg2 = arg2;

		}
		if (this->command == "EDIT") {

			this->arg1 = arg1;
			this->arg2 = arg2;

		}
	}


	size_t size() const {

		if (this->arg1 == "none" && this->arg2 == "none") {
			return 1;
		}
		else {
			return 3;
		}

	}

	string& operator[](size_t index)  {

		if (index > 2) {
			throw out_of_range("You want access to argument or command that doesnt exists");
		}

		if (index == 0) {
			return this->command;
		}
		if (index == 1) {
			return this->arg1;
		}
		if (index == 2) {
			return this->arg2;
		}

	}


	string& GetCommand() {
		return this->command;
	}
	
	string& GetFirstArgument() {
		return this->arg1;
	}
	string& GetSecondArgument() {
		return this->arg2;
	}
	
};

class Processor {

private:


private:

	bool is_valid(Command& com) {

		if (com.GetCommand() != "SIZE" && com.GetCommand() != "SHOW" && com.GetCommand() != "EXIT" && com.GetCommand() != "EDIT") {
			return false;
		}
		return true;
	}

	

};


class Editor {

private:

	size_t size;


private:


	Editor(char** argv) {

		fstream file;
		open(file, argv[0]);

		

	}

	void open(fstream& file, char* argv) {

		file.open(argv);
		if (!file) {

			throw invalid_argument("You have not entered valid directory");
		}

	}

	void close(fstream& file) {

		file.close();
	}

	size_t size() {
		return this->size;
	}

};


int main(int argc, char** argv)
{
	

	return 0;
}