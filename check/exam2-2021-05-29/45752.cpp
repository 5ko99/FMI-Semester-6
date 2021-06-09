// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Александър Михайлов Тангълов
// ФН: 45752
// Специалност: Информатика
// Курс: 1
// Административна група: 2
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

class command {
private:
	std::string commandText;
	std::vector<std::string> arguments;
public:
	command(std::string commandText) : commandText(commandText)
	{
		std::string word;
		for (int i = 0; i < commandText.size(); i++)
		{
			if (!isspace(commandText[i]))
			{
				word += commandText[i];
			}
			else
			{
			    arguments.push_back(word);
				word.clear();
            }
		}
		arguments.push_back(word);
		word.clear();
	}

	std::size_t size() const
	{
		return arguments.size() - 1;
	}

	std::string operator[](std::size_t pos)
	{
		return arguments[pos];
	}

};

class editor {
private:
	std::size_t fileSize;
protected:
	std::fstream File;	
public:
	editor(std::string path, std::ios_base::openmode mode)
	{
		open(path, mode);
		if (mode & std::ios_base::out)
		{
			File.seekp(File.end);
			fileSize = File.tellp();
		}
		if (mode & std::ios_base::in)
		{
			File.seekg(File.end);
			fileSize = File.tellg();
		}
	}

	std::size_t size()
	{
		return sizeof(*this);
	}

	void open(std::string path, std::ios_base::openmode mode)
	{
		try
		{
			File.open(path);

			if (!File)
			{
				throw std::runtime_error("Cannot open file");
			}
		}
		catch (const std::runtime_error& re)
		{
			std::cerr << re.what();
		}
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		try
		{
			File.seekp(offset);
			File.write((const char*)value, sizeof(value));
			if (offset > fileSize)
			{
				throw std::invalid_argument("Position is outside the file");
			}
		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << ia.what();
		}
	}

	void close(std::fstream File)
	{
		File.close();
	}
};

class processor: public editor {
public:
	processor(std::string path, std::ios_base::openmode mode) : editor(path, mode) {}
	
	bool is_valid(command command)
	{
		if (strcmp(command[0].c_str(), "EXIT") || strcmp(command[0].c_str(), "SIZE")
			|| strcmp(command[0].c_str(), "EDIT") || strcmp(command[0].c_str(), "SHOW"))
		{
			return false;
		}
		if (!strcmp(command[0].c_str(), "EXIT") || !strcmp(command[0].c_str(), "SIZE"))
		{
			if (command.size() > 0)
			{
				return false;
			}
		}
		if (!strcmp(command[0].c_str(), "EDIT") || !strcmp(command[0].c_str(), "SHOW"))
		{
			for (int i = 0; i < command[1].size(); i++)
			{
				if (!isdigit(command[1][i]))
				{
					return false;
				}
			}
			for (int i = 0; i < command[2].size(); i++)
			{
				if (!isdigit(command[2][i]))
				{
					return false;
				}
			}
			if (command.size() > 2)
			{
				return false;
			}
		}
		return true;
	}

	void execute(command command)
	{
		if (is_valid(command))
		{
			if (!strcmp(command[0].c_str(), "EXIT"))
			{
				File.close();
			}
			if (!strcmp(command[0].c_str(), "EDIT"))
			{
				edit(stoi(command[1]), stoi(command[2]));
			}
		}
	}
};



int main()
{
	

	return 0;
}