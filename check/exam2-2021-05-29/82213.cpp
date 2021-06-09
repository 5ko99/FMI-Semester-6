//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Соня Николова Николова
// ФН: 82213
// Специалност: Компютърни науки
// Курс: I
// Административна група: IV
// Ден, в който се явявате на контролното: 29//05/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class command
{
private:
	std::string cmd;
	std::string cmdName;
	std::string cmdArg;
	std::vector<std::string> args;

public:
	command(const std::string &cmd);

	std::size_t size() const;
	std::string operator[](const std::size_t pos);

	std::string getCmdName() const;
};

command::command(const std::string &cmd) //works if there is only one white space between arguments
{
	this->cmd = cmd;
	const std::size_t len = this->cmd.size();

	int cntWhiteSpaces = 0;
	std::vector<int> whiteSpacePos;

	for (int i = 0; i < len; i++)
	{
		if (this->cmd[i] == ' ')
		{
			cntWhiteSpaces++;
			whiteSpacePos.push_back(i);
		}
	}

	if (cntWhiteSpaces)
	{
		int firstWhiteSpace = whiteSpacePos[0];
		std::string buffer;

		for (int i = 0; i < firstWhiteSpace; i++)
		{
			buffer[i] = this->cmd[i];
			this->cmdName.push_back(buffer[i]);
		}
		if (cntWhiteSpaces == 1)
		{
			int argLen = len - firstWhiteSpace - 1;
			int argIdx = firstWhiteSpace + 1;

			for (int j = 0; j < argLen; j++)
			{
				buffer[j] = this->cmd[argIdx];
				argIdx++;
				this->cmdArg.push_back(buffer[j]);
			}
			this->args.push_back(this->cmdArg);
		}
		else if (cntWhiteSpaces == 2)
		{
			int scndWhiteSpace = whiteSpacePos[1];
			std::string temp;

			int argLen = len - scndWhiteSpace - 1;
			int argIdx = firstWhiteSpace + 1;

			for (int j = 0; j < argLen; j++)
			{
				buffer[j] = this->cmd[argIdx];
				argIdx++;
				this->cmdArg.push_back(buffer[j]);
			}
			this->args.push_back(this->cmdArg);

			this->cmdArg.erase();
			int scndArgLen = len - argLen - 2 - this->cmdName.size();
			int scndArgIdx = scndWhiteSpace + 1;

			for (int j = 0; j < scndArgLen; j++)
			{
				temp[j] = this->cmd[scndArgIdx];
				scndArgIdx++;
				this->cmdArg.push_back(temp[j]);
			}
			this->args.push_back(this->cmdArg);
		}
	}
}
std::string command::getCmdName() const
{
	return this->cmdName;
}

std::size_t command::size() const
{
	return this->args.size();
}
std::string command::operator[](const std::size_t pos)
{
	if (pos > this->size() + 1)
	{
		throw std::invalid_argument("No such position");
	}
	else if (pos == 0)
	{
		return this->cmdName;
	}
	else
	{
		return this->args[pos - 1];
	}
}

class editor
{
private:
	std::size_t sizeOfCurrentFile;

public:
	std::fstream currentFile;
	editor(const std::string &path);
	editor();

	void open(const std::string &fileName);
	void close();

	std::size_t size() const;
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream &out, std::size_t offset, std::size_t limit);
};

editor::editor() {}
editor::editor(const std::string &path) : currentFile(path, std::ios::binary | std::ios::out | std::ios::in)
{
	if (!this->currentFile.is_open())
	{
		throw std::invalid_argument("Could not open file with given path");
	}
}

void editor::open(const std::string &fileName)
{
	std::fstream newFile(fileName, std::ios::binary | std::ios::out | std::ios::in);
	if (!newFile.is_open())
	{
		throw std::invalid_argument("Could not open file with given path");
	}
}

void editor::close()
{
	this->currentFile.close();
}

class processor
{
private:
	command cmd;

	bool is_valid(const command &cmd) const;

public:
	processor(const std::string cmd);
	void execute(const command &cmd);
};
bool processor::is_valid(const command &cmd) const
{
	return (cmd.getCmdName() == "EXIT" || cmd.getCmdName() == "SIZE" || cmd.getCmdName() == "EDIT" || cmd.getCmdName() == "SHOW");
}
processor::processor(const std::string cmd) : cmd(cmd)
{
}

int main()
{

	return 0;
}