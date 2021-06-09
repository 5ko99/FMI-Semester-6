#include <iostream>
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Искендер Чобанов
// ФН:45508
// Специалност: Информатика
// Курс:3-ти
// Административна група:-
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
#include <string>
#include <iomanip>

class command
{
private: //the given commands can have max of 2 arguments
	std::string text;
	std::string com;
	std::string arg1;
	std::string arg2;
	size_t num_of_arg;
public:
	command(std::string text)
	{
		num_of_arg = 0;
		bool is_command = 1;
		bool is_arg1 = 1;
		for (unsigned i = 0; i < text.size(); i++)
		{
			if (is_command)
			{
				if (text[i] == ' ')
				{
					is_command = 0;
					continue;
				}
				com.push_back(text[i]);
			}
			else {
				if (is_arg1)
				{
					if (text[i] == ' ')
					{
						is_arg1 = 0;
						continue;
					}
					arg1.push_back(text[i]);
				}
				else {
					if (text[i] == ' ')
					{
						continue;
					}
					arg2.push_back(text[i]);
				}
			}

		}
		if (arg1 != "")
			num_of_arg++;
		if (arg2 != "")
			num_of_arg++;
	}

	void print_all()
	{
		std::cout << com << " " << arg1 << " " << arg2 <<"\nNumber of arg: "<<num_of_arg<< std::endl;
	}
	std::size_t size() const
	{
		return num_of_arg;
	}
	std::string& operator[](size_t index) 
	{
		if (index > 2 || index < 0)
			throw std::out_of_range("invalid index");
		switch (index)
		{
		case 0: return com;
		case 1: return arg1;
		case 2: return arg2;
		}
	}
	const std::string& operator[](size_t index) const
	{
		if (index > 2 || index < 0)
			throw std::out_of_range("invalid index");
		switch (index)
		{
		case 0: return com;
		case 1: return arg1;
		case 2: return arg2;
		}
	}
};
class editor
{
private:
	std::fstream binfile;
	bool file_opened;
	size_t file_size;
public:
	editor(const char* path)
	{
		open(path);
	}
	void open(const char* path) {
		binfile.open(path, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
		if (!binfile.is_open())
		{
			file_opened = 0;
			throw std::runtime_error("Error opening file");
		}
		binfile.seekp(std::ios_base::end);
		file_size = binfile.tellp();
		file_opened = 1;
	}
	size_t size()
	{
		if (file_opened)
			return file_size;
		throw std::runtime_error("file not opened");
	}
	void edit(std::size_t offset, std::uint8_t value)
	{
		if (offset >= file_size)
		{
			throw std::invalid_argument("Invalid offset");
		}
		binfile.seekp(offset, std::ios_base::beg);
		binfile.write((char*)&value, sizeof(std::uint8_t));
	}
	void close()
	{
		binfile.close();
	}
	std::ostream& display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (offset >= file_size)
		{
			throw std::invalid_argument("Invalid offset");
		}
		binfile.seekg(offset, std::ios_base::beg);
		std::string text;
		if (limit > file_size)
		{
			binfile.read((char*)&text, file_size);
		}
		binfile.read((char*)&text, limit);
		out << text;
		return out;
	}
	bool file_opened_succ()
	{
		return file_opened;
	}
	~editor()
	{
		close();
	}

};

class processor {
private:
	const char* path;
public:
	processor(const char* _path)
	{
		path = _path;
	}
	bool is_valid(const command& com)
	{
		return ((com[0] == "EXIT" && com.size() == 0)|| (com[0] == "SIZE" && com.size() == 0) || (com[0] == "EDIT" && com.size() == 2 && stoi(com[1]) && stoi(com[2]))
			|| (com[0] == "SHOW" && com.size() == 2 && stoi(com[1]) && stoi(com[2]))
			);
			
	}
	bool execute(const command& com)
	{
		try {
			editor ed(path);
			if (com[0] == "SHOW" && is_valid(com))
			{
				ed.display(std::cout, stoi(com[1]), stoi(com[2]));
				return 1;
			}
			if (com[0] == "EDIT" && is_valid(com))
			{
				ed.edit(stoi(com[1]), stoi(com[2]));
				return 1;
			}
			if (com[0] == "SIZE" && is_valid(com))
			{
				std::cout<<'\n'<<ed.size()<<'\n';
			}
			return 0;
		}
		catch (...)
		{
			return 0;
		}
	}
};



int main(int argc, char* argv[]) 
{

		if (argc != 2)
		{
			throw std::invalid_argument("Invalid argument wrong number of par");
		}
		editor ed(argv[1]);
		while (1)
		{
			std::string text;
			std::cin >> text;
			command com(text);
			processor proc(argv[1]);
			if (proc.is_valid(com) && com[0] == "EXIT")
				break;
			proc.execute(com);
		}
		return 0;
	}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
