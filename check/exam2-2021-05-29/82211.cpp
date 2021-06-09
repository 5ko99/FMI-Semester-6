// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// ФН: 82211
// Име: Ангел Димитров Петров
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Command {

	std::vector<std::string> commands;

public:
	Command(std::string userInput) {

		size_t i = 0;

		while(i < userInput.size()) {
			std::string commandToAdd;

			for (;i < userInput[i] != ' '; ++i) {
				commandToAdd[i] = userInput[i];
			}
			commands.push_back(commandToAdd);
			
			while(userInput[i] == ' ') {
				++i;
			}
		}
	}

	std::size_t size() const {
		return commands.size();
	}

	std::string& operator[](std::size_t pos) {

		return commands.at(pos); 
	}
};

class Editor {

	static Editor* instance;
	std::string path;
	std::fstream in;
	size_t fileSize;

	void setSize() {

		size_t beg, end;

		in.seekp(std::ios::beg);
		beg = in.tellp();
		in.seekp(std::ios::end);
		end = in.tellp();

		fileSize = end - beg;
	}

	Editor(std::string path) : path(path) {
		open();
		setSize();
	}

public:

	static Editor* getInstance(std::string path) {
		if (!instance) {
			instance = new Editor(path);
		}

		return instance;
	}

	void open() {
		in.open(path, std::ios::binary);

		if (!in.is_open()) {
			throw std::runtime_error("Couldn't open file!\n");
		}
	}

	void close() {

		in.close();
	}	

	size_t size() const {

		return fileSize;
	}

	void edit(std::size_t offset, std::uint8_t value) {

		if (offset > fileSize) {
			throw std::invalid_argument("FAIL!\n");
		}


		in.seekp(offset);
		in.put(value);

		std::cout << "OK\n";
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		
		if(offset > fileSize) {
			throw std::invalid_argument("Error: \n");
		}

		in.seekg(offset);

		size_t cnt = 1;
		for (;in.tellg() == limit || in.eof(); ++cnt) {

			if (cnt % 16 == 0) {
				out << std::setfill('0') << std::setw(8) << std::hex << in.get() - in.beg << std::endl;
			}

			out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)in.get();

			in.seekg(++offset);
		}
	}

	~Editor() {
		in.close();
	}
};

Editor* Editor::instance = 0;


class Processor {

	static Processor* instance;

	std::string path;

	Processor(std::string path) : path(path) {}

	bool isValid(Command& obj) {
		
		if(!(obj[0] == "EXIT" || obj[0] == "SIZE" || obj[0] == "EDIT" || obj[0] == "SHOW")) {
			return false;
		}

		if ((obj[0] == "EDIT" || obj[0] == "SHOW") && obj.size() != 3) {
			return false;
		}
		else if ((obj[0] == "EXIT" || obj[0] == "SIZE") && obj.size() != 1) {
			return false;
		}

		if (obj[0] == "EDIT" || obj[0] == "SHOW") {

			for (size_t i = 0; i < obj[1].size(); ++i) {
				if (obj[1][i] < '0' || obj[1][i] > '9') {
					return false;
				}
			}

			for (size_t i = 0; i < obj[2].size(); ++i) {
				if (obj[2][i] < '0' || obj[2][i] > '9') {
					return false;
				}
			}
		}

		return true;
	}
public:

	static Processor* getInstance(std::string path) {

		if(!instance) {
			instance = new Processor(path);
		}

		return instance;
	}

	void execute(Command& toDo) {

		if (!isValid(toDo)) {
			throw std::invalid_argument("Invalid commnad!\n");
		}

		Editor* editor;

		try {
			editor = Editor::getInstance();
		}
		catch(std::runtime_error& e) {
			std::cout << e.what();
		}

		if (toDo[0] == "SHOW") {
			size_t offset = atoi(toDo[1].c_str());
			size_t limit = atoi(toDo[2].c_str());

			try {
				editor->display(std::cout, offset, limit);
			}
			catch (std::invalid_argument& e) {
				std::cout << e.what();
				std::cout << "size of file is " << editor->size() << ".\n";
				return;
			}
		}
		else if (toDo[0] == "EDIT") {
			size_t offset = atoi(toDo[1].c_str());
			size_t byte = atoi(toDo[2].c_str());

			try {
				editor->edit( offset, byte);
			}
			catch (std::invalid_argument& e) {
				std::cout << e.what();
				return;
			}
		}
		else if (toDo[0] == "SIZE") {
			std::cout << "Size of file is: " << editor->size() << ".\n";
		}
		else if (toDo[0] == "EXIT") {
			editor->close();
		}
	}

};

Processor* Processor::instance = 0;

int main(int argc, const char** argv)
{
	if (argc < 2) {
		std::cout << "Path required.\n";
		return 1;
	}	

	std::string path(argv[1]);

	Processor* process = Processor::getInstance(path);

	while (true) { 
		std::string userInput;

		std::cout << "Enter command: ";
		std::getline(std::cin, userInput);

		Command toExecute(userInput);

		if (toExecute[0] == "EXIT") {
			break;
		}

		try {
			process->execute(toExecute);
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what();
			break;
		}
	}
	return 0;
}