// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Иван Тодоров Иванов
// ФН: 82171
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 29/5/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: gcc
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
#include <iomanip>
#include <fstream>

class Command {
	private:
		std::vector<std::string> commArg;

		void split(std::string str) {
			std::string holder;
			bool isSpaced = false;
			std::size_t begin = 0;

			for (std::size_t i = 0; i < str.length(); ++i) {
				if (str[i] == ' ' && isSpaced == false) {
					isSpaced = true;
					this->commArg.push_back(str.substr(begin, i - begin));
				}
				else if (isSpaced == true && str[i] != ' ') {
					isSpaced = false;
					begin = i;
				}
			}

			this->commArg.push_back(str.substr(begin, str.length() - begin));
		}
	public:
		Command(std::string commandAndArguments) {
			split(commandAndArguments);
		}

		std::size_t size() const {
			return this->commArg.size();
		}

		std::string& operator[](const std::size_t i) {
			return this->commArg[i];
		}
};

class Editor {
	private:
		bool isOpened = false;
		std::fstream file;
		std::string filePath = "";
		std::size_t fileSize;
	public:
		Editor() {
			;
		}

		Editor(std::string filePath) : filePath(filePath) {
			open();
		}

		void open() {
			if (filePath == "") {
				throw std::invalid_argument("No file path given.");
			}

			std::ofstream create(this->filePath, std::ios::app);
			create.close();

			this->file.open(this->filePath, std::ios::binary | std::ios::out | std::ios::app);

			if(!this->file) {
				throw std::exception();
			}

			this->isOpened = true;

			this->file.seekg(0, std::ios::end);
			this->fileSize = this->file.tellg();
		}

		void close() {
			if (this->isOpened == false) {
				throw std::exception();
			}
			this->file.close();
			this->isOpened = false;
		}

		std::size_t size() const {
			if (this->isOpened == false) {
				throw std::exception();
			}

			return this->fileSize;
		}

		void edit(std::size_t offset, std::uint8_t value) {
			if (this->isOpened == false) {
				throw std::exception();
			}

			if (offset > this->fileSize) {
				throw std::invalid_argument("Position not in file");
			}

			this->file.seekg(offset);
			file.write((char*)& value, sizeof(std::uint8_t));
		}

		void display(std::ostream& out, std::size_t offset, std::size_t limit) {
			if (this->isOpened == false) {
				throw std::exception();
			}

			if (offset > this->fileSize) {
				throw std::invalid_argument("Position not in file");
			}

			if (offset + limit > this->fileSize) {
				limit = this->fileSize - offset;
			}

			this->file.seekp(offset);

			int countOnRow = 0;
			std::uint8_t value;

			for (std::size_t i = 0; i <= limit; ++i) {
				if (countOnRow == 16) {
					out << std::endl;
					out << std::setfill('0') << std::setw(8) << std::hex << file.tellp();
					countOnRow = 0;
				}


				file.read((char*)value, sizeof(std::uint8_t));

				out << " " << std::setfill('0') << std::setw(2) << std::hex << value;
				++countOnRow;
			}

		}

		Editor* operator*() {
			return this;
		}

		~Editor() {
			if (this->isOpened == true) {
				this->file.close();
			}
		}
};

class Processor {
	private:
		Editor* editor;
	public:
		Processor() {
			;
		}

		void setEditor(Editor* editor) {
			this->editor = editor;
		}

		bool is_valid(Command command) {
			if (command[0] == "EXIT" && command.size() == 1) {
				return true;
			}

			if (command[0] == "SIZE" && command.size() == 1) {
				return true;
			}

			if (command[0] == "EDIT" && command.size() == 3) {
				return true;
			}

			if (command[0] == "SHOW" && command.size() == 3) {
				return true;
			}

			return false;
		}

		void execute(Command command) {
			if (is_valid(command) == false) {
				throw std::invalid_argument("Command not valid.");
			}

			if (command[0] == "EXIT" && command.size() == 1) {
				throw std::exception();
			}

			if (command[0] == "SIZE" && command.size() == 1) {
				try {
 					std::cout << this->editor->size() << std::endl;
				}
				catch(const std::exception& e) {
					std::cout << "File not opened." << std::endl;
				}
			}

			if (command[0] == "EDIT" && command.size() == 3) {
				try {
 					this->editor->edit(atoi(command[1].c_str()), atoi(command[2].c_str()));
					std::cout << "OK";
				}
				catch (const std::invalid_argument&) {
					std::cout << "ERROR: file size is " << this->editor->size() << "." << std::endl;
				}
				catch (const std::exception& e) {
					std::cout << "File not opened." << std::endl;
				}
			}

			if (command[0] == "SHOW" && command.size() == 3) {
				try {
					this->editor->display(std::cout, atoi(command[1].c_str()), atoi(command[2].c_str()));
					std::cout << "OK";
				}
				catch (const std::invalid_argument&) {
					std::cout << "ERROR: file size is " << this->editor->size() << "." << std::endl;
				}
				catch (const std::exception& e) {
					std::cout << "File not opened." << std::endl;
				}
			}

		}
};


int main(int argv, char* argc[])
{
	if(argv == 1) {
		std::cout << "No path was given, program will exit." << std::endl;
		return 1;
	}

	Editor editor(argc[0]);
	Processor processor;
	processor.setEditor(*editor);
	std::string input;

	while(true) {
		std::cin >> input;
		std::cout << input;
		Command command(input);

		try {
			processor.execute(command);
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
		catch (...) {
			break;
		}
	}


	return 0;
}