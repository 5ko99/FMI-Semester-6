// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Филип Карастоянов
// ФН: 45757
// Специалност: Информатика
// Курс:1
// Административна група:2
// Ден, в който се явявате на контролното:29.05.2021 
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
class Command
{
public:
	Command(std::string _command) : command(_command)
	{
		divideString();
	};
	size_t size() const
	{
		return commandArray.size();
	}
	std::string operator[](size_t index)
	{
		return commandArray.at(index);
	}
	void print()
	{
		for (unsigned i = 0; i < commandArray.size(); i++)
		{
			std::cout << commandArray[i] << " ";
		}
	}

private:
	void divideString()
	{   
		
		std::string newString;
		for (unsigned i = 0; i <= command.size(); i++)
		{
			if (command[i] == ' ' || i == command.size())
			{
				commandArray.push_back(newString);
				newString.clear();
				
			}
			else
			{
				newString.push_back(command[i]);
			}
		}
	}
	std::string command;
	std::vector <std::string> commandArray;
};



class Editor
{
public:
	Editor() = default;
	Editor(char *fileAddress)
	{
		workingFile.open(fileAddress, std::ios::binary , std::ios_base::app);
		workingFile.seekg(workingFile.end);
		_size = workingFile.tellg();
	};
	void open(std::string fileAddress)
	{
		if (workingFile.is_open())
		{
			std::cout << "File already opened" << '\n';
		}
		else
		{
			workingFile.open(fileAddress, std::ios::binary , std::ios_base ::app);
			std::cout << "File opened!" << '\n';
			workingFile.seekg(workingFile.end);
			_size = workingFile.tellg();
		}
	}
	void close()
	{
		if (!workingFile.is_open())
		{
			std::cout << "File already closed" << '\n';
		}
		else
		{
			workingFile.close();
			std::cout << "File closed" << '\n';
		}
	}
	size_t size() const
	{
		return _size;
	}
	void edit(size_t offset, uint8_t value)
	{
		if (offset > _size) throw std::invalid_argument("invalid argument");
		workingFile.seekp(offset, std::ios_base::beg);
		workingFile << value;

	}
	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (offset > _size) throw std::invalid_argument("invalid argument");
		workingFile.seekg(offset, std::ios_base::beg);
		while (workingFile.tellg() != limit || workingFile.eof())
		{
			
		}
	}
	~Editor()
	{
		if (workingFile.is_open())
		{
			workingFile.close();
		}
	}
private:
	std::fstream workingFile;
	size_t _size;

};

class Processor
{
public:
	bool is_valid(Command& command)
	{
		if (command[0] == "EXIT") return 1;
		if (command[0] == "SHOW") return 1;
		if (command[0] == "EDIT") return 1;
		if (command[0] == "SIZE") return 1;


		return 0;
	}
	void execute(Command& command , Editor& editor)
	{
		if (command[0] == "SIZE")
		{
			std::cout<< "file size is : " << editor.size() << '\n';
		}
		if (command[0] == "EDIT")
		{
			try
			{
				editor.edit(strtoull(command[1].c_str(),nullptr,10) , strtoull(command[2].c_str(),nullptr,10));
			}
			catch (std::invalid_argument)
			{
				std::cout << "Error!";
			}
		}
		if (command[0] == "EXIT")
		{
			std::cout << "Exiting the program...";
		}
		if (command[0] == "SHOW")
		{
			try
			{
				editor.display(std::cout, strtoull(command[1].c_str(), nullptr, 10), strtoull(command[2].c_str(), nullptr, 10));
			}
			catch(std::invalid_argument)
			{
				std::cout << "Error!";
			}
		}
	}


private:

};
int main(int argc,char *argv[])
{
	std::string inputCommand;
	Editor editor(argv[1]);
	Processor processor;
	
	while (inputCommand != "EXIT")
	{
		std::cin >> inputCommand;
		Command command(inputCommand);
		processor.execute(command, editor);
	}
	
	
	return 0;
}

