// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Василена Тодорова Кръжева
// ФН: 82183
// Специалност: Компютърни науки
// Курс: Първи
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021г.
// Начален час на контролното: 10:30ч.
// Кой компилатор използвате: GCC

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::fstream;
using std::string;
using std::vector;
using std::size_t;
using std::cin;
using std::cout;
using std::endl;
/*
basic_istream& read(char_type* s, std::streamsize count)
basic_ostream& write(const char_type* s, std::streamsize count);
basic_istream& seekg(pos_type pos);
basic_istream& seekg(off_type off, std::ios_base::seekdir dir);
basic_ostream& seekp(pos_type pos);
basic_ostream& seekp(off_type off, std::ios_base::seekdir dir);
pos_type tellg();
pos_type tellp();
*/

class Command
{
private:
	vector<string> arguments;

	void removeExcessWhiteSpaces(string& message);
	void splitMessage(string message);

public:
	Command(const char* message);

	std::size_t size() const;	//count of the arguments

	const char* operator[](size_t pos);
};

class Editor
{
private:
	fstream file;
	const char* path;
	size_t size;
	bool isOpen;

public:
	Editor();
	Editor(const char* path);
	~Editor();

	void open(const char* path);
	void close();

	bool IsOpen();
	size_t getSize();
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
};

class Processor
{
private:
	static const char* commands[];
	static const int commandsCnt = 4;
	Editor editor;

	void size();
	void edit(Command& command);
	void show(Command& command);

	Processor(){}

	~Processor()
	{
		editor.close();
	}

public:
	Processor(const Processor& other) = delete;
	Processor& operator=(const Processor& other) = delete;

	static bool is_valid(Command& command);
	static Processor& getInstance(const char* path = "file.dat")
	{
		static Processor processor;
		if(path != nullptr)
		{
			processor.editor.open(path);
		}
		return processor;
	}
	bool execute(Command& command);
};

const char* Processor::commands[] = {"EXIT", "SIZE", "EDIT", "SHOW"};


void Processor::size()
{
	cout<<editor.getSize()<<" byte(s)\n";
}
void Processor::edit(Command& command)
{
	try
	{
		editor.edit( (size_t)(command[1]), atoll(command[2]));
	}
	catch(const std::invalid_argument& e)
	{
		std::cout << e.what() << '\n';
	}
	catch(const std::logic_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
}
void Processor::show(Command& command)
{
	try
	{
		editor.display(std::cout, (size_t)(command[1]), (size_t)command[2]);
	}
	catch(const std::invalid_argument& e)
	{
		std::cout << e.what() << '\n';
	}
	catch(const std::logic_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

bool Processor::is_valid(Command& command)
{
	for (size_t i = 0; i < commandsCnt; i++)
	{
		if(strcmp(command[0],commands[i])==0)
		{
			return true;
		}
	}
	return false;
}

bool Processor::execute(Command& command)
{
	if(strcmp(commands[0], command[0]) == 0)
	{
		return false;
	}
	else if(strcmp(commands[1], command[0]) == 0)
	{
		size();
	}
	else if(strcmp(commands[2], command[0]) == 0)
	{
		edit(command);
	}
	else if(strcmp(commands[3], command[0]) == 0)
	{
		show(command);
	}
	else{
		cout<<"Command was not found!\n";
	}

	return true;
}



Editor::Editor() : isOpen(false), size(0)
{}
Editor::Editor(const char* path)
{
	open(path);
}
Editor::~Editor()
{
	if(isOpen)
		close();
}

void Editor::open(const char* path)
{
	if(isOpen)
	{
		close();
	}
	
	file.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	size = file.tellg();
	isOpen = true;
	
}
void Editor::close()
{
	if(isOpen)
	{
		file.close();
		isOpen = false;
	}
}

bool Editor::IsOpen()
{
	return isOpen;
}
size_t Editor::getSize()
{
	return size;
}
void Editor::edit(std::size_t offset, std::uint8_t value)
{
	if(offset > size)
	{
		throw std::invalid_argument("Offset is after the end of the file!");
	}
	if(!isOpen)
	{
		throw std::logic_error("File is not open!");
	}
	file.seekp(offset);
	file.write((char*)&value, sizeof(value));

	if(file.tellp() > size)
	{
		size = file.tellp();
	}
}
void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit)
{
	if(offset > size)
	{
		throw std::invalid_argument("Offset is after the end of the file!");
	}
	if(!isOpen)
	{
		throw std::logic_error("File is not open!");
	}

	file.seekg(offset);
	int dataCnt = 0;
	std::uint8_t value;
	while(!file.eof() && dataCnt <= limit)
	{
		file.read((char *)&value, sizeof(value));
		++dataCnt;

		out << std::setfill('0') << std::setw(8) << std::hex << value;
	}

}

Command::Command(const char* message)
{
	splitMessage(message);
}


void Command::removeExcessWhiteSpaces(string& message)
{
	int spaceCnt;
	for (size_t i = 0; i < message.length(); i++)
	{
		if(isspace(message[i]))
		{
			++spaceCnt;
		}
		else{
			if(spaceCnt > 1)
			{
				message.erase(message.begin() + i - spaceCnt, message.begin() + i - 1);
			}
			spaceCnt = 0;
		}
	}
	if(spaceCnt > 0)
	{
		message.erase(message.end() - spaceCnt + 1, message.end());
	}
}

void Command::splitMessage(string message)
{
	removeExcessWhiteSpaces(message);
	int from = 0;
	string temp;

	for (size_t i = 0; i < message.length(); i++)
	{
		if(isspace(message[i]) && from < i)
		{
			temp = message.substr(from, i - from);
			if(temp.compare(" ") != 0){
				arguments.push_back(temp);
			}
			from = i + 1;
		}
	}
	
	if(from < message.length())
	{
		temp = message.substr(from, message.length());
		if(temp.compare(" ") != 0){
			arguments.push_back(temp);
		}
	}
}

std::size_t Command::size() const
{
	return arguments.size();
}

const char* Command::operator[](size_t pos)
{
	assert(pos < arguments.size());
	return arguments[pos].c_str();
}


int main(int argc, char* argv[])
{
	char* path = nullptr;
	if(argc > 1){
		path = argv[1];
	}
	Processor& processor = Processor::getInstance(path);
	bool next = true;
	char* input = new char[1000];
	while(next)
	{
		cin.getline(input, 1000);
		Command c(input);
		next = processor.execute(c);
	}
	return 0;
}