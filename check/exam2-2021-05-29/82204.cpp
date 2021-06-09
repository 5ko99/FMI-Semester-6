//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Теодор Тодоров Карушков
// ФН: 82204
// Специалност: КН
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

class Command
{
private:
	std::vector<std::string> commandArray;

	//std::size_t countWordsInString(std::string str);
	bool isCommandValid(std::string command);
	void splitCommand(std::string command);

public:
	Command(std::string command);
	std::size_t size() const;
	std::string operator[](std::size_t index);
};

std::size_t countWordsInString(std::string str)
{
	std::size_t counter = 0;
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] == ' ' && str[i - 1] != ' ')
			++counter;
		else if (i == str.length() - 1 && str[i] != ' ')
			++counter;
	}

	return counter;
}

std::size_t countLettersInString(std::string str)
{
	std::size_t i = 0;
	while (str[i])
		++i;

	return i;
}

bool Command::isCommandValid(std::string command)
{
	for (std::size_t i = 0; i < command.length(); ++i)
	{
		if (command[i] == ' ')
			return false;
	}
	return true;
}
void Command::splitCommand(std::string command)
{
	std::string tempStr;
	std::size_t i = 0;
	while (command[i] != ' ')
	{
		tempStr[i] = command[i];
		++i;
	}
	commandArray.push_back(tempStr);
}

Command::Command(std::string command)
{
	//TO DO
	//could not come up with a solution
	//splitCommand(command);
	/*std::string tempStr;
	for (std::size_t i = 0; i < command.length(); ++i)
	{
		if (command[i] != ' ')
		{
			tempStr[i] = command[i];
		}
		else if (command[i] == ' ' && command[i - 1] != ' ')
		{
			if (isCommandValid(tempStr))
			{
				commandArray.push_back(tempStr);
			}
			//tempStr = nullptr;
		}
	}*/
}

std::size_t Command::size() const
{
	return commandArray.size();
}
std::string Command::operator[](std::size_t index)
{
	return commandArray.at(index);
}

/*Класът да има предикат is_valid, която получава обект от тип command и връща true или false, 
в зависимост дали командата е коректна или в нея има грешка.
Класът да има функция execute, която получава команда и я изпълнява.
Класът да не изпълнява командите директно, нито да работи директно с файла, а вместо това да работи с обект от класа editor.
Класът трябва да прихваща възможни изключения хвърлени от editor и когато е нужно да извежда съобщение за грешка.*/
class Processor
{
private:
	bool isValid(Command &command);

public:
	void execute(Command &command);
};

// helper func
std::string strToUpperCase(std::string str)
{
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] += 'A' - 'a';
		}
	}
	return str;
}
bool Processor::isValid(Command &command)
{
	if (strToUpperCase(command[0]) == "EXIT")
	{
		return true;
	}
	else if (strToUpperCase(command[0]) == "SIZE")
	{
		return true;
	}
	else if (strToUpperCase(command[0]) == "EDIT")
	{
		return true;
	}
	else if (strToUpperCase(command[0]) == "SHOW")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Processor::execute(Command &command)
{
	//Editor myEditor();
}

/*
- Класът да има функции open, close, с които да може да отваря и затваря файл. Ако отварянето на файл пропадне, да се хвърля изключение. 
Функциите на класа, чрез които се работи с файл, могат да работят само ако има успешно отворен файл.
- Отварянето на файл трябва да може да се направи и при създаване на обект от тип editor. За целта класът да има конструктор, 
който получава път до файл и го отваря.
- Файлът да се отваря в двоичен режим и да се държи отворен до извикване на close или до унищожаване на обекта от тип editor.
- При отварянето на файл, класът да намира размера му и да го запазва в private променлива от тип std::size_t. 
За намирането на размера да се използва техниката със seek/tell, която разглеждахме на лекциите.
- Класът да има функция size, която връща размера му като стойност от тип std::size_t.
- Класът да има функция edit(std::size_t offset, std::uint8_t value). Тя записва стойността value на позиция offset спрямо началото на файла.
Ако offset се намира след края на файла, функцията да не прави нищо, а да хвърля изключение от тип std::invalid_argument.
- Класът да има функция display(std::ostream& out, std::size_t offset, std::size_t limit). 
Функцията извежда, на потока <out>, подобно на шестнадесетичен редактор, съдържанието на файла, започвайки от позиция <offset>. 
Извежданато да приключи или когато се изведат точно <limit> на брой байта, или се достигне краят на файла. 
Ако позицията <offset> се намира след края на файла, да не се извеждат нищо, а да се хвърли изключение от тип std::invalid_argument. 
За точния формат, в който да се извеждат данните, вижте описанието на командата SHOW по-долу.*/
class Editor
{
	std::fstream file;

public:
	Editor(std::string path);

	void open(std::string path);
	void close();

	std::size_t size() const;

	void edit(std::size_t offset, std::uint8_t value);
	void displaydisplay(std::ostream &out, std::size_t offset, std::size_t limit);
};

Editor::Editor(std::string path) : file(path.c_str(), std::ios::binary)
{
}

void Editor::open(std::string path)
{
	file.open(path.c_str(), std::ios::binary);

	if (!file.is_open())
		throw std::invalid_argument("Cannot open file");
}
void Editor::close()
{
	file.close();
}

int main(int argc, char **argv)
{
	//std::string testCounter = "asd1 asd2 asd3";
	//std::cout << countWordsInString(testCounter);
	std::string substrTest = "asd1 asd2 asd3";
	std::cout << substrTest.substr(4);
	std::string lettersTest = "asd";
	std::cout << '\n'
			  << countLettersInString(lettersTest);
	//Command test1("test1 test2 test3");
	//std::cout << test1[1];
	//std::string test = "asd";
	//strToUpperCase(test);
	//std::cout << test;

	return 0;
}