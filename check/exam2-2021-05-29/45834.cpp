// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Теодор Тодоров
// ФН: 45834
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 2021-05-29
// Начален час на контролното: 9:00
// Кой компилатор използвате: Clang
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class command {
	std::vector<std::string> parts;

public:
	explicit command(const char * str) {
		if (str == nullptr) {
			return;
		}
		
		const std::size_t strSize = std::strlen(str);
		
		std::string buffer;
		for (std::size_t i = 0; i < strSize; i++) {
			char currChar = str[i];
			
			if (currChar == ' ') {
				if (!buffer.empty()) {
					parts.push_back(buffer);
					buffer = "";
				}
				continue;
			}
			else {
				buffer += str[i];
			}
		}
		if (!buffer.empty()) {
			parts.push_back(buffer);
		}
	}
	
	std::size_t size() const {
		return parts.size();
	}
	
	const std::string & operator[](std::size_t index) const {
		return parts[index];
	}
};

class editor {
	std::fstream file;
	std::size_t fileSize = 0;
	
	void throwIfNoFile() const {
		if (!file) {
			throw std::runtime_error("No file is open");
		}
	}
	
	static std::size_t getFileSize(const char * filePath) {
		if (filePath == nullptr) {
			throw std::invalid_argument("filePath is nullptr");
		}
		
		std::ifstream file(filePath, std::ios::binary | std::ios::in);
		if (!file) {
			throw std::runtime_error("Could not open file in getFileSize(const char *)");
		}
		
		file.seekg(0, std::ios::end);
		std::size_t size = file.tellg();
		file.close();
		return size;
	}

public:
	editor() = default;
	
	explicit editor(const char * filePath) {
		if (filePath == nullptr) {
			throw std::invalid_argument("filePath is nullptr");
		}
		this->open(filePath);
	}
	
	~editor() {
		this->close();
	}
	
	editor(const editor & other) = delete;
	editor & operator=(const editor & other) = delete;
	
	editor(editor && other) = delete;
	editor & operator=(editor && other) = delete;
	
	std::size_t size() const {
		if (!file) {
			throw std::runtime_error("File must be open to get size");
		}
		return this->fileSize;
	}
	
	void open(const char * filePath) {
		if (filePath == nullptr) {
			throw std::invalid_argument("filePath is nullptr");
		}
		
		if (file.is_open()) {
			file.close();
		}
		
		fileSize = getFileSize(filePath);
		
		file.open(filePath);
		if (!file) {
			throw std::runtime_error("Could not open file in open(const char *)");
		}
	}
	
	void close() {
		if (file.is_open()) {
			file.close();
		}
	}
	
	void edit(std::size_t offset, std::uint8_t value) {
		throwIfNoFile();
		
		if (offset >= fileSize) {
			throw std::invalid_argument("Offset is outside of file bounds");
		}
		
		file.seekp(offset);
		file.put(value);
	}
	
	void display(std::ostream & out, std::size_t offset, std::size_t limit) {
		throwIfNoFile();
		
		if (offset >= fileSize) {
			throw std::invalid_argument("Offset is outside of file bounds");
		}
		
		for (std::size_t i = 0; i < limit; i++) {
			if (offset + i >= fileSize) {
				break;
			}
			
			if (i % 16 == 0) {
				if (i != 0) {
					out << '\n';
				}
				
				out << std::setfill('0') << std::setw(8) << std::hex << offset + i << std::dec;
			}
			
			file.seekp(offset + i);
			const std::uint8_t byte = file.get();
			
			out << ' ' << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) byte << std::dec;
		}
		out << std::endl;
	}
};

class processor {
	editor edit;

public:
	explicit processor(const char * filePath) {
		edit.open(filePath);
	}
	
	processor(const processor & other) = delete;
	processor & operator=(const processor & other) = delete;
	
	processor(processor && other) = delete;
	processor & operator=(processor && other) = delete;
	
	bool is_valid(const command & cmd) {
		if (cmd.size() == 0) {
			return false;
		}
		
		if (cmd[0] == "SIZE" && cmd.size() == 1) {
			return true;
		}
		else if (cmd[0] == "EDIT" && cmd.size() == 3) {
			return true;
		}
		else if (cmd[0] == "SHOW" && cmd.size() == 3) {
			return true;
		}
		
		return false;
	}
	
	void execute(const command & cmd) {
		if (!is_valid(cmd)) {
			throw std::invalid_argument("Invalid command");
		}
		
		if (cmd[0] == "SIZE") {
			try {
				std::cout << edit.size() << " byte(s)" << std::endl;
			}
			catch (std::exception & e) {
				std::cout << "Encountered exception: " << e.what() << std::endl;
			}
		}
		else if (cmd[0] == "EDIT") {
			const std::size_t offset = std::stoull(cmd[1]);
			const std::size_t data = std::stoull(cmd[2]);
			const std::uint8_t byteMaxValue = -1;
			
			if (data > (std::size_t) byteMaxValue) {
				std::cout << "Fail" << std::endl;
				return;
			}
			
			try {
				edit.edit(offset, (std::uint8_t) data);
			}
			catch (std::exception & e) {
				std::cout << "Fail" << std::endl;
				return;
			}
			
			std::cout << "OK" << std::endl;
		}
		else if (cmd[0] == "SHOW") {
			const std::size_t offset = std::stoull(cmd[1]);
			const std::size_t limit = std::stoull(cmd[2]);
			const std::uint8_t byteMaxValue = -1;
			
			try {
				edit.display(std::cout, offset, limit);
			}
			catch (std::exception & e) {
				std::cout << "Encountered exception: " << e.what() << std::endl;
			}
		}
	}
	
	void run() {
		std::cout << "Available commands:\n"
				  << '\t' << "EXIT" << '\n'
				  << '\t' << "SIZE" << '\n'
				  << '\t' << "EDIT <offset> <byte>" << '\n'
				  << '\t' << "SHOW <offset> <limit>" << '\n'
				  << std::endl;
		
		while (true) {
			std::cout << "> ";
			std::string input;
			std::getline(std::cin, input);
			
			command cmd(input.c_str());
			
			if (cmd[0] == "EXIT") {
				break;
			}
			
			try {
				this->execute(cmd);
			}
			catch (std::exception & e) {
				std::cout << "Encountered exception: " << e.what() << std::endl;
			}
			
			std::cout << std::endl;
		}
	}
};

int main(int argc, char ** argv) {
	if (argc == 1) {
		std::cout << "No file path given, process is exiting." << std::endl;
		return 1;
	}
	
	if (argc > 2) {
		std::cout << "Too many arguments given, only 1 is expected, process is exiting." << std::endl;
		return 2;
	}
	
	const std::string filePath = argv[1];
	
	try {
		processor proc(filePath.c_str());
		proc.run();
	}
	catch (std::exception & e) {
		std::cout << "Exception encountered: " << e.what() << "\nProcess is exiting." << std::endl;
		return 3;
	}
	
	return 0;
}