// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Николай Манански
// ФН: 45774
// Специалност: Информатика
// Курс:1
// Административна група:3
// Ден, в който се явявате на контролното: 29.05.21
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#include <cassert>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class command
{
private:
	std::string cmd;
	std::string args;
public:
	command(std::string command)
	{
		for (size_t i = 0; i < command.size(); i++)
		{
			if (command[i] == ' ')
			{
				this->cmd = command.substr(0, i);
				this->args = command.substr(i);
			}
		}
	}

	std::size_t size() const
	{
		int countArgs = 0;

		for (size_t i = 0; i < args.size(); i++)
		{
			if (args[i] == ' ')
			{
				countArgs++;
			}
		}
		countArgs++;
		return countArgs;
	}

	std::string operator[](std::size_t index)
	{
		int j = 0;
		if (index == 0)
		{
			return this->cmd;
		}
		else
		{
			for (size_t i = 0; i < args.size(); i++)
			{
				if (args[i] == ' ')
				{
					index--;
					if (index == 0)
					{
						return args.substr(j, i - j);
					}
					j = i + 1;
				}
			}

			return args.substr(j, args.size() - j);
		}
	}

	std::string returnCmd()
	{
		return cmd;
	}
};

class processor:public command
{
private:

public:
	bool is_valid(command cmd)
	{
		if (cmd.returnCmd() == "EXIT" && cmd.size() == 0)
		{
			return true;
		}
		else if (cmd.returnCmd() == "SIZE" && cmd.size() == 0)
		{
			return true;
		}
		else if (cmd.returnCmd() == "EDIT" && cmd.size() == 2)
		{
			return true;
		}
		else if (cmd.returnCmd() == "SHOW" && cmd.size() == 2)
		{
			return true;
		}
		return false;
	}

	/*void execute(command cmd)
	{

	}*/
};

class editor
{
private:
	std::size_t size;
	std::ofstream File;
public:
	editor(const char* filename)
	{
		File.open(filename);
	}

	void open(const char* filename)
	{
		std::ofstream File;
		File.open(filename, std::ios::out | std::ios::binary);
		if (!File.is_open())
		{
			throw std::runtime_error("Cannot open the file!");
		}
	}

	void close()
	{
		File.close();
	}

	~editor()
	{
		close();
	}

	//std::size_t size()
	//{
	//	return this->size;
	//}
};

int main()
{
	std::cout << "Hello World!\n";
	return 0;
}

//EXIT
//Затваря файла и излиза от програмата.
//
//SIZE
//Извежда на екрана размера на файла в брой байтове.
//
//EDIT <offset> <byte>
//Записва стойността <byte> на позиция <offset> във файла.Да се извежда текст "ОК" или "Fail", в зависимост от това записът е бил успешен.Ако позицията <offset> се намира след края на файла, да се изведе съобщение, което уведомява потребителя колко е размерът на файла.Както <byte>, така и <offset> да се въвеждат като числа в десетичен запис.
//
//SHOW <offset> <limit> Извежда на екрана, подобно на шестнадесетичен редактор, съдържанието на файла, започвайки от позиция <offset>.Извежданато да приключи или когато се изведат <limit> на брой байта, или се достигне края на файла.Ако позицията <offset> се намира след края на файла, да не се извеждат байтове, а вместо това да се изведе съобщение, което уведомява потребителя колко е размерът на файла.Както <offset>, така и <limit> да се въвеждат като числа в десетичен запис.