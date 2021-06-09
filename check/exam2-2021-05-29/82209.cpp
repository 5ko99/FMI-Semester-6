// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Делчо Христов Дичев
// ФН: 82209
// Специалност: КН
// Курс: Първи
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string toLower(std::string stringToLower);
//------------------------------------------------------------------------------------------

class Command
{
protected:
	std::string commandText;
	std::vector<std::string> commandArguments;
	std::size_t numberOfArguments{};
	std::string removeWhitespaces(size_t& pos);
	void dissolve();
public:
	Command(const std::string _commandText);
	std::size_t size() const;
	std::string operator[](std::size_t position);
};

Command::Command(const std::string _commandText)
	:commandText(_commandText)
{
}

std::size_t Command::size() const
{
	return numberOfArguments;
}

std::string Command::operator[](std::size_t position)
{
	//assert(position <= commandArguments.size());
	return commandArguments[position];
}

void Command::dissolve()
{
	size_t index{}, i = 0;
	std::string temp;
	for (i; commandText[i] == ' '; i++) {}
	while (commandText[i] != '\0')
	{
		commandArguments.push_back(removeWhitespaces(i));
		i++;
	}
}

std::string Command::removeWhitespaces(size_t& pos)
{
	size_t startIndex, finalIndex, i;
	for (i = pos; commandText[i] == ' '; i++) {}
	startIndex = i;
	finalIndex = i;
	while (commandText[i] != ' ')
	{
		finalIndex++;
	}
	return commandText.substr(startIndex, finalIndex);
}

//------------------------------------------------------------------------------------------

class Editor
{
protected:
	std::fstream file;
	std::size_t fileSize{};
public:
	Editor(const std::string filePath);
	void open(const std::string filePath);
	void close();
	std::size_t size();
	bool getFileState();
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
	~Editor();
};

Editor::Editor(const std::string filePath)
{
	file.open(filePath, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "There is a problem with opening the file ";
	}
}

void Editor::open(const std::string filePath)
{
	if (!file.is_open())
	{
		file.open(filePath, std::ios::binary);
		if (file.is_open())
		{
			throw std::exception("The file can not be opened");
		}
	}
	else
	{
		std::cout << "The file is already opened";
	}
}

void Editor::close()
{
	if (file.is_open())
	{
		file.close();
		if (file.bad())
		{
			throw std::exception("The file can not be closed");

		}
	}
	else
	{
		std::cout << "The file is already closed";
	}
}

std::size_t Editor::size()
{
	//can be done with opening the file with ate and get the position of g(tellg()) because in this mode it tis positioned at the end of the file
	long currentIndex = file.tellg();
	file.seekg(0, std::ios::beg);
	std::size_t size = file.tellg();
	file.seekg(currentIndex, std::ios::beg);
	return size;
}

bool Editor::getFileState()
{
	return file.is_open();
}

Editor::~Editor()
{
	if (file.is_open())
	{
		file.close();
		if (file.bad())
		{
			std::cerr << "There is a problem with closing the file ";
		}
	}
	else
	{
		std::cout << "The file is already closed";
	}
}

//------------------------------------------------------------------------------------------

class Processor
{
private:
	Editor fileEditor;
public:
	static bool isValid(Command commandToExamine);
	static void execute(Command commandToExecute);
	void exit();
};

bool Processor::isValid(Command commandToExamine)
{
	return (toLower(commandToExamine[0]) == "exit" || toLower(commandToExamine[0]) == "size" || toLower(commandToExamine[0]) == "edit" || toLower(commandToExamine[0]) == "show");
}

void Processor::execute(Command commandToExecute)
{
	if (!isValid(commandToExecute))
	{
		std::cerr << "Unknown command";
	}
	/*else
	{
		if (toLower(commandToExecute.operator[](0))=="exit")
		{

		}
		else if (toLower(commandToExecute.operator[](0)) == "show")
		{

		}
		else if (toLower(commandToExecute.operator[](0)) == "edit")
		{

		}
		else if (toLower(commandToExecute.operator[](0)) == "size")
		{

		}
		else
		{

		}
	}*/

}

void Processor::exit()
{
	try
	{
		fileEditor.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	
}
//------------------------------------------------------------------------------------------

//function for lower casing in order not to be dependent
std::string toLower(std::string stringToLower)
{
	int index = 0;
	while (stringToLower[index] != '\0')
	{
		if (stringToLower[index] >= 'A' && stringToLower[index] <= 'Z')
		{
			stringToLower[index] = stringToLower[index] - 'A' + 'a';
		}
		index++;
	}
	return stringToLower;
}

int main(int argc, char* argv[])
{
	/*try
	{
		Editor activeFile(argv[1]);
		if (!activeFile.getFileState())
		{
			std::cerr << "There is a problem with opening the file";
			return -1;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	catch (...)
	{
		std::cerr << "Unknown problem";
	}*/
	

	std::string userCommand;
	do
	{
		//reading with white spaces
		getline(std::cin, userCommand);

		//Processor::execute(Command::Command(userCommand));
	} 
	while (toLower(userCommand) != "exit");
	return 0;
}