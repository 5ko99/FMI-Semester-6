// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Петър Стоянов Овчаров
// ФН: 45805
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: <9:08>
// Кой компилатор използвате: <Visual C++>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
enum CommandType { EXIT = 0, SIZE = 1, EDIT = 2, SHOW = 3 };
/*
 Напишете клас command, който представя команда.

Класът трябва да има подходящ конструктор,
в който да получава символен низ -- текстът на командата.

Вътрешно класът трябва да разбие низа на части
-- името на командата и нейните аргументи.

Класът да има функция std::size_t size() const, която връща броя на аргументите.

Класът да предефинира operator[] така,
че с него да могат да се извличат частите на командата
. Операторът ще получава стойност от тип std::size_t.
Тази стойност указва индекса на дума в командата
(т.е. 0 - името на командата, 1 - първият ѝ аргумент и т.н.).
*/
class command
{
	string* arguments = nullptr; // {name-0,arg1-1,arg2-2,...}
	size_t argSize = 0;
	size_t strArgCount(const char* str)
	{
		size_t spaces = 0;
		size_t length = strlen(str);
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] == ' ')
			{
				spaces++;
			}
		}
		return spaces + 1;
	}
	const char* getArgFromIndex(const char* str, size_t& from)
	{
		if (from > strlen(str))
		{
			return "";
		}
		string s = "";
		while (str[from] != ' ')
		{
			s += str[from];
			from++;//todo check if ' ' is added at the end
		}
		from++;
		return s.c_str();
	}
	CommandType m_type = EXIT;
	void setType(string t)
	{
		if (t.compare("EXIT"))
		{
			m_type = EXIT;
		}
		else if (t.compare("SIZE"))
		{
			m_type = SIZE;
		}
		else if (t.compare("EDIT"))
		{
			m_type = EDIT;
		}
		else if (t.compare("SHOW"))
		{
			m_type = SHOW;
		}
	}
public:
	command(const char* cmdStr)
	{
		if (!cmdStr)
		{
			throw invalid_argument("cmdStr is nullptr");
		}
		size_t argCnt = strArgCount(cmdStr);
		this->arguments = new string[argCnt];//char** newArguments = new char* [argCnt];
		this->argSize = argCnt;
		size_t fromIndex = 0;
		for (size_t i = 0; i < argCnt; i++)
		{
			while (cmdStr[fromIndex] != ' ' && fromIndex < strlen(cmdStr))
			{
				this->arguments[i].push_back(cmdStr[fromIndex]);
				fromIndex++;
			}
			fromIndex++;
		}
		this->setType(this->arguments[0]);
	}
	command(const command& other)
	{
		size_t argCnt = other.size();
		string* s = new string[argCnt];
		delete[] this->arguments;
		this->arguments = s;
		for (size_t i = 0; i < argCnt; i++)
		{
			this->arguments[i] = other.arguments[i];
		}
		this->argSize = argCnt;
		this->setType(this->arguments[0]);

	}
	command& operator=(const command& other)
	{
		if (this != &other)
		{
			size_t argCnt = other.size();
			string* s = new string[argCnt];
			delete[] this->arguments;
			this->arguments = s;
			for (size_t i = 0; i < argCnt; i++)
			{
				this->arguments[i] = other.arguments[i];
			}
			this->argSize = argCnt;
			this->setType(this->arguments[0]);
		}
		return *this;
	}
	~command()
	{
		delete[] this->arguments;
	}
	size_t size() const { return this->argSize; }
	size_t type() const
	{
		return this->m_type;
	}
	const string& operator[](size_t index)
	{
		if (index > this->argSize)
		{
			throw out_of_range("Index is out of range!");
		}
		return this->arguments[index];
	}
};

/*
Напишете клас editor, който изпълнява операции с файлове.

Класът да има функции open, close,
с които да може да отваря и затваря файл.

	Ако отварянето на файл пропадне, да се хвърля изключение.
	Функциите на класа, чрез които се работи с файл,
	могат да работят само ако има успешно отворен файл.

	Отварянето на файл трябва да може да се направи
	и при създаване на обект от тип editor.
	За целта класът да има конструктор, който получава път до файл и го отваря.

	Файлът да се отваря в двоичен режим и да се държи отворен до извикване на
	close или до унищожаване на обекта от тип editor.

	При отварянето на файл, класът да намира размера му
	и да го запазва в private променлива от тип std::size_t.
	За намирането на размера да се използва техниката със seek/tell,
	която разглеждахме на лекциите.

	функция size, която връща размера му като стойност от тип std::size_t.

	функция edit(std::size_t offset, std::uint8_t value).
	Тя записва стойността value на позиция offset спрямо началото на файла.

	Ако offset се намира след края на файла, функцията да не прави нищо,
	а да хвърля изключение от тип std::invalid_argument.

функция display(std::ostream& out, std::size_t offset, std::size_t limit).

Функцията извежда, на потока <out>,
подобно на шестнадесетичен редактор,
съдържанието на файла, започвайки от позиция <offset>.

	Извежданато да приключи или когато се изведат точно <limit> на брой байта,
	или се достигне краят на файла.
	Ако позицията <offset> се намира след края на файла,
	да не се извеждат нищо, а да се хвърли изключение от тип std::invalid_argument.

За точния формат, в който да се извеждат данните,
вижте описанието на командата SHOW по-долу.
*/
class editor
{
	fstream file;
	size_t fileSize = 0;
	bool isOpen = false;
	size_t getFileSize(const char* path)
	{
		ifstream f;
		size_t s = 0;
		f.open(path, ios::ate | ios::binary);
		if (f.is_open())
		{
			s = f.tellg();
		}
		f.close();
		return s;
	}
public:
	editor() {}
	editor(const char* path)
	{
		this->open(path);
	}
	void open(const char* path)
	{
		this->file.open(path);
		if (this->file.is_open())
		{
			this->isOpen = true;
			this->fileSize = this->getFileSize(path);
		}
		else
		{
			throw exception("Could not open this file!");
		}
	}
	void close()
	{
		this->isOpen = false;
		this->file.close();
	}
	~editor()
	{
		this->close();
	}
	size_t size() const { return this->fileSize; }
	void edit(std::size_t offset, std::uint8_t value)
	{
		if (offset > this->fileSize)
		{
			throw invalid_argument("invalid offset!");
		}
		this->file.seekg(0, ios::beg);
		file << value;
	}
	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (offset > this->fileSize)
		{
			throw invalid_argument("invalid offset!");
		}
		size_t cnt = 0;
		while (cnt < limit)
		{
			if (file.eof())
			{
				return;
			}
			out << file.get();
		}
	}
};
/*
Напишете клас processor, който изпълнява команди.
Класът да не изпълнява командите директно,
нито да работи директно с файла, а вместо това да работи с обект от класа editor.

Класът трябва да прихваща възможни изключения хвърлени от editor
и когато е нужно да извежда съобщение за грешка.
///////////
	Класът да има предикат is_valid,
	която получава обект от тип command и връща true или false,
	в зависимост дали командата е коректна или в нея има грешка.

Класът да има функция execute, която получава команда и я изпълнява.
*/
class processor
{
public:
	processor() {}
	bool is_valid(const command& cmd)
	{
		//if not valid return false
		switch (cmd.type())
		{
		case EXIT:
			return true;
		case SIZE:
			return true;
		case EDIT:
			return true;
		case SHOW:
			return true;
		default:
			return false;
		}
	}
	int execute(const command& cmd, const editor& ed)
	{
		//execute
		if (this->is_valid(cmd))
		{
			switch (cmd.type())
			{
			case EXIT:
				return - 1;
				break;
			case SIZE:
				return 0;
				break;
			case EDIT:
				break;
			case SHOW:
				break;
			default:
				break;
			}
		}
		else
		{
			throw exception("invalid comand!");
		}
	}
};
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "No file path!" << endl;
		return -1;
	}
	try
	{
		editor e(argv[1]);
		string str;
		do
		{
			getline(cin, str);
			command cmd(str.c_str());
			processor p();
			int c = p.execute(cmd,e);
			if (c == -1)
			{
				return 0;
			}
			else
			{

			}
		} while (true);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return -1;
	}
	command c("cmd this is a cmd");
	//cout << c.size();
	for (size_t i = 0; i < c.size(); i++)
	{
		cout << c[i] << endl;
	}
	/*
	*/

	return 0;
}
