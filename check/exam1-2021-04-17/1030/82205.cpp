// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Йоана Дудева
// ФН: 82205
// Специалност: КН1
// Курс: 1ви
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04
// Начален час на контролното: <тук попълнете часа за вашата група>
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

//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl; 

class Date
{
	private:
	std::uint8_t dayy;
	std::uint8_t monthh;
	std::uint8_t yearr;

	public:
	Date(unsigned int day, unsigned int month, unsigned int year);
	//конструктор, който създава нов обект за дата с ден day, месец month и година year. Ако датата не е валидна, да се хвърля изключение от тип std::invalid_argument.

	unsigned int day() const;
	//връща деня като unsigned int.

	unsigned int month() const;
	//връща месеца като unsigned int.

	unsigned int year() const;
	//връща годината като unsigned int.

	bool operator==(const Date& rhs) const;
	//Връща истина, ако датата съхранена в текущия обект е същата като тази в rhs.

	bool operator<(const Date& rhs) const;
	//връща истина, ако датата съхранена в текущия обект е по-ранна от тази съхранена в обекта rhs.
};

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->dayy = day;
	if (this->dayy <= 0 && this->dayy > 31)
	{
		throw std::invalid_argument("");
		if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && this->dayy > 30)
		{
			throw std::invalid_argument("");
		}
		if (month == 2 && this->dayy >29)
		{
			throw std::invalid_argument("");
		}
	}
	this->monthh = month;
	if (this->monthh<1 && this->monthh>12)
	{
		throw std::invalid_argument("");
	}
	this->yearr = year; 
	if (this->yearr < 0)
	{
		throw std::invalid_argument("");
	}
}
unsigned int Date::day() const
{
	return this->dayy;
}

unsigned int Date::month() const
{
	return this->monthh;
}

unsigned int Date::year() const
{
	return this->yearr;
}

bool Date::operator==(const Date& rhs) const
{
	return ((this->yearr == rhs.yearr) && (this->monthh == rhs.monthh) && (this->dayy == rhs.dayy));
}

bool Date::operator<(const Date& rhs) const
{
	return this->yearr < rhs.yearr || this->monthh < rhs.monthh || this->dayy < rhs.dayy; 
}

class Registration
{
	private:
	std::string idd; 
	Date* datee = 0; 

	public:
	Registration(const std::string& id, const Date& date);
	bool operator==(const Registration& rhs) const;
	//Връща истина, ако номерът и датата на текущия обект съвпадат с тези на rhs.
	bool operator<(const Registration& rhs) const;
	//Проверява дали текущата регистрация предхожда тази в rhs. Считаме, че една регистрация A предхожда друга регистрация B или (1) ако датата на A е преди тази на B, или (2) ако двете дати съвпадат, но регистрационният номер на A предхожда лексикографски този на B.		
};

Registration::Registration(const std::string& id, const Date& date)
{
	this->idd = id;
	try
	{
		this->datee = new Date(date);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}
bool Registration::operator==(const Registration& rhs) const
{
	return (this->idd == rhs.idd && this->datee == rhs.datee);
}
bool Registration::operator<(const Registration& rhs) const
{
	return this->datee < rhs.datee || (this->datee == rhs.datee && this->idd < rhs.idd);
}

class RegistrationList
{
	private:
	Registration** registrations = nullptr;
	size_t sizee = 0;
	size_t capacityy = 0; 

	void sort(); 
	void copy(const RegistrationList& wanted); 
	void resize();
	void deallocate();  

	public:
    RegistrationList(size_t capacity); //създава списък, който може да съдържа най-много capacity на брой регистрации.

    RegistrationList(const RegistrationList& other);
	~RegistrationList();
	RegistrationList& operator=(const RegistrationList& other); 
	//Всички функции от rule of 3 (по желание: всички от rule of 5). Забележете, че RegistrationList не е като класа за гараж от домашното. RegistrationList притежава обектите съхранени в него и трябва да ги почиства в деструктора си. При копиране на списък, новото копие трябва да създаде за себе си нови обекти от тип Registration; то не трябва да сочи към тези на оригинала. Копието трябва да бъде със същия капацитет като оригинала. Операторът за присвояване да дава strong exception safety guarantee.

    void insert(const std::string& id, const Date& date);
    //добавя регистрацията с номер id и дата date. Тъй като класът трябва да поддържа регистрациите сортирани в нарастващ ред, тази операция трябва да вмъкне новия запис на подходящо място в списъка. Ако операцията не успее (например няма повече място), да се хвърля изключение от тип std::exception. Операцията да дава strong exception guarantee.

    const Registration& at(size_t index) const;
    //достъп до елемента намиращ се на позиция index. Ако такъв няма, да се хвърля изключение std::out_of_range.

    const Registration& operator[](size_t index) const;
    //достъп до елемента намиращ се на позиция index. Функцията да не прави проверка за коректност дали index е валидна позиция. (В debug режим assert-вайте дали index е валидна позиция).

    bool empty() const;
    //Проверява дали списъка е празен (т.е. в него не е била добавена нито една регистрация).

    size_t capacity() const;
    //капацитет на списъка.

    size_t size() const;
    //брой регистрации добавени в списъка.
};

void RegistrationList::sort()
{
	for (int i = 0; i < this->sizee; ++i)
	{
		for (int j = i+1; j < this->sizee; ++j)
		{
			if (this->registrations[j] < this->registrations[i])
			{
				std::swap(this->registrations[i], this->registrations[j]);
			}
		}
	}
} 
void RegistrationList::copy(const RegistrationList& wanted)
{
	this->sizee = wanted.sizee;
	this->capacityy = wanted.capacityy; 

	try
	{
		this->registrations = new Registration*[this->capacityy];
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	for (int i = 0; i < this->capacityy; ++i)
	{
		if (i < this->sizee)
		{
			this->registrations[i] = wanted.registrations[i]; 
		}
		else
		{
			this->registrations[i] = nullptr; 
		}
	}
	
}
void RegistrationList::resize()
{
	this->capacityy*= 2;
	Registration** newList;
	try
	{
		newList = new Registration*[this->capacityy];
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < this->capacityy; ++i)
	{
		newList[i] = this->registrations[i];
	}
	this->deallocate();
	this->registrations = newList; 
}
void RegistrationList::deallocate()
{
	for (int i = 0; i < this->capacityy; ++i)
	{
		delete this->registrations[i];
	}
	delete[] this->registrations; 
}

RegistrationList::RegistrationList(size_t capacity)
{
	this->capacityy = capacity;
	try
	{
		this->registrations = new Registration*[this->capacityy];
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	for (int i = 0; i < this->capacityy; ++i)
	{
		this->registrations[i] = nullptr; 
	}
}
RegistrationList::RegistrationList(const RegistrationList& other)
{
	copy(other);
}
RegistrationList::~RegistrationList()
{
	for (int i = 0; i < this->capacityy; ++i)
	{
		delete this->registrations[i];
	}
	delete[] this->registrations; 
}
RegistrationList& RegistrationList::operator=(const RegistrationList& other)
{
	if (this != &other)
	{
		deallocate();
		copy(other); 
	}

	return *this; 
}

void RegistrationList::insert(const std::string& id, const Date& date)
{
	if (this->sizee == this->capacityy)
	{
		throw std::exception(); 
	}

	try
	{
		this->registrations[this->sizee++] = new Registration(id, date); 
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	sort();
	
}
const Registration& RegistrationList::at(size_t index) const
{
	for (int i = 0; i < this->capacityy; ++i)
	{
		if (this->registrations[index] == nullptr)
		{
			throw std::out_of_range("");
		}
	}

	return *(this->registrations[index]);
}
const Registration& RegistrationList::operator[](size_t index) const
{
	#ifdef _DEBUG
	assert(index < this->sizee && index >= 0);
	#endif

	return *(this->registrations[index]);
}
bool RegistrationList::empty() const
{
	return this->sizee == 0; 
}
size_t RegistrationList::capacity() const
{
	return this->capacityy;
}
size_t RegistrationList::size() const
{
	return this->sizee;
}


int main()
{
	// Date data1(20, 4, 2014);
	// Registration registraciq1("proba", data1);
	// Date data2(19, 3, 2015);
	// Registration registraciq2("alo", data2);
	// bool proba = registraciq1 < registraciq2; 
	// cout<<proba; 

	// RegistrationList list(2);
	// list.insert("proba", data1);

	size_t number;
	cout<<"Enter capacity: ";
	cin>>number;

	RegistrationList littleRegistrationList(number);

	for (int i = 0; i < number; ++i)
	{
		unsigned int day, month, year; 

		cout<<"Lets enter date!"<<endl;
		cout<<"Day: ";
		cin>>day;
		cout<<"Month: ";
		cin>>month;
		cout<<"Year: ";
		cin>>year;

		Date littleDate(day, month, year); 
		cout<<"Day added! Lets add registration! "<<endl;

		std::string id; 
		cout<<"Id: ";
		cin>>id; 
 
		cout<<"Inserting..."<<endl;
		littleRegistrationList.insert(id, littleDate); 
		cout<<"Added!"<<endl;
		cout<<"-------------"<<endl;
	}

	for (int i = 0; i < number; ++i)
	{
		cout<<"Registration #"<<i+1<<endl;
		//cout<<littleRegistrationList.at(littleRegistrationList.[i]);
	}

	return 0;
}