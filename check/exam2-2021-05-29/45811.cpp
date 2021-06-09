// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Петко Иванов Петков
// ФН: 45811
// Специалност: Информатика
// Курс: 1
// Административна група: 5
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
#include<iomanip>

using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;
using std::exception;
using std::cout;
using std::stoi;
using std::cin;
using std::endl;
using std::ostream;
using std::invalid_argument;
using std::getline;

class editor {
private:
	size_t fileSize = 0;
	ifstream reader;
	ofstream writer;
public:
	editor(const string& path) {
		open(path);
	}

	void open(const string& path) {
		if (!reader.is_open())
		{
			reader.open(path, std::ios_base::binary);

			if (!reader.is_open())
			{
				throw exception("Couldn't open file.");
			}

			reader.seekg(0, reader.end);
			fileSize = reader.tellg();
			reader.seekg(0, reader.beg);
		}

		if (!writer.is_open())
		{
			writer.open(path, std::ios_base::binary);

			if (!writer.is_open())
			{
				throw exception("Couldn't open file.");
			}
		}
	}

	void close() {
		if (reader.is_open())
		{
			reader.close();
		}

		if (writer.is_open())
		{
			writer.close();
		}
	}

	void edit(size_t offset, uint8_t value) {
		if (offset > fileSize)
		{
			string err("ERROR: file size is ");
			throw invalid_argument(err + std::to_string(fileSize));
		}

		if (writer.is_open())
		{
			writer.seekp(offset);
			writer << value;
		}
	}

	void display(ostream& out, size_t offset, size_t limit) {
		if (offset > fileSize)
		{
			string err("ERROR: file size is ");
			throw invalid_argument(err + std::to_string(fileSize));
		}


		if (reader.is_open())
		{
			reader.seekg(offset);
			for (size_t i = 1; i <= limit; i++)
			{
				if (i > fileSize)
				{
					break;
				}

				uint8_t c;
				reader >> c;
				out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)c;

				if (i < limit)
				{
					out << ' ';
				}

				if (i % 16 == 0)
				{
					out << '\n';
				}
			}
		}
	}

	size_t size() const { return fileSize; }

	~editor() {
		if (reader.is_open())
		{
			reader.close();
		}

		if (writer.is_open())
		{
			writer.close();
		}
	}
};

class command {
private:
	vector<string> tokens;

	void tokenizeText(const string& text) {
		size_t wordInd = 0;
		size_t i = 0;

		while (text[i] != '\0')
		{
			while (text[i] == ' ')
			{
				i++;
			}

			wordInd = i;
			while (isalpha(text[i]) || isdigit(text[i]))
			{
				i++;
			}

			if (isalpha(text[wordInd]) || isdigit(text[wordInd]))
			{
				tokens.push_back(text.substr(wordInd, i - wordInd));
			}
		}
	}
public:
	command(const string& text) {
		tokenizeText(text);
	}

	size_t size() const {
		return tokens.size();
	}

	// Could make validation, but operator[] usually doesn't make one
	const string& operator[](size_t pos) const {
		return tokens[pos];
	}

	enum class CommandType {
		EXIT,
		SIZE,
		EDIT,
		SHOW,
		NOCOMMAND
	};

	CommandType getCommandType() const {
		if (!tokens.empty())
		{
			if (tokens[0] == "EXIT")
			{
				return CommandType::EXIT;
			}
			else if (tokens[0] == "SIZE")
			{
				return CommandType::SIZE;
			}
			else if (tokens[0] == "EDIT")
			{
				return CommandType::EDIT;
			}
			else if (tokens[0] == "SHOW")
			{
				return CommandType::SHOW;
			}
			else
			{
				return CommandType::NOCOMMAND;
			}
		}
	}
};

class processor {
private:
	bool isCmdDigitsOnly(const string& cmd) const {
		for (size_t i = 0; i < cmd.size(); i++)
		{
			if (!isdigit(cmd[i]))
			{
				return false;
			}
		}

		return true;
	}
public:
	bool is_valid(const command& cmd) const {
		if (cmd[0] == "EXIT")
		{
			return true;
		}
		else if (cmd[0] == "SIZE") {
			return true;
		}
		else if (cmd[0] == "EDIT")
		{
			if (cmd[1].empty() || !isCmdDigitsOnly(cmd[1]) || cmd[2].empty() || !isCmdDigitsOnly(cmd[2]))
			{
				return false;
			}

			return true;
		}
		else if (cmd[0] == "SHOW")
		{
			if (cmd[1].empty() || !isCmdDigitsOnly(cmd[1]) || cmd[2].empty() || !isCmdDigitsOnly(cmd[2]))
			{
				return false;
			}

			return true;
		}
	}

	void execute(const command& cmd, editor& edit) {
		switch (cmd.getCommandType())
		{
		case command::CommandType::EXIT:
			break;
		case command::CommandType::SIZE:
			cout << edit.size() << " byte(s)" << endl;
			break;
		case command::CommandType::EDIT:
			try
			{
				edit.edit(stoi(cmd[1]), stoi(cmd[2]));
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			catch (const invalid_argument& e) {
				cout << e.what() << endl;
			}
			break;
		case command::CommandType::SHOW:
			try
			{
				edit.display(cout, stoi(cmd[1]), stoi(cmd[2]));
				cout << endl;
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			catch (const invalid_argument& e) {
				cout << e.what() << endl;
			}
			break;
		case command::CommandType::NOCOMMAND:
			break;
		default:
			break;
		}
	}
};

int main(int argv, char** argc)
{
	const string path(argc[1]);
	editor e(path);
	processor p;

	try
	{
		e.open(path);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	while (true)
	{
		cout << '>';
		string	input;
		getline(cin, input);
		command cmd(input);

		if (!p.is_valid(cmd))
		{
			cout << "Invalid command!" << endl;
			continue;
		}

		if (cmd[0] == "EXIT")
		{
			break;
		}

		p.execute(cmd, e);
	}

	return 0;
}