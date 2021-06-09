// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Жени Христова Каракашева
// ФН: 81977
// Специалност: Компютърни науки
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
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

const std::size_t maxLength = 255;

class command {
	std::string receivedCommand;
	std::vector<std::string> arguments;

	public:
	command(std::string& otherReceivedCommand) {
		receivedCommand = otherReceivedCommand;

		separateCommand(receivedCommand);
	}

	void separateCommand(std::string& otherReceivedCommand) {
		std::string temp;
		
		for(std::size_t i = 0; otherReceivedCommand[i] == '\0'; i++) {
			if(otherReceivedCommand[i] == ' ') {
				arguments.push_back(temp);

				temp.clear();
				i++;
			}

			temp[i] = otherReceivedCommand[i];
		}


	}

	std::size_t size() const {
		return arguments.size();
	}

	std::string& operator[](std::size_t index) {
		return arguments.at(index);
	}
};

class editor {
	std::fstream file;
	std::size_t sizeOfFile;

	public:
	editor(std::string path) {	
		open(path);
	}

	void open(std::string path) {
		std::fstream file;

		file.open(path, std::ios::in | std::ios::out |std::ios::app);

		if(!file.is_open()) {
			throw std::invalid_argument("The file cannot be opened!");
		}
	}

	void close(std::fstream& file) {
		if(file.is_open()) {
			file.close();
		}
	}

	~editor() {
		close(file);
	}

	std::size_t size() {
		return sizeOfFile;
	}

	void edit(std::size_t offset, std::uint8_t value) {
	
		if(file.is_open()) {
			file.seekg(offset, std::ios::beg);

			if(file.eof()) {
				throw std::invalid_argument("Offset exceeds end of file!");
			} 

		
			
		} else {
			throw std::invalid_argument("File is not opened!");
		}
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		if(file.is_open()) {
			file.seekg(offset);
			
			std::size_t counter = 0;

		
		} else {
			throw std::invalid_argument("File is not opened!");
		}
	}
};

class processor: public command, public editor {
	public:
	bool is_valid(command& commandToCheck) {
		if (commandToCheck[0] == "EXIT" || commandToCheck[0] == "SIZE") {
			return commandToCheck.size() == 1;
		} else if (commandToCheck[0] == "EDIT" || commandToCheck[0] == "SHOW") {
			return commandToCheck.size() == 3;
		}
	}

	void execute(command& commandToExecute);
};

int main()
{
	std::string temp = "EXIT";
	command tempCommand(temp);
	
	return 0;
}