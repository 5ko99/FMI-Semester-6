// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Христо Тихомиров Христов
// ФН: 82109
// Специалност: КН
// Курс: 2
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
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
#include <sstream>
#include <vector>

using namespace std;

class Command
{
	vector<string> command;
    std::size_t len;

public:
	Command(string input)
	{
		string argument;
		stringstream whole_comm(input);
		while (whole_comm >> argument)
		{
			command.push_back(argument);
		}
	}

	std::size_t size() const
	{
		return command.size();
	}

	string& operator[](size_t index)
	{
		return command[index];
	}

	~Command()
	{

	}
};


class Editor
{
	bool is_open;
	string fpth;
	fstream binfile;
	size_t size;

	void set_size()
	{
		streampos begin, end;
		begin = binfile.tellp();
		binfile.seekp(0, ios::end);
		end = binfile.tellp();
		size_t size_of_file = end - begin;
		this->size = size_of_file;
	}

public:
	Editor(string filepath) : binfile(filepath, ios::binary)
	{
		if (!binfile)
		{
			cout << "The file can't be opened" << endl;
			is_open = false;
		}
		else
		{
			set_size();
			is_open = true;
		}
	}

	void file_open(string filepath)
	{
		binfile.close();
		fstream newbinfile(filepath, ios::binary);
		//binfile = newbinfile;
		if (!binfile)
		{
			cout << "The file can't be opened" << endl;
			is_open = false;
		}
		else
		{
			set_size();
			is_open = true;
		}
	}

	void file_close()
	{
		binfile.close();
	}

	bool is_working()
	{
		return is_open;
	}

	size_t file_size()
	{
		if (is_open)
		{
			return this->size;
		}
		else
		{
			cout << "The file is not opened" << endl;
			return 0;
		}
	}

	void file_edit(std::size_t offset, std::uint8_t value)
	{
		if (is_open)
		{
			if (offset < this->size)
			{
				binfile.seekp(offset);
				binfile.write((char*)&value, sizeof(value));
			}
		}
		else
		{
			cout << "The file is not opened" << endl;
		}
	}

	void file_display(std::ostream &out, std::size_t offset, std::size_t limit)
	{
		if (is_open)
		{
			if (offset +limit >this->size)
			{
				limit = this->size - offset;
			}
			for (size_t i = 0; i < limit; i++)
			{
				uint8_t byte;
				binfile.seekg(offset + i);
				binfile.read((char*)&byte, sizeof(byte));
				//std::cout << std::setfill('0') << std::set_;
			}
		}	
		else
		{
			cout << "The file is not opened" << endl;
		}
	}

	void file_exit()
	{
		binfile.close();
	}

	~Editor()
	{
		file_exit();
	}
};
class Processor
{
	Editor e;
	bool working_processor;

public:
	Processor(string filename) : e(filename)
	{
		if (e.is_working())
		{
			working_processor = true;
		}
		else
		{
			working_processor = false;
		}
	}

	bool is_valid(Command c)
	{
		if (c.size() > 3)
		{
			return false;
		}
		else if (c[0].compare("EXIT") != 0 && c[0].compare("SIZE") != 0 && c[0].compare("EDIT") != 0 && c[0].compare("SHOW") !=0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void execute(Command c)
	{
		if (is_valid(c) && working_processor)
		{
			if (c[0].compare("EXIT") == 0)
			{
				working_processor = false;
				e.file_exit();
			}
			else if (c[0].compare("SIZE") == 0)
			{
				cout << "The file is " << e.file_size() << "bytes" << endl;
			}
			else if (c[0].compare("EDIT") == 0)
			{
				e.file_edit(stoi(c[1]), stoi(c[2]));
			}
			else if (c[0].compare("SHOW") == 0)
			{
				e.file_display(cout, stoi(c[1]), stoi(c[2]));
			}
		}
		else
		{
			cout << "Not valid command or else" << endl;
		}
	}

	~Processor()
	{
	}
};

int main()
{
	Command c("");
	return 0;
}