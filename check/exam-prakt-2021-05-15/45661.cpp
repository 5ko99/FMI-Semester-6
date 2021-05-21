// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Снежана Йорданова Чолакова
// ФН: 45661
// Специалност: Информатика
// Курс: 1 
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: Visual C++
// 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

enum Type {
	info,
	warning,
	error,
	critical_error,
	MAX_ELEMENTS
};

class Message {
	Type type;
	char* description;
public:
	Message(Type, const char*);
	Message(const Message&);
	~Message();
	void operator<<(const Message&);
};

class Logger {
	Message message;
public:

};

Message::Message(Type T, const char* description) {
	size_t size = strlen(description);
	try {
		this->description = new char[size + 1];
	}
	catch (std::bad_alloc& ex) {
		std::cerr << "Failure to allocate memory\n";
		throw;
	}
	for (size_t i = 0; i < size; ++i) {
		this->description[i] = description[i];
	}
	this->description[size] = '\0';
	type = T;
}
Message::Message(const Message& other) {
	size_t size = strlen(other.description);
	try {
		this->description = new char[size + 1];
	}
	catch (std::bad_alloc& ex) {
		std::cerr << "Failure to allocate memory\n";
		throw;
	}
	for (size_t i = 0; i < size; ++i) {
		this->description[i] = other.description[i];
	}
	this->description[size] = '\0';
	this->type = other.type;
}
Message::~Message() {
	delete[] description;
}
void Message::operator<<(const Message& obj) {
	switch (obj.type) {
	case info:
		std::cout << "INFO: ";
		break;
	case warning:
		std::cout << "WARNING: ";
		break;
	case error:
		std::cout << "ERROR: ";
		break;
	case critical_error:
		std::cout << "CRITICAL ERROR: ";
		break;
	}
	std::cout << description << '\n';
}

int main()
{
	Message msg1(info, "Test 01");
	Message msg2(warning, "Test 02");
	Message msg3(error, "Test 03");
	Message msg4(error, "Test 04");

	return 0;
}