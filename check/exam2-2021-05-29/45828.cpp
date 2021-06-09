// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Божидар Атанасов христов
// ФН: 45828
// Специалност: Информатика
// Курс: 1
// Административна група: 6
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class command {
	std::vector<std::string> text;
public:

	command(const std::string rhs) {
		size_t pos = 0, prev = 0;
		do {
			std::string delim = " ";
			pos = rhs.find(delim, prev);
			if (pos == std::string::npos) pos = rhs.length();
			std::string token = rhs.substr(prev, pos - prev);
			if (!token.empty()) text.push_back(token);
			prev = pos + delim.length();
		} while (pos < rhs.length() && prev < rhs.length());
	}
	std::size_t size() const {
		return text.size();
	}
	std::string operator[](const std::size_t& i) {
		return text[i];
	}
};

class editor {
	std::string path;
	std::size_t size = 0;
	std::fstream file;
public:
	editor(){
		size = 0;
		path = "";
	}
	editor(std::string path) {
		this->path = path;
		open();
	}
	size_t getSize() const {
		return this->size;
	}
	std::string getPath() const {
		return this->path;
	}

	void setPath(std::string rhs) {
		path = rhs;
	}
	void setSize(std::size_t rhs) {
		size = rhs;
	}
	void open() {
		file.open(path, std::ios::binary);
		while (!file.eof()) {
			size++;
		}
		if (!file) {
			throw std::exception("Failed openning file!\n");
		}
	}
	void close() {
		file.close();
	}
	void edit(std::size_t offset, std::uint8_t value) {
		if (offset > size) throw std::invalid_argument("Invalid argument!\n");
		file.seekp(offset);
		file >> value;
	}
	void display(std::ostream& out, std::size_t offset, std::size_t limit) {
		if (offset > size) throw std::invalid_argument("Invalid argument!\n");
		file.seekg(offset);
		char* buffer = new char[limit];
		file.read(buffer, limit);

		out << std::setfill('0') << std::setw(limit) << std::hex << buffer;
		delete[] buffer;
	}
};

class processor {
	editor a;
public:
	processor(editor rhs) {
		a.setPath(rhs.getPath());
		a.setSize(rhs.getSize());
	}
	bool is_valid(command rhs) {
		for (size_t i = 0; i < rhs[0].length(); i++)
		{
			if (rhs[0][i] >= 'A' && rhs[0][i] <= 'Z') return true;
			return false;
		}
	}
	void execute(command rhs) {
		if (rhs[0] == "SHOW") a.display(std::cout, stoi(rhs[1]), stoi(rhs[2]));
		else if (rhs[0] == "EXIT") {
			a.close();
			return;
		}
		else if (rhs[0] == "SIZE") std::cout << a.getSize() << std::endl;
		else if (rhs[0] == "EDIT") a.edit(stoi(rhs[1]), stoi(rhs[2]));
		else throw std::exception("Wrong input!\n");
	}
};

int main(int argc, char* argv)
{
	std::string input;
	while (true) {
		std::cin >> input;
		command c = command(input);
		processor p = processor(editor(argv));
		p.execute(c);
		if (c[0] == "EXIT") break;
	}
	

	return 0;
}