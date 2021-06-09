// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Чудомир Ченков
// ФН: 82142
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
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
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Editor {
public:
	Editor()=default;

	Editor(const char *path) {
		open(path);
	}

	~Editor() { file.close(); }

	void open(const char *path) {
		file.open(path, std::ios_base::binary | std::ios_base::out | std::ios_base::in | std::ios_base::ate);

		if (!file.good()) {
			throw std::runtime_error("Error: Could not open file " + std::string(path));
		}

		file.seekg(0, std::ios_base::end);
		file_size = file.tellg();
		file.seekg(0, std::ios_base::beg);

		file_path = std::string(path);
	}

	void close() { file.close(); }

	std::size_t size() const { return file_size; }

	bool edit(std::size_t offset, std::uint8_t value) {
		if (offset > file_size) {
			throw std::invalid_argument("Error: Invalid file offset");
		} else if (offset == file_size) {
			file_size++;
		}

		file.seekp(offset, std::ios_base::beg);
		file.write((const char *) &value, sizeof(std::uint8_t));

		return file.good();
	}

	void display(std::ostream &out, std::size_t offset, std::size_t limit) {
		if (offset >= file_size) {
			throw std::invalid_argument("Error: Invalid file offset");
		}

		file.seekg(offset, std::ios_base::beg);

		std::uint8_t byte;

		for (std::size_t i = 0; file.read((char *) &byte, sizeof(std::uint8_t)) && i < limit; i++) {
			if (i % 16 == 0) {
				if (i != 0) out << '\n';
				out << std::setfill('0') << std::setw(8) << std::hex << file.tellg() << ' ';
			}

			out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) byte << ' ';
		}

		out << '\n';

		/* 
		 * Веднъж след прочитане на EOF, файловият поток се чупи, затова тук бива отворен наново
		 * Не знам дали това е адекватно решение, но е единственото, което измислих
		 */

		if (!file.good()) {
			file.close();
			file.open(file_path);
		}
	}

private:
	std::fstream file;
	std::size_t file_size;
	std::string file_path;
};

class Command {
public:
	Command(const std::string &str) {
		for (std::size_t i = 0; i < str.size(); i++) {
			std::string curr;

			while (str[i] != ' ' && i < str.size()) {
				curr.push_back(str[i++]);
			}

			args.push_back(curr);
		}
	}

	std::size_t size() const { return args.size() - 1; }

	std::string operator[](std::size_t pos) const { return args.at(pos); }

private:
	std::vector<std::string> args;
};

class Processor {
public:
	Processor(Editor *editor) : m_editor(editor) {}

	bool is_valid(const Command &cmd) const {
		if (cmd[0] == "SIZE" && cmd.size() == 0) return true;
		if (cmd[0] == "EDIT" && cmd.size() == 2) return true;
		if (cmd[0] == "SHOW" && cmd.size() == 2) return true;
		
		return false;
	}

	void execute(const Command& cmd) {
		if (!is_valid(cmd)) throw std::invalid_argument("Error: Invalid command");

		if (cmd[0] == "SIZE") {
			std::cout << m_editor->size() * sizeof(std::uint8_t) << " byte(s)" << std::endl;
		} else if (cmd[0] == "EDIT") {
			try {
				bool status = m_editor->edit(std::stoll(cmd[1]), std::stoll(cmd[2]));
				std::cout << (status ? "OK" : "FAIL") << std::endl;
			} catch (const std::exception &ex) {
				std::cerr << ex.what() << std::endl;
			}
		} else if (cmd[0] == "SHOW") {
			try {
				m_editor->display(std::cout, std::stoll(cmd[1]), std::stoll(cmd[2]));
			} catch (const std::exception &ex) {
				std::cerr << ex.what() << std::endl;
			}
		}
	}

private:
	Editor *m_editor;

};

int main(int argc, char *argv[]) {
	/*
	 * Програмата не създава файла ако той не съществува
	 * Не е ясно упоменато в условието какво точно трябва да е поведението
	 * Ако файлът трябва да се създава, то при отварянето на файла трябва да се подаде std::ios_base::trunc за openmode
	 */

	if (argc < 2) {
		std::cerr << "Error: No filename provided" << std::endl;
		return 1;
	}

	Editor editor;

	try {
		editor.open(argv[1]);
	} catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}

	Processor proc(&editor);

	while (true) {
		std::string command_text;

		std::cout << "> ";
		std::getline(std::cin, command_text);

		if (command_text == "EXIT") break;

		Command cmd(command_text);

		try {
			proc.execute(cmd);
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}