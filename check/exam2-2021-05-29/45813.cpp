// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Атанас Веселинов Караиванов
// ФН: 45813
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 29/05/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class CommandNames {
	EXIT, SIZE, EDIT, SHOW
};

class Command {
	string text;
	vector<string> arguments;
	size_t m_size;
public:
	Command(const char* commandText) : text(commandText) {
		size_t cnt = 0;
		size_t cnt2 = 0;
		string temp;
		for (size_t i = 0; i < text.size() + 1; i++) {
			if (text[i] == ' ' || text[i] == '\n' || text[i] == '\0') {
				arguments[cnt] = temp;
				temp = "";
				cnt++;
				continue;
			}
			temp[cnt2] += text[i];
			cnt2++;

		}
		m_size = cnt++;
	}

	size_t size() const {
		return m_size;
	}

	string& operator[](size_t pos) {
		if (m_size < pos) {
			throw out_of_range("Position is out of range!");
		}
		return arguments[pos];
	}
};


class Processor {

public:

	bool is_valid(Command& command) {
		if (command[0] == "EXIT") {
			return true;
		}
		if (command[0] == "SIZE") {
			return true;
		}
		if (command[0] == "EDIT") {
			return true;
		}
		if (command[0] == "SHOW") {
			return true;
		}
		return false;
	}

	void execute(Command& comm) {
		if (is_valid(comm)) {

		}
	}
};

class Editor {
	ifstream file;
	string path;
	int fileSize;
public:
	Editor(const char* pathTxt) {
		open(pathTxt);
		file.seekg(0, file.eof());
		fileSize = file.tellg();
	}

	void open(const char* fileName) {
		file.open(fileName, ios::binary);
		if (!file.is_open()) {
			throw exception("File didn't open!");
		}
	}

	void close(const char* fileName) {
		file.close();
	}

	void edit(size_t offset, uint8_t value) {

	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {

	}

	int size() const {
		return fileSize;
	}

	~Editor() {
		close(path.c_str());
	}
};

int main(int argc,char* argv[]) {
	


	return 0;
}