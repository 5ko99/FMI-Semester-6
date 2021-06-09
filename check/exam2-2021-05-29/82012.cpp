// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Мария Маркова
// ФН: 82012
// Специалност: КН
// Курс: 2
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9.00
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang>
// VS Code (компилатор - MinGW)

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
//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Command
{
private:
	std::vector<std::string> arguments;

	void split(const std::string& _arguments)
	{
		int index = 0;
		while (index < _arguments.size())
		{
			while (_arguments[index] == ' ' && index < _arguments.size())
				index++;

			std::string temp = "";
			while (_arguments[index] != ' ' && index < _arguments.size())
			{
				temp += _arguments[index];
				index++;
			}

			if (temp.size() > 0)
			{
				arguments.push_back(temp);
			}
		}
	}
public:
	Command(const std::string& _arguments)
	{
		split(_arguments);
	}
	std::size_t size() const
	{
		return arguments.size() - 1; // - 1 because the 1st one is the command, the next are the arguments
	}

	std::string operator [] (std::size_t index) const
	{
		if (index < 0 || index >= arguments.size())
			throw std::out_of_range("Index is too big or too small!");

		return arguments[index];
	}
};

class Editor
{
private:
	std::fstream file;
	std::size_t sizeOfFile;
public:
	Editor(const std::string& filePath)
	{
		openFile(filePath);
	}

	std::size_t get_size() const
	{
		return sizeOfFile;
	}

	void openFile(const std::string& filePath)
	{
		file.open(filePath, std::ios::binary | std::ios::in | std::ios::out);

		if (!file.is_open())
			throw std::runtime_error("Cannot open this file!");

		file.seekp(0, std::ios::end);
		sizeOfFile = file.tellp();
	}

	void closeFile()
	{
		file.close();
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		file.seekp(0, std::ios::beg);

		if (offset < 0 || offset > sizeOfFile)
		{
			throw std::invalid_argument("The offset is out of the file!");
		}

		file.seekp(offset, std::ios::beg);
		file.write((const char*)(&value), sizeof(value));
		std::cout << "Successful editting!\n";
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (offset > sizeOfFile)
		{
			out << "The size of the file is " << sizeOfFile << '\n';
			return;
		}

		file.seekg(0, std::ios::beg);
		file.seekg(offset, std::ios::beg);

		
		
		int bytes = 0;
		while (bytes < limit)
		{
			std::uint64_t data;
			file.read((char*)(&data), sizeof(data));
			if (file.eof())
				break;
			out << std::setfill('0') << std::setw(16) << std::hex << data << std::endl;
			bytes += 16;
		}
	}
};

class Processor
{
private:
	Editor editor;
public:
	Processor(const std::string& file) : editor(file) {}

	bool is_valid (const Command& command)
	{
		if (command[0] == "EXIT" || command[0] == "SIZE" || command[0] == "EDIT" ||
			command[0] == "SHOW")
			return true;

		return false;
	}

	void execute (const Command& command)
	{
		if (command[0] == "EXIT")
		{
			editor.closeFile();
		}

		if (command[0] == "SIZE")
		{
			std::cout << editor.get_size() << " byte(s)\n";
		}

		if (command[0] == "EDIT")
		{	
			std::size_t offset = 0;
			std::uint8_t value = 0;

			std::string temp = "";
			temp = command[1];

			for (int i = 0; i < temp.size(); ++i)
				offset += (temp[i] - '0');

			temp = command[1];

			for (int i = 0; i < temp.size(); ++i)
				value += (temp[i] - '0');

			editor.edit(offset, value);
		}

		if (command[0] == "SHOW")
		{	
			std::size_t offset = 0;
			std::size_t limit = 0;
			std::string temp = "";

			temp = command[1];
			for (int i = 0; i < temp.size(); ++i)
				offset += (temp[i] - '0');

			temp = command[2];

			for (int i = 0; i < temp.size(); ++i)
				limit += (temp[i] - '0');

			editor.display(std::cout, offset, limit);
		}
	}
};



int main(int argc, char* argv[])
{
	// test command
	/*Command c("edit cell 67 to 3");
	std::cout << c[0] << '\n';
	std::cout << c[1] << "\n";
	std::cout << c[2] << '\n';
	std::cout << c[3] << '\n';
	std::cout << c[4] << '\n';
	std::cout << c.size() << "\n";*/

	if (argc != 2)
	{
		std::cout << "Please enter a name of file!";
		return 0;
	}

	Processor pr(argv[1]);

	std::string commandLine;
	while (true)
	{
		getline(std::cin, commandLine);
		Command command(commandLine);

		if (!pr.is_valid(command))
		{
			std::cout << "Invalid command!\n";
			continue;
		}

		pr.execute(command);
	}
	return 0;
}