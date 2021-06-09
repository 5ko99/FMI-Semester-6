// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Яни Енчев
// ФН: 45818
// Специалност: Информатика
// Курс: 1
// Административна група: 6
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
#include <vector>

class Command
{
public:
	Command(std::string& text);
	std::size_t size() const;
	std::string operator[](std::size_t pos);
protected:
	size_t sz;
	//std::string command;
	std::vector<std::string> commandParts;
};

class Processor : public Command
{
public:
	bool isValid();
	void execute();
	Processor(std::string& fileName, std::string& text);
private:
	Editor edit;
};

class Editor : public Command
{
public:
	void open(std::string& fileName);
	void close();
	Editor(std::string& fileName, std::string& text);
	Editor(std::string& text);
	~Editor();
	std::size_t size();
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
	void SIZE();
	void EDIT();
	//void SHOW();
private:
	std::fstream file;
	std::size_t sz;	
};

int main(int argv, std::string argc)
{

	return 0;
}

Command::Command(std::string& text)
	:sz(0)
{
	size_t len = text.length();
	bool inAString = 0;
	std::string str;

	for (size_t i = 0; i < len; ++i)
	{
		if (text[i] != ' ' && !inAString)
		{
			str.clear();
			inAString = 1;
			str += text[i];
		}

		else if (text[i] != ' ' && inAString)
			str += text[i];

		else if (text[i] == ' ' && inAString)
		{
			commandParts.push_back(str);
			this->sz++;
			inAString = 0;
			str.clear();
		}

		//else if (text[i] == ' ' && !inAString) we don't do anything in this case
	}
}

std::size_t Command::size() const
{
	return this->sz;
}

std::string Command::operator[](std::size_t pos)
{
	if (pos >= commandParts.size())
		throw std::out_of_range("Index given is out of range");

	return commandParts[pos];
}

void Editor::open(std::string& fileName)
{
	this->file.open(fileName, std::ios::binary | std::ios::in | std::ios::out);

	if (this->file.is_open())
		throw std::exception("File failed to open!");

	this->sz = this->size();
}

void Editor::close()
{
	this->file.close();
}

Editor::Editor(std::string& fileName, std::string& text)
	:Command(text)
{
	this->open(fileName);
}

Editor::Editor(std::string& text)
	:Command(text), sz(0)
{
	this->file.close();
}

Editor::~Editor()
{
	this->close();
}


std::size_t Editor::size()
{
	if (!this->file.is_open())
		throw std::exception("File is not open!!");

	file.seekg(0, std::ios::end);

	return file.tellg();
}

void Editor::edit(std::size_t offset, std::uint8_t value)
{
	if(!this->file.is_open())
		throw std::exception("File is not open!!");

	if (offset > this->size())
		throw std::invalid_argument("Offset if bigger than the size of the file!!");

	file.seekg(offset, std::ios::beg);
	file.write(reinterpret_cast<const char*>(value), sizeof(value));
}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit)
{
	if (!this->file.is_open())
		throw std::exception("File is not open!!");

	if (offset > this->size())
		throw std::invalid_argument("Offset if bigger than the size of the file!!");

	file.seekg(offset, std::ios::beg);

	for (int i = 0; i < limit && !file.eof(); i++)
	{
		char toPrint;
		file.read(&toPrint, 1);
		out << toPrint;
		file.seekg(offset + i, std::ios::beg);
	}
}

void Editor::SIZE()
{
	if (commandParts.size() != 1 || commandParts[0] != "SIZE")
		throw std::exception("An error has occured");

	std::cout << this->size();
}

void Editor::EDIT()
{
	if(commandParts.size() != 3)
		throw std::exception("An error has occured");

	const char* check = commandParts[1].c_str();
	size_t len = strlen(check);

	for (size_t i = 0; i < len; ++i)
		if (check[i] > '9' || check[i] < '0')
			throw std::invalid_argument("The argument isn't what is expected!");

	size_t num = 0;

	for (size_t i = 0; i < len; ++i)
		num += i * 10 + check[i] - '0';

	const char* check1 = commandParts[2].c_str();
	size_t len1 = strlen(check1);

	for (size_t i = 0; i < len1; ++i)
		if (check1[i] > '9' || check1[i] < '0')
			throw std::invalid_argument("The argument isn't what is expected!");

	size_t num1 = 0;

	for (size_t i = 0; i < len1; ++i)
		num1 += i * 10 + check1[i] - '0';

	try{
		edit(num, (uint8_t)num1);
	}
	catch (std::exception& e)
	{
		e.what();
	}
	catch (std::invalid_argument& ex)
	{
		ex.what();
		std::cout << "The current size of the file is ";
		std::cout << this->size();
	}
}

bool Processor::isValid()
{
	if (commandParts.size() == 0)
		return false;

	if (commandParts[0] == "EXIT" && commandParts.size() == 1)
		return true;

	if (commandParts[0] == "SIZE" && commandParts.size() == 1)
		return true;

	if (commandParts[0] == "EDIT" && commandParts.size() == 3)
		return true;

	if (commandParts[0] == "SHOW" && commandParts.size() == 3)
		return true; 

	return false;
}

void Processor::execute()
{
	if (!isValid())
		throw std::invalid_argument("The argument given is invalid");

	if (commandParts[0] == "SIZE")
		this->edit.SIZE();

	if (commandParts[0] == "EDIT")
		this->edit.EDIT();

	/*if (commandPart[0] == "SHOW")
		this->edit.SHOW();*/
}

Processor::Processor(std::string& fileName, std::string& text)
	:Command(fileName), edit(fileName,text)
{
}
