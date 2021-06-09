// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Мартин Конов
// ФН: 45804
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате:Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::size_t;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl; 


class command {
	string starting_cmd;
	string main_cmd;
	float offset;
	float limit_byte;
	vector<string> cmd;
public:
	bool valid_or_no = true;

	void split_cmd(string start_cmd) {

		string temp;

		for (size_t i = 0; i < starting_cmd.size(); i++) {
			if (starting_cmd[i] != ' ') {
				temp.push_back(starting_cmd[i]);
			}
			else {
				this->cmd.push_back(temp);
				temp.clear();
			}
		}


		this->cmd.push_back(temp);
	}
	
	string get_main() {
		return this->main_cmd;
	}

	float get_offs() {
		return this->offset;
	}
	float get_limit_bt() {
		return this->limit_byte;
	}


	command(const char* start_cmd) {
		this->starting_cmd = start_cmd;
		split_cmd(starting_cmd);
		if (cmd.size() > 1) {
			this->main_cmd = cmd[0];
			try
			{
				this->offset = stof(cmd[1]);
				this->limit_byte = stof(cmd[2]);

			}
			catch (...)
			{
				valid_or_no = false;
			}
		}
		else {
			this->main_cmd = cmd[0];
		}
	}

	size_t size() const {
		return cmd.size();
	}

	string operator[](size_t i) {
		return cmd[i];
	}

};



class editor {
	ofstream file;
	string path;
	size_t size_file;

public:
	editor() {
		size_file = 0;
	}

	editor(string pth) {
		this->path = pth;
		file.open(path, std::ios_base::binary);
		if (file.fail()) {
			throw std::exception("Failed to open file");
		}
		size_file = sizeof(file);
	}

	~editor(){
		path.clear();
		file.close();
	}

	editor&  operator = (const editor& other) {
		this->open(other.path);
		return *this;
	}

	void open(string path) {
		this->path = path;
		file.open(this->path, std::ios_base::binary);
		if (file.fail()) {
			throw std::exception("Failed to open file");
		}
		size_file = sizeof(file);
	}

	void close() {
		file.close();
	}

	size_t get_size_file() {
		return size_file;
	}

	void edit(size_t offset, std::uint8_t value) {
		if (offset > this->size_file) {
			cout << "The size of the fail is: " << this->size_file;
			throw std::invalid_argument("Fail");
		}
		file.seekp(offset);
		this->file.write((char*)value, offset);
		cout << "OK";
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit) {

	}

};

class processor {

	editor a;

public:

	processor(const editor& b) {
		a = b;
	}


	void execute(command& cmd) {

		if (is_valid(cmd)) {
			if (cmd.get_main() == "SIZE") {
				cout << "The size of this file is: " << this->a.get_size_file() << endl;
			}
			else if (cmd.get_main() == "EDIT") {
				try
				{
					a.edit(cmd.get_offs(), cmd.get_limit_bt());
				}
				catch (const std::invalid_argument& e)
				{
					cout << e.what() << endl;
				}
			}
			else if (cmd.get_main() == "SHOW") {

			}

		}
		else {
			cout << "Invalid command! Try again!" << endl;
		}

		
	}


	bool is_valid(command& check) {
		if (check.get_main() == "EDIT" || check.get_main() == "SHOW" || check.get_main() == "SIZE") {
			if (check.valid_or_no) {
				return true;
			}
		}
		else {
			return false;
		}
	}

};

int main(int argc, char*argv[])
{
	if (argc > 1) {
		editor a;
		try
		{
			a.open(argv[1]);
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}

		char cmd[50];

		cout << "Please type in your command:" << endl;
		
		cin.getline(cmd, 50);

		while (strcmp(cmd, "EXIT") != 0) {

			command this_command(cmd);
			try
			{
				processor process(a);
				process.execute(this_command);

			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
				break;
			}
		
		}

		if (cmd == "EXIT") {
			a.close();
		}

	}
	else {
		cout << "Please  use a command line argument!";
	}

	return 0;
}
