//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Веселин Ангелов
// ФН: 82185
// Специалност: КН
// Курс: I
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: gcc
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class Command
{
private:
	std::string m_command;
	std::vector<std::string> m_arrArgs;
	std::size_t m_argsCount;

	void splitByWhiteSpaces()
	{
		for (int i = 0; i < this->m_command.length(); i++)
		{
			int delimiterIndex = m_command.find(' ', i);
			if (delimiterIndex == -1)
			{
				m_arrArgs.push_back(m_command.substr(i, m_command.length() - i));
				break;
			}
			else
			{
				std::string temp = m_command.substr(i, delimiterIndex - i);
				m_arrArgs.push_back(temp);
				i += temp.length();
			}
			m_argsCount++;
		}
	}

public:
	Command(std::string userCommand)
	{
		this->m_command = userCommand;
		this->m_argsCount = 0;
		splitByWhiteSpaces();
	}
	std::size_t size() const
	{
		return this->m_argsCount - 1;
	}
	std::string &operator[](std::size_t index)
	{
		return this->m_arrArgs.at(index);
	}
};

class Editor
{
private:
	std::size_t m_size;
	std::istream *m_streamReader;
	std::ostream *m_streamWriter;

	void checkSize()
	{
		this->m_streamReader->seekg(std::ios::end);
		this->m_size = this->m_streamReader->tellg();
	}

public:
	Editor(std::string path)
	{
		this->m_streamReader = new std::ifstream(path, std::ios::binary | std::ios::in);
		this->m_streamWriter = new std::ofstream(path, std::ios::binary | std::ios::out);
		if (!m_streamReader->good())
		{
			throw std::exception();
		}
		checkSize();
	}
	~Editor()
	{
		delete this->m_streamReader;
		delete this->m_streamWriter;
	}
	void open(std::string path)
	{
		this->m_streamReader = new std::ifstream(path, std::ios::binary | std::ios::in);
		this->m_streamWriter = new std::ofstream(path, std::ios::binary | std::ios::out);
		if (!m_streamReader->good())
		{
			throw std::exception();
		}
		checkSize();
	}
	void close()
	{
		this->m_streamReader = nullptr;
		this->m_streamWriter = nullptr;
	}
	std::size_t size() const
	{
		return this->m_size;
	}
	edit(std::size_t offset, std::uint8_t value)
	{
		m_streamReader->seekg(std::ios::end);
		std::size_t index = m_streamReader->tellg();
		if (offset > index)
		{
			throw std::invalid_argument("Invalid index");
		}
		else
		{
			m_streamWriter->seekp(std::ios::beg);
			m_streamWriter->write((const char *)&value, sizeof(value));
		}
	}
	display(std::ostream &out, std::size_t offset, std::size_t limit)
	{
		m_streamReader->seekg(std::ios::end);
		std::size_t index = m_streamReader->tellg();
		if (offset > index)
		{
			throw std::exception();
		}
		else
		{
		}
	}
};
class Processor
{
private:
	Editor *editor;


public:
	Processor(Editor &editor)
	{
		this->editor = &editor;
	}
	void execute(std::string command)
	{
		Command cmd(command);
		if (cmd[0] == "SIZE")
		{
			std::cout<<"SIZE: "<<this->editor->size()<<std::endl;
		}
		else if (cmd[0] == "SHOW")
		{
		}
		else if (cmd[0] == "EDIT")
		{
			try
			{
				//editor->edit();
			}
			catch(const std::invalid_argument& e)
			{
				std::cout<<e.what();
			}
			
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}
};

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		Editor editor(argv[0]);
		Processor p(editor);
		std::string user_input;
		while (true)
		{
			std::getline(std::cin, user_input);
			Command cmd(user_input);
			if (cmd[0] == "EXIT")
			{
				break;
			}
			else if (cmd[0] == "SHOW")
			{
			}
			else if (cmd[0] == "EDIT")
			{
			}
			else if (cmd[0] == "SIZE")
			{
			}
			else
			{
				std::cout << "Invalid command!" << std::endl;
			}
		}
		return 0;
	}
	else
	{
		std::cout << "No valid path!" << std::endl;
		return -1;
	}
}