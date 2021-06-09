// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Борислав Минчев
// ФН: 82126
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 29.05
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
#include <cmath>

class command
{
	std::vector<std::string> arguments;

	std::vector<std::string> splitArgs(std::string str)
	{
		std::string buffer;
		std::vector<std::string> result;
		bool seenSpace = false;
		for (std::size_t i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			{
				if (!seenSpace && !buffer.empty())
				{
					result.push_back(buffer);
					buffer.clear();
				}

				seenSpace = true;
			}
			else
			{
				seenSpace = false;
				buffer += str[i];
			}
		}
		return result;
	}
public:
	command(const char* str)
	{
		this->arguments = splitArgs(str);
	}

	std::size_t size() const
	{
		return this->arguments.size();
	}

	std::string operator[](std::size_t pos)
	{
		return this->arguments[pos];
	}
};

class editor
{

	std::fstream file;
	std::size_t fileSize;
public:
	void open(const char* path)
	{
		std::ifstream f(path);//check if file exists (does not create new file if it doesnt exist)
		if (!f)
		{
			throw std::runtime_error("File not foud:" + std::string(path));
		}
		else
		{
			f.close();
		}
		this->file.open(path, std::ios::binary |
			std::ios::in |
			std::ios::out |
			std::ios::ate);//always creates new file if it doesnt exist


	}
	void close()
	{
		this->file.close();
	}

	editor(const char* path)
	{
		open(path);
		this->fileSize = this->file.tellg();
	}

	~editor()
	{
		close();
	}
	std::size_t size()
	{
		return this->fileSize;
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		if (offset >= (this->fileSize - sizeof(value)))
		{
			throw std::invalid_argument("Invalid offset: " + std::to_string(offset));
		}

		this->file.seekp(offset, std::ios::beg);
		this->file.write((const char*)value, sizeof(std::uint8_t));
		this->file.seekp(0, std::ios::beg);
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		//std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte;
		std::size_t s = ceil(limit / 16.0);
		
		for (size_t i = 0; i < s; i++)
		{
			out << std::setfill('0') << std::setw(8) << std::hex << (unsigned int)offset;
			out << " ";
			for (std::size_t j = 0; j < 16 && limit>0; j++, limit--)
			{	
				std::uint8_t byte = 0;
				this->file.read((char*)byte, sizeof(std::uint8_t));
				out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte;
				out << " ";
			}
			out << '\n';
		}
	}
};

class processor
{
	editor editor;

	bool validNum(std::string num)
	{
		for (std::size_t i = 0; i < num.length(); i++)
		{
			if (num[i] < '0' || num[i] > '9')
			{
				return false;
			}
		}

		return true;
	}

	bool is_valid(command& command)
	{
		if (command[0] == "EXIT" && command.size() == 1)
		{
			return true;
		}
		else if (command[0] == "SIZE" && command.size() == 1)
		{
			return true;
		}
		else if (command[0] == "EDIT" && command.size() == 3)
		{
			if (validNum(command[1]) && validNum(command[2]))
			{
				if (std::stoull(command[1]) > editor.size())
				{
					throw std::runtime_error("Error file size is" + std::to_string(editor.size()));
				}
				return true;
			}
		}
		else if (command[0] == "SHOW" && command.size() == 3)
		{
			if (validNum(command[1]) && validNum(command[2]))
			{
				return true;
			}
		}
		
		return false;
	}


	
public:
	processor(const char* file) : editor(file) {}
	
	void execte(command command)
	{
		if (!is_valid(command))
		{
			throw std::runtime_error("Invalid command");
		}

		if(command[0] == "EXIT")
		{
			
		}
		else if (command[0] == "SIZE")
		{
			
		}
		else if (command[0] == "EDIT")
		{
			
		}
		else if (command[0] == "SHOW")
		{
		
		}
	}
};


void startConversation(processor& p)
{

}


int main(int argc, char** argv) 
{
	
	if (argc != 2)
	{
		std::cout << "Error ocured when program started (check arguments)";
		return 1;
	}
	processor p(argv[0]);
	startConversation(p);

	return 0;
}