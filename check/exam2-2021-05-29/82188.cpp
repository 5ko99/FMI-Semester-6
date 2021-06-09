// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Пламен Стефанов Берберов
// ФН: 82188
// Специалност: Компютърни науки
// Курс: 1ви
// Административна група: 3та
// Ден, в който се явявате на контролното: 29.05.2021 
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++ (MSVC)
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


enum CommandType
{
	EXIT,
	SIZE,
	EDIT,
	SHOW,
	INVALID = -1
};

class command
{
	CommandType _type;
	std::vector<std::string> _data;
	bool is_whitespace(char c)
	{
		return c == ' ' || c == '\n' || c == '\t';
	}

public:
	command(std::string data)
	{
		std::string buffer = "";
		for (size_t k = 0;  k < data.length(); k++)
		{
			if (is_whitespace(data[k]))
			{
				if (k > 0 && is_whitespace(data[k - 1]))
				{
					continue;
				}
				else
				{
					this->_data.push_back(buffer);
					buffer = "";
				}
			}
			else
			{
				buffer += data[k];
			}

			if (k == data.length() - 1)
			{
				this->_data.push_back(buffer);
			}
		}

		if (_data[0] == "SHOW")
		{
			this->_type = SHOW;
		}
		else if (_data[0] == "EXIT")
		{
			this->_type = EXIT;
		}
		else if (_data[0] == "SIZE")
		{
			this->_type = SIZE;
		}
		else if (_data[0] == "EDIT")
		{
			this->_type = EDIT;
		}
		else
		{
			this->_type = INVALID;
		}
	}
	std::string operator[](size_t index)
	{
		return this->_data[index];
	}

	CommandType type() const
	{
		return this->_type;
	}

	size_t size() const
	{
		return this->_data.size() - 1;
	}
};

class editor
{
	std::fstream _file;
	size_t _size;
public:
	editor()
	{
		this->_file = std::fstream();
		this->_size = 0;
	}
	editor(std::string path)
	{
		open(path);
	}
	~editor()
	{
		close();
	}

	void open(std::string path)
	{
		this->_file = std::fstream(path, std::ios::out | std::ios::binary | std::ios::in);
		if (this->_file.is_open())
		{
			_file.seekg(0, _file.end);
			_size = _file.tellg();
		}
		else
		{
			throw std::exception();
		}
	}

	void close()
	{
		this->_file.close();
		if (!this->_file.is_open())
		{
			this->_size = 0;
		}
	}

	const size_t size() const
	{
		return this->_size;
	}

	bool edit(size_t offset, std::uint8_t value)
	{
		if (offset > this->_size)
		{
			throw std::invalid_argument("Offset out of file");
		}

		_file.seekp(offset, _file.beg);
		_file.write((char*)&value, sizeof(std::uint8_t));

		_file.seekg(0, _file.end);
		_size = _file.tellg();
	}

	void display(std::ostream& out, size_t offset, size_t limit)
	{
		_file.seekg(offset, std::ios::beg);

		for (size_t k = 0; k < limit; k++)
		{
			std::uint8_t byte;
			_file.read((char*)&byte, sizeof(std::uint8_t));

			std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte << std::endl;

			if (!_file.good())
			{
				break;
			}
		}

		std::cout << std::dec;
	}
};

class processor
{
	processor()
	{
	}
public:
	static bool is_valid(command& command)
	{
		if (command.type() == CommandType::INVALID)
		{
			return false;
		}
	}
	static bool execute(command& command, editor& editor)
	{
		if (is_valid(command))
		{
			try
			{
				switch (command.type())
				{
				case EXIT:
					editor.close();
					return false;
					break;
				case SIZE:
					std::cout << editor.size() << std::endl;
					return true;
					break;
				case EDIT:
					{
						size_t offset = std::stoul(command[1].c_str());
						std::uint8_t byte = std::stoul(command[2].c_str());
						try
						{
							std::cout << (editor.edit(offset, byte) ? "OK" : "Fail") << std::endl ;
						}
						catch (std::invalid_argument& e)
						{
							std::cerr << e.what() << ": filesize = " << editor.size();
						}
						return true; 
					}
					break;
				case SHOW:
					{
						size_t offset = std::stoul(command[1].c_str());
						size_t limit = std::stoul(command[2].c_str());
						editor.display(std::cout, offset, limit);
						return true;
					}
					break;
				}
			}
			catch (...)
			{
				std::cerr << "Something went wrong when executing the command" << std::endl;
			}
		}
	}
};

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << "No file path specified" << std::endl;
		return -1;
	}
	std::string path(argv[1]);
	editor* edit;
	try
	{
		edit = new editor(path);
	}
	catch (...)
	{
		std::cerr << "File couldn't be opened" << std::endl;
		return -1;
	}

	bool continueExecution = true;
	while (continueExecution)
	{
		std::string buffer;
		std::getline(std::cin, buffer);
		command com(buffer);
		processor::execute(com, *edit);
	}

	delete edit;
	return 0;
}