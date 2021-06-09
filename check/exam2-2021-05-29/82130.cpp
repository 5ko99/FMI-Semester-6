// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Цветелин Костадинов Цецков
// ФН: 82130
// Специалност: КН
// Курс: 1
// Административна група: 1
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

#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstddef>

class Command
{
public:
	Command(const std::string& text)
	{
		std::stringstream ss(text);
		ss >> command;
		while (ss)
		{
			std::string arg;
			ss >> arg;
			argv.push_back(arg);
		}
	}

	// Returns the cound of the args
	std::size_t size() const { return argc; }

	const std::string& operator[](std::size_t idx) const
	{
		assert(idx <= argc);
		return idx == 0 ? command : argv[idx - 1];
	}
private:
	std::string command;
	std::size_t argc;
	std::vector<std::string> argv;
};

class Editor
{
public:
	Editor()
	{
		fileOpen = false;
	}

	Editor(const std::string& filepath)
	{
		open(filepath);
	}

	~Editor()
	{
		close();
	}

	std::size_t size() const {
		if (!fileOpen)
		{
			throw std::runtime_error("Cannot get size of a file that is not open!");
		}
		return fileSize;
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		if (!fileOpen)
		{
			throw std::runtime_error("Cannot edit a file that is not open!");
		}
		if (offset >= fileSize)
		{
			throw std::invalid_argument("Attempted to edit after end of file!");
		}
		out.seekp(offset);
		std::size_t pos = out.tellp();
		const char character = value;
		out.write(&character, 1);
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (!fileOpen)
		{
			throw std::runtime_error("Cannot display a file that is not open!");
		}
		if (offset >= fileSize)
		{
			throw std::invalid_argument("Attempted to read after end of file!");
		}
		for (std::size_t i = 0; i < limit && offset + i < fileSize; ++i)
		{
			this->out.seekg(offset + i);
			char currByte;
			this->out.read(&currByte, 1);
			out << std::setfill('0') << std::setw(2) << std::hex << ((std::size_t)currByte) << " ";
			//out.write(&currByte, 1).write(" ", 1);
		}
	}

	void open(const std::string& filepath)
	{
		out.open(filepath, std::ios::in | std::ios::out | std::ios::binary);
		fileOpen = (bool)out;
		if (!fileOpen)
		{
			throw std::invalid_argument("The file could not be opened!");
		}
		out.seekg(0, std::ios::end);
		fileSize = out.tellg();
	}

	void close()
	{
		if (fileOpen)
		{
			out.close();
			fileOpen = false;
		}
	}
private:
	bool fileOpen;
	std::fstream out;
	std::size_t fileSize;
};

// Works with the standart io, but can be parametrized to work with other io streams
class Processor
{
public:
	Processor(Editor& e)
		:editor(e)
	{}

	bool isValid(const Command& command) const
	{
		if (command[0] == EXIT_COMMAND || command[0] == SIZE_COMMAND)
		{
			return command.size() == 0;
		}
		else if (command[0] == EDIT_COMMAND || command[0] == SHOW_COMMAND)
		{
			return command.size() == 2;
		}
		return false;
	}

	void execute(const Command& command)
	{
		if (command[0] == EXIT_COMMAND)
		{
			exiting = true;
		}
		else if (command[0] == SIZE_COMMAND)
		{
			try {
				std::cout << editor.size() << std::endl;
			}
			catch (std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
			}
			catch (std::runtime_error& e)
			{
				std::cerr << "The file was not opened at all. Exiting!" << std::endl;
				exiting = true;
			}
		}
		else if (command[0] == EDIT_COMMAND)
		{
			try {
				std::size_t offset;
				std::uint8_t byte;
				try {
					offset = std::stol(command[1]);
					byte = std::stol(command[2]);
				}
				catch (std::invalid_argument&)
				{
					std::cerr << "Invalid formatting of the numbers. They should be integers! Try again" << std::endl;
					return;
				}
				editor.edit(offset, byte);
				std::cout << "OK";
			}
			catch (std::invalid_argument& e)
			{
				std::cerr << "FAIL - " << e.what() << std::endl;
			}
			catch (std::runtime_error&)
			{
				std::cerr << "FAIL - " << "The file was not opened at all. Exiting!" << std::endl;
				exiting = true;
			}
		}
		else if (command[0] == SHOW_COMMAND)
		{
			try {
				std::size_t offset;
				std::uint8_t limit;
				try {
					offset = std::stol(command[1]);
					limit = std::stol(command[2]);
				}
				catch (std::invalid_argument&)
				{
					std::cerr << "Invalid formatting of the numbers. They should be integers! Try again" << std::endl;
					return;
				}

				for (std::size_t i = 0; i < limit / 16; i++)
				{
					std::cout << std::setfill('0') << std::setw(8) << std::hex << (offset + i) << " ";
					try {
						editor.display(std::cout, offset + i * 16, 16);
						std::cout << std::endl;
					}
					catch (std::invalid_argument& e) {
						std::cerr << "<- Address is not in file" << std::endl;
						return;
					}
				}
				std::size_t rem = limit % 16;
				if (rem != 0)
				{
					std::cout << std::setfill('0') << std::setw(8) << std::hex << (offset + (limit / 16 * 16)) << " ";
					try {
						editor.display(std::cout, offset + (limit / 16 * 16), rem);
						std::cout << std::endl;
					}
					catch (std::invalid_argument& e) {
						std::cerr << "<- Address is not in file" << std::endl;
						return;
					}
				}
			}
			catch (std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
			}
			catch (std::runtime_error&)
			{
				std::cerr << "The file was not opened at all. Exiting!" << std::endl;
				exiting = true;
			}
		}
		else {
			throw std::invalid_argument("Passed invalid command");
		}
	}

	bool shouldExit() const
	{
		return exiting;
	}
private:
	Editor& editor;
	bool exiting = false;

	static const std::string EXIT_COMMAND;
	static const std::string SIZE_COMMAND;
	static const std::string EDIT_COMMAND;
	static const std::string SHOW_COMMAND;
};
const std::string Processor::EXIT_COMMAND = "EXIT";
const std::string Processor::SIZE_COMMAND = "SIZE";
const std::string Processor::EDIT_COMMAND = "EDIT";
const std::string Processor::SHOW_COMMAND = "SHOW";

int main(int argc, const char** argv)
{
	std::cout << "The program is case sensitive as per the problem's description" << std::endl;
	if (argc != 2)
	{
		std::cerr << "Unexpected number of args is 1(but you passed " << argc - 1 << "), expected to be a single filepath. Exiting" << std::endl;
		return 1;
	}
	Editor e;
	try {
		e.open(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	Processor proc(e);
	do {
		std::string commandStr;
		std::getline(std::cin, commandStr);
		Command command(commandStr);
		if (proc.isValid(command))
		{
			proc.execute(command); // guaranteed to not throw
		}
		else {
			std::cerr << "Inavlid command" << std::endl;
		}

		// second way
		/*try{
			proc.execute(command);
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << "You passed invalid command" << std::endl;
		}*/
	} while (!proc.shouldExit());

	return 0;
}