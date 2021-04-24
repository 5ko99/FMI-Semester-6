// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Ангел Димитров Петров
// ФН: 82211
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021 
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

class Date {

	private:

	uint8_t day = 0;
	uint8_t month = 0;
	uint8_t year = 0;

	bool isValidDate(unsigned day, unsigned month, unsigned year) {

		if (month < 1 || month > 12 || day < 1) {
			return false;
		}

		if ((!year % 4 || year % 100) || (!year % 4 && !year % 100 && !year % 400)) {

			if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
				&& day > 31) {
					return false;
			} 
			else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
				return false;
			} 
			else if (month == 2 && day > 29) {
				return false;
			}
			
		} else {

			if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
				&& day > 31) {
					return false;
			} 
			else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
				return false;
			} 
			else if (month == 2 && day > 28) {
				return false;
			}
		}

		return true;
	}

	void copy(const Date& other) {
		
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}
	public:

	Date(unsigned int day, unsigned int month, unsigned int year) {

		try {
			if (!isValidDate(day, month, year)) {
				throw std::invalid_argument("Invalid argument!\n");
			}
		}
		catch (const char* e) {
			std::cout << e;
		}

		this->day = day;
		this->month = month;
		this->year = year;
	}

	Date(const Date& other) {
		copy(other);
	}

	unsigned int getDay() const {
		return day;
	}

	unsigned int getMonth() const {
		return month;
	}

	unsigned int getYear() const {
		return year;
	}

	bool operator==(const Date& rhs) const {

		return  (day == rhs.day && month == rhs.month && year == rhs.year);
	}

	bool operator<(const Date& rhs) const {

		if (year < rhs.year) {

			return true;
		} 
		else if (year > rhs.year) {

			return false;
		} 
		else {
			if (month < rhs.month) {

				return true;
			}
			else if (month > rhs.month) {

				return false;
			}
			else {
				if (day < rhs.day) {

					return true;
				}
				else if (day > rhs.day) {

					return false;
				}
				else {
					return false;
				}
			}
		}
	}

	Date& operator=(const Date& other) {
		
		if (this != & other) {

			copy(other);
		}
		return *this;
	}
};

class Registration {

	public:

	std::string id;
	Date regDate;

	Registration(const std::string& id, const Date& date){

		this->id = id;
	}

	Registration& operator=(Registration& other) {

		if (this != &other) {

			id = other.id;
			regDate = other.regDate;
		}
	}

	bool operator==(const Registration& rhs) const {

		return id == rhs.id && regDate == rhs.regDate;
	}

	bool operator<(const Registration& rhs) const {

		if (regDate < rhs.regDate) {

			return true;
		} else if (!(regDate < rhs.regDate)) {

			return false;
		} else {

			return id < rhs.id;
		}
	}
};

class Allocator {

	private:

	std::size_t size;
	std::size_t capacity;
	Registration** container;

	public:	

	Allocator(std::size_t capacity) {

		this->capacity = capacity;
		container = new Registration* [capacity];
		for (int i = 0; i < capacity; ++i) {

			std::string null = "N/A";
			Date nullDate(0,0,0);

			container[i] = new Registration (null, nullDate);
		}
	}

	~Allocator () {

		for (int i = 0; i < capacity; ++i) {
			delete container[i];
		}
		delete[] container;
	}


	Registration getRegistrationAt(size_t pos) {

		return *container[pos];
	}
};


class RegistrationList {

	private:

	std::size_t capacity;
	std::size_t count;
	Registration** pointerList;
	Allocator container;

	void copy(RegistrationList& other) {

		try {

			pointerList = new Registration* [other.capacity];
			for (int i = 0; i < other.capacity; ++i)
				pointerList[i] = nullptr;
		}
		catch (std::bad_alloc& e) {

			for (int i = 0; i < other.capacity; ++i) 
				delete pointerList[i];
			delete[] pointerList;

			std::cout << e.what();
		}

		capacity = other.capacity;
		count = other.count;
		for (int i = 0; i < other.capacity; ++i) {

			container.getRegistrationAt(i) = other.container.getRegistrationAt(i);
			pointerList[i] = &container.getRegistrationAt(i);
		}
	}
	public:

	RegistrationList(std::size_t capacity) {

		this->capacity = capacity;

		try {
			pointerList = new Registration* [capacity];
		}
		catch (std::bad_alloc& e) {
			std::cout << e.what();
		}

		try {
			std::string null = "N/A";
			Date nullDate(0,0,0);

			for (int i = 0; i < capacity; ++i)
				container[i] = new Registration (null, nullDate);
		}
		catch (std::bad_alloc& e) {

			delete[] pointerList;
			std::cout << e.what();
		}
	}

	RegistrationList(RegistrationList& other) {

		copy(other);
	}

	RegistrationList& operator=(RegistrationList& other) {

		if (this != &other) {

			copy(other);
		}

		return *this;
	}

	~RegistrationList() {

		for (int i = 0; i < capacity; ++i) {

			delete pointerList[i];
		}
		delete[] container;
		delete[] pointerList;

	}

	void insert(const std::string& id, const Date& date) {

		Registration toInsert (id, date);

		try {
			if(count == capacity) {
				throw std::overflow_error("No more space left.\n");
			}
		}
		catch(const char* e) {
			std::cout << e;
		}

		try {
			for (int i = 0; i < count; ++i) {
				if (id == container[i].id) {
					throw std::invalid_argument("Id already exists.\n");
				}
			}
		}
		catch(const char* e) {
			std::cout << e;
		}

		++count;

		for (int i = 0; i < count; ++i) {

			if (toInsert < container[i]) {
				Registration temp (container[i].id, container[i].regDate);
				container[i] = toInsert;
				pointerList[i] = &container[i];

				for (int j = i+1; j < count-1; ++j) {
					container[j] = container[j+1];
					pointerList[j] = pointerList[j+1];
				}
				break;
			}	
		}	
	}

	const Registration& at(std::size_t index) const {

		try {
			if (index >= count) {
				throw std::out_of_range("Invalid index.\n");
			}
		}
		catch (const char* e) {
			std::cout << e;
		}

		return *pointerList[index];
	}

	const Registration& operator[](std::size_t index) const {

		assert (index < count);

		return *pointerList[index];
	}

	bool empty() const {
		
		return !count;
	}

	std::size_t capacity() const {

		return capacity;
	}

	std::size_t size() const {

		return count;
	}
};

void print (RegistrationList& list) {

	for (int i = 0; i < list.size(); ++i) {
		std::cout << list[i].id << " " << list[i].regDate << std::endl;
	}
}

int main() {

	unsigned N;
	
	std::cout << "Enter list's length:";
	std::cin >> N;

	RegistrationList list(N);

	for (int i = 0; i < N; ++i) {

		std::string toInsertId;

		std::cout << "Enter id:";
		std::cin >> toInsertId;

		unsigned day, month, year;

		std::cout << "Enter day:";
		std::cin >> day;
		std::cout << "Enter month:";
		std::cin >> month;
		std::cout << "Enter year:";
		std::cin >> year;
		
		Date toInsertDate(day, month, year);

		list.insert(toInsertId, toInsertDate);
	}

	print(list);

	return 0;
}