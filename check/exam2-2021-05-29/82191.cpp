// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Божидар Иванов
// ФН: 82191
// Специалност: КН
// Курс: Първи
// Административна група: Трета
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: clang
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Utils
{
public:
	static std::vector<std::string> split(const std::string& string, char delim)
	{
		std::vector<std::string> result;
		std::size_t prev = 0;
		do
		{
			std::size_t next = string.find(delim, prev + 1);
			if (next == std::string::npos)
			{
				std::string res = string.substr(prev == 0 ? prev : prev + 1, string.size() - prev);
				result.push_back(res);
			}
			else
				result.push_back(string.substr(prev == 0 ? prev : prev + 1, next - prev));
			
			prev = next;
		} while (prev != std::string::npos);
		
		return result;
	}
};

class Command
{
public:
	Command(const std::string& cmd)
	{
		m_Args = Utils::split(cmd, ' ');
	}
	
	std::size_t size() const { return m_Args.size(); }
	
	const std::string& operator[](std::size_t idx) const
	{
		assert(idx < m_Args.size());
		return m_Args[idx];
	}
	
private:
	std::vector<std::string> m_Args;
};

class Editor
{
public:
	Editor() = default;
	~Editor() { if (m_Stream.is_open()) m_Stream.close(); }
	Editor(const Editor& other) = delete;

	void open(const std::string& filepath)
	{
		try {
			m_Stream = std::fstream(filepath, std::ios::binary | std::ios::in | std::ios::out);
			if (!m_Stream.is_open())
				throw std::runtime_error("Could not open file!");
			m_Stream.seekg(0, std::ios::end);
			m_Size = m_Stream.tellg();
			m_Stream.seekg(0);
		} catch (const std::exception& ex) {
			throw;
		}
	}
	
	void close()
	{
		m_Stream.close();
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		if (offset >= m_Size)
			throw std::invalid_argument("Fail. Invalid offset. File size is: " + std::to_string(m_Size));
		m_Stream.seekp(offset);
		m_Stream.write((char*)&value, 1);
	}

	std::size_t size() const { return m_Size; }
	
	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{
		if (offset >= m_Size)
			throw std::invalid_argument("Invalid offset. File size is: " + std::to_string(m_Size));
		m_Stream.seekg(offset);
		
		size_t gcnt = 0;
		for (std::size_t i = offset; i < std::min(offset + limit, m_Size); i++, gcnt++)
		{
			if (gcnt % 16 == 0)
				std::cout << std::endl << std::setfill('0') << std::setw(8) << std::hex << (int)i << " ";
			uint8_t c;
			m_Stream.read((char*)&c, 1);
			m_Stream.seekg(m_Stream.tellg());
			out << std::setfill('0') << std::setw(2) << std::hex << (int)c << " ";
		}
		std::cout << std::endl;
	}
private:
	std::fstream m_Stream;
	std::size_t m_Size;
};

class Processor
{
public:
	static bool is_valid(const Command& command)
	{
		if (command.size() == 0)
			return false;
		if (command.size() == 1)
			return command[0] == "EXIT" || command[0] == "SIZE";
		
		if (command.size() == 3)
			return command[0] == "SHOW" || command[0] == "EDIT";
		
		return false;
	}
	
	static void init(const std::string& filepath)
	{
		assert(!s_Instance);
		s_Instance = new Processor(filepath);
	}
	
	static void execute(const Command& cmd)
	{
		assert(s_Instance);
		if (cmd[0] == "EXIT") {
			shutdown();
			exit(0);
		}
		
		if (cmd[0] == "SHOW")
		{
			try {
				std::size_t offset = std::stoull(cmd[1]);
				std::size_t limit = std::stoull(cmd[2]);
				s_Instance->m_Editor.display(std::cout, offset, limit);
			}
			catch (const std::exception& ex) {
				throw;
			}
		}

		if (cmd[0] == "EDIT")
		{
			try {
				std::size_t offset = std::stoull(cmd[1]);
				std::size_t limit = std::stoull(cmd[2]);
				s_Instance->m_Editor.edit(offset, limit);
				std::cout << "OK" << std::endl;
			}
			catch (const std::exception& ex) {
				throw;
			}
		}
		
		if (cmd[0] == "SIZE")
		{
			std::cout << s_Instance->m_Editor.size() << " byte(s)" << std::endl;
		}
	}
	
	static void shutdown()
	{
		assert(s_Instance);
		delete s_Instance;
	}
	
private:
	Processor(const std::string& filepath)
	{
		m_Editor.open(filepath);
	}

	static Processor* s_Instance;
	Editor m_Editor;
};

Processor* Processor::s_Instance = nullptr;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "File path required" << std::endl;
		return 0;
	}

	try {
		Processor::init(argv[1]);
	} catch(const std::exception& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
		return 0;
	}
	std::string cmdStr;
	while (true)
	{
		std::getline(std::cin, cmdStr);
		try {
			Command cmd(cmdStr);
			if (Processor::is_valid(cmd))
				Processor::execute(cmd);
			else
				std::cout << "Invalid command/args!" << std::endl;
			
		}
		catch (const std::exception& ex) {
			if (ex.what() == std::string("stoull"))
				std::cout << "Invalid args!" << std::endl;
			else
				std::cout << ex.what() << std::endl;
		}
	}
	Processor::shutdown();
	return 0;
}