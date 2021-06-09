// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Мартин Попов
// ФН: 82134
// Специалност: компютърни науки
// Курс: първи
// Административна група: първа
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: Visual C++
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <string>
#include <vector>

class Command {
	std::vector<std::string> arguments;
	
	void clearTabs(std::string& cmdText) {
		std::string newCmdText;
		for (std::size_t i = 0; i < cmdText.size(); i++) {
			if (cmdText[i] == '\t') {
				newCmdText += ' ';
			}
			else {
				newCmdText += cmdText[i];
			}
		}
		cmdText = newCmdText;
	}
	void clearWhiteSpaces(std::string& cmdText) {
		clearTabs(cmdText);

		std::string newCmdText;
		for (std::size_t i = 0; i < cmdText.size(); i++) {
			if (cmdText[i] == ' ') {
				if (i < cmdText.size() - 1 && cmdText[i + 1] == ' ') {
					continue;
				}
				else {
					newCmdText += cmdText[i];
				}
			}
			else {
				newCmdText += cmdText[i];
			}
		}
		cmdText = newCmdText;
	}
public:
	Command(std::string cmdText) {
		clearWhiteSpaces(cmdText);
		std::size_t lastArgPos = 0;
		for (std::size_t i = 0; i < cmdText.size(); i++) {
			if (cmdText[i] == ' ') {
				arguments.push_back(cmdText.substr(lastArgPos, i - lastArgPos));
				lastArgPos = i + 1;
			}
			else if (i == cmdText.size() - 1) {
				arguments.push_back(cmdText.substr(lastArgPos));
			}
		}
	}
	std::size_t size() const {
		return arguments.size();
	}

	const std::string& operator[](std::size_t pos) const {
		assert(pos < size());
		return arguments[pos];
	}
};

class Editor {
	std::size_t fileSize = 0;
	std::fstream file;
	bool loaded = false;

	void calcSize() {
		while (!file.eof()) {
			std::uint8_t b;
			file.read((char*)&b, sizeof(b));
			fileSize++;
		}
		fileSize--;
		rewind();
	}
	void open(std::string path) {
		file = std::fstream(path, std::ios_base::binary | std::ios_base::in | std::ios_base::out);
		if (!file) {
			throw std::invalid_argument("Could not open file");
		}
		loaded = true;

		calcSize();
	}
	void close() {
		file.close();
		loaded = false;
	}
	void checkLoaded() {
		if (!loaded) {
			throw std::runtime_error("No file loaded");
		}
	}
	void checkOffset(const std::size_t& offset) {
		if (offset >= fileSize) {
			throw std::invalid_argument("Invalid offset");
		}
	}
	void rewind() {
		file.seekg(0, std::ios_base::beg);
	}
public:
	Editor(std::string path) {
		open(path);
	}
	void print() {
		file.seekg(0, std::ios_base::beg);
		std::cout << file.tellg() << '\n';
		while (!file.eof()) {
			std::uint8_t a;
			file.read((char*)&a, sizeof(a));
			std::cout << a << "\n";
		}
		rewind();
	}
	const std::size_t& size() const {
		return fileSize;
	}
	void edit(std::size_t offset, std::uint8_t value) {
		checkLoaded();
		checkOffset(offset);

		file.seekg(offset*sizeof(std::uint8_t), std::ios_base::beg);
		file.write((const char*)&value, sizeof(std::uint8_t));
		rewind();
	}
	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		checkLoaded();
		checkOffset(offset);

		file.seekg(offset * sizeof(std::uint8_t), std::ios_base::beg);
		std::size_t count = 0;
		while (!file.eof()) {
			//out bytes
			for (std::size_t i = 0; i < 16; i++) {
				if (i == 0) {
					out << "offset? ";
				}
				std::uint8_t byte;
				file.read((char*)&byte, sizeof(byte));
				out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte << " ";

				if (file.eof()) {
					break;
				}
				count++;
				if (count == limit) {
					break;
				}
			}
			out << "\n";
		}

		rewind();
	}
};

class Processor {

	bool is_valid(Command cmd) {
		//validate command
	}
public:
	void execute(Command cmd) {

	}
};

int main(){

	//Command cmd("SHOW                 50			20");

	//std::cout << cmd[0];
	Editor f("test.bin");
	f.display(std::cout, 0, 30);
	//f.edit(3, 42);


	//while (!file.eof()) {
	//	std::uint8_t a;
	//	file.read((char*)&a, sizeof(a));
	//	std::cout << a << "\n";
	//}
	//f.seekg(0);
	//std::fstream file("test.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);

	//std::cout << file.tellg() << "\n";
	//while (!file.eof()) {
	//	std::uint16_t a;
	//	file.read((char*)&a, sizeof(std::uint16_t));
	//	std::cout << a << "\n";
	//}

	//std::fstream file("test.bin", std::ios_base::binary | std::ios_base::out);
	//for (int i = 0; i < 40; i++) {
	//	std::uint16_t a = i;
	//	std::cout << a << "\n";
	//	file.write((const char*)&a, sizeof(std::uint16_t));
	//}

	return 0;
}