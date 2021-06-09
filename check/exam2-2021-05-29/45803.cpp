//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Деян Крумов
// ФН:45803
// Специалност: Информатика
// Курс: 1-ви
// Административна група: 5-та
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: <GCC>
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
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Command
{
	string command_name;
	string command_arguments;
	size_t arg_size;

public:
	Command(string& command)
	{
		arg_size = -1;

		char* char_array = nullptr;
		try
		{
			char_array = new char[command.length() + 1];
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		strcpy(char_array, command.c_str());

		char *token = strtok(char_array, " ");
		int i = 0;

		while (token != NULL)
		{
			if (i == 0)
			{
				command_name = token;
			}
			else
			{
				command_arguments += ";";
				command_arguments += token;
			}
			i++;
			token = strtok(NULL, " ");
		}

		arg_size = i;
		delete[] char_array;
	}

	void size() const
	{
		cout << arg_size << endl;
	}

	string get_Command()
	{
		return command_name;
	}

	Command operator[](size_t index)
	{
		char *char_array = nullptr;
		try
		{
			char_array = new char[arg_size + 1];
		}
		catch (const std::bad_alloc &e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}

		char*command_argumentsArray = nullptr;
		try
		{
			command_argumentsArray = new char[arg_size];
		}
		catch(std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}
		
		strcpy(char_array, command_arguments.c_str());

		char *token = strtok(char_array, ";");
		int i = 0;

		while (token != NULL)
		{
			command_argumentsArray[i] = *token;
			i++;
			token = strtok(NULL, " ");
		}

		cout << command_argumentsArray[index] << endl;

		delete[] char_array;
	}
};



class editor
{
	std::fstream file;
	std::size_t size;

	// void copyFrom(const editor& other)
	// {
	// 	this->file = other.file;
	// 	this->size = other.size;
	// }

public:

	// copy
	// editor(editor& other)
	// {
	// 	if(this != &other)
	// 	{
	// 		this->copyFrom(other);
	// 	}
	// }

	// editor& operator=(const editor& other)
	// {
	// 	if(this != &other)
	// 	{
	// 		this->copyFrom(other);
	// 	}
	// }

	editor(std::string &filepath)
	{
		try
		{
			this->open(filepath);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}
	}

	

	void open(std::string &filepath)
	{
		if (filepath.c_str() == nullptr)
		{
			throw std::invalid_argument("Invalid filepath");
			return;
		}
		this->file.open(filepath, std::ios::binary | std::ios::trunc);
		this->size = sizeOfFile();

		if (!file.is_open())
		{
			std::logic_error e("Cant open file");
			throw std::exception(e);
		}
	}

	void close()
	{
		if (this->file.is_open() && file.good())
			this->file.close();
	}

	std::size_t sizeOfFile()
	{
		if (file.is_open())
		{
			file.seekp(0, std::ios_base::end);
			std::size_t size = file.tellp();
			file.seekp(0, std::ios_base::beg);
			return size;
		}
		return 0;
	}

	void edit(std::size_t &offset, std::uint8_t &value)
	{
		if (offset > this->size)
		{
			throw std::invalid_argument("Leaving bounds of file");
		}
		if (file.is_open())
		{
			this->file.seekp(offset, std::ios_base::beg);
			file.put(value);
		}
	}

	void display(std::ostream &out, std::size_t &offset, std::size_t &limit)
	{
		if (offset > this->size || offset < 0)
		{
			std::cerr << "Size of file is: " << this->size << std::endl;
			throw std::invalid_argument("Leaving bounds of file");
			return;
		}

		if (file.is_open())
		{
			file.seekg(offset, std::ios_base::beg);
		}

		std::size_t count = 0;
		while (count <= limit || count < this->size)
		{
			uint8_t byte = file.get();
			out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte;
		}
	}

	~editor()
	{
		this->size = 0;
		this->file.close();
	}
};

class Processor
{
	editor editor_sub;

public:
	Processor(std::string& filepath) : editor_sub(filepath)
	{
		
	}

	bool isValid(Command command) const
	{
		string valid_commands = "EXIT;SIZE;EDIT";
		if (valid_commands.find(command.get_Command()) != string::npos)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void execute(Command command) 
	{
		try
		{
			if (command.get_Command() == "SIZE")
			{
				editor_sub.sizeOfFile();
			}
			else if (command.get_Command() == "EXIT")
			{
				editor_sub.close();
			}
			else if (command.get_Command() == "EDIT")
			{
				size_t offset;
				cout << "Enter Offset" << endl;
				cin >> offset;

				uint8_t value;
				cout << "Enter value" << endl;
				cin >> value;
				editor_sub.edit(offset, value);
			}
		}
		catch (const ifstream::failure &e) 
		{
			cout << "Error" << endl;
		}
	}
};
int main()
{

	return 0;
}