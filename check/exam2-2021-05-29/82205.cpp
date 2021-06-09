// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Йоана Дудева
// ФН: 82205
// Специалност: КН
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC
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
#include <vector>

using std::cout;
using std::cin;
using std::endl; 

class Command
{
	private:
	// std::string commandLine;
	std::string name;
	std::string first; 
	std::string second; 

	public:
	Command(std::string comm);

	std::size_t size() const;
	std::string operator[](size_t n); 
};

Command::Command(std::string comm)
{
	int pos = comm.find(" ");
	this->name = comm.substr(0, pos);

	comm = comm.substr(pos+1); 

	std::string tempcommand; 
	if (comm[0] == ' ')
	{
		int i = 0;
		while (!isalpha(comm[i]) || !std::isdigit(comm[i]))
		{
			++i;
		}
		comm = comm.substr(i+1);  
	}

	int seconpos = comm.find(" ");
	this->first = comm.substr(0, seconpos); 

	comm = comm.substr(seconpos+1); 
	
	int lastspace = comm.find_last_of(" "); 
	if (comm[lastspace+1] != '\0')
	{
		this->second = comm.substr(lastspace, comm.size()); 
	}
	else
	{
		this->second = nullptr; 
	}
}

std::size_t Command::size() const
{
	if (this->second.empty())
	{
		return 1;
	} 
	if (this->first.empty())
	{
		return 0;
	}

	return 2; 
}
std::string Command::operator[](size_t n)
{
	if (n > 2 || n < 0)
	{
		throw std::out_of_range("Invalid n");
	}

	if (n == 0)
	{
		return this->name;
	}
	if (n == 1)
	{
		return this->first;
	}
	
	return this->second; 
} 

class Processor : public Command
{
	private:
	bool is_valid;

	public:
	Processor(const std::string comm, bool valid); 

	void execute(std::string comm); 

};

Processor::Processor(const std::string comm, bool valid) : Command(comm)
{
	if (comm.empty())
	{
		this->is_valid = false; 
	}
	
	this->is_valid = true; 
}

void Processor::execute(std::string comm)
{
	//Command temp(comm);
	bool valid = false; 
	Processor process(comm, valid);

	if (!valid)
	{
		throw std::invalid_argument("");
	}
}

class Editor
{
	private:
	size_t size; 
	std::uint8_t* data;

	public:
	Editor(std::string path);

	void open(std::string path);
	void close(std::string path); 

	size_t getSize() const; 
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);

};

Editor::Editor(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios::binary | std::ios::in);

	if (!file.is_open())
	{
		throw std::exception();
	}

	size_t cur = file.tellg();
	file.seekg(0, std::ios::end);

	this->size = file.tellg();
	file.seekg(cur, std::ios::beg);


	this-> data = new std::uint8_t[this->size];
	file.read((char*)data, sizeof(std::uint8_t)*this->size);

	file.close(); 

}

void Editor::open(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios::binary | std::ios::in);

	if (!file.is_open())
	{
		throw std::exception();
	}

	size_t cur = file.tellg();
	file.seekg(0, std::ios::end);

	this->size = file.tellg();
	file.seekg(cur, std::ios::beg);

	this->data = new std::uint8_t[this->size];
	file.read((char*)data, sizeof(std::uint8_t)*this->size);

	file.close(); 
}
void Editor::close(std::string path)
{
	std::ofstream file;
	file.open(path, std::ios::binary | std::ios::trunc);

	if (!file.is_open())
	{
		throw std::exception();
	}

	for (int i = 0; i < this->size; ++i)
	{
		file.write((char*)this->data[i], sizeof(this->data[i]));
	}

	file.close(); 
}

size_t Editor::getSize() const
{
	return this->size; 
} 
void Editor::edit(std::size_t offset, std::uint8_t value)
{
	if (offset > this->size)
	{
		throw std::invalid_argument("");
	}

	for (int i = 0; i < this->size; ++i)
	{
		if (offset = i)
		{
			this->data[i] = value; 
		}
	}
}
void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit)
{

}

int main(int argc, char* argv[])
{
	
	if (argv == 0)
	{
		throw std::exception(); 
	}

	
	//Editor editor = Editor(argv[0]); 

	std::string buffer; 
	cout<<"Write command:"<<endl;
	getline(cin, buffer); 

	Command line(buffer);

	if (line[0].compare("EXIT") == 0)
	{

	}
	if (line[0].compare("SIZE") == 0)
	{
		
	}



	return 0;
}