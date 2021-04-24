// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Иван Тодоров Иванов
// ФН: 82171
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното:  17/04/2021г.
// Начален час на контролното: 10:30
// Кой компилатор използвате: gcc
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
#include <iostream>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <cstdint>

class Date {
    private:
        std::uint8_t m_day;
        std::uint8_t m_month;
        std::uint16_t m_year;

        std::uint8_t daysFebruary() const {
            if (m_year % 4 != 0) {
                return false;
            }
            else if (m_year % 100 != 0) {
                return true;
            }
            else if (m_year % 400 != 0) {
                return false;
            }

            return true;
        }

        bool isValid() const {
            if (m_month > 12 || m_month < 1) {
                return false;
            }

            if (m_day == 0) {
                return false;
            }

            switch(m_month) {
                case 1: case 3: case 5: case 7: case 9:
                case 11: if (m_day > 31) {
                        return false;
                    }
                    break;
                case 4: case 6: case 8: case 10:
                case 12: if (m_day > 30) {
                        return false;
                    }
                    break;
                case 2: if (m_day > daysFebruary()) {
                        return false;
                    }
                    break;
            }

            return true;
        }
    public:
        Date(unsigned int day, unsigned int month, unsigned int year) {
            this->m_day = day;
            this->m_month = month;
            this->m_year = year;
            if (!this->isValid()) {
                throw std::invalid_argument("Date is not valid.");
            }
        }

        Date(const Date& date) {
            m_day = date.m_day;
            m_month = date.m_month;
            m_year = date.m_year;
        }

        Date& operator=(const Date& date) {
            if (this == &date) {
                return *this;
            }
            
            m_day = date.m_day;
            m_month = date.m_month;
            m_year = date.m_year;

            return *this;
        }

        unsigned int day() const {
            return m_day;
        }

        unsigned int month() const {
            return m_month;
        }

        unsigned int year() const {
            return m_year;
        }

        bool operator==(const Date& rhs) const {
            if (m_day == rhs.m_day && m_month == rhs.m_month && m_year == rhs.m_year) {
                return true;
            }
            return false;
        }

        bool operator<(const Date& rhs) const {
            if (m_year == rhs.m_year) {
                if (m_month == rhs.m_month) {
                    return (m_day < rhs.m_day);
                }

                return (m_month < rhs.m_month);
            }

            return (m_year < rhs.m_year);
        }
};

class Registration {
    private:
    public:
        const std::string m_id;
        const Date m_date;

        Registration(const std::string& id, const Date& date) : m_id(id), m_date(date) {
            
        }

        bool operator==(const Registration& rhs) const {
            if(m_id == rhs.m_id && m_date == rhs.m_date) {
                return true;
            }

            return false;
        }

        bool operator<(const Registration& rhs) const {
            if(m_date < rhs.m_date) return true;
            return (m_id < rhs.m_id);
        }
};

class RegistrationList {
    typedef Registration* RegistrationPtr;
    private:
        std::size_t m_capacity;
        RegistrationPtr* m_registrations;
        std::size_t m_size;

        std::size_t findIndex(Registration* reg) {
            if (m_size != 0) {
                for (std::size_t i = m_size - 1; i >= 0; ++i) {
                    if (*m_registrations[i] < *reg) {
                        return i + 1;
                    }
                
                    insertAt(m_registrations[i], i + 1);
                }
            }

            return 0;
        }

        void insertAt(Registration* reg, std::size_t i) {
            m_registrations[i] = reg;
        }
    public:
        RegistrationList(std::size_t capacity) {
            m_capacity = capacity;
            m_registrations = new RegistrationPtr[capacity];
            m_size = 0;
        }

        RegistrationList(const RegistrationList& rL) {
            m_capacity = rL.m_capacity;
            m_size = rL.m_size;
            m_registrations = new RegistrationPtr[m_capacity];
            for (std::size_t i =  0; i < m_size; ++i) {
                Registration* reg = new Registration(rL.m_registrations[i]->m_id, rL.m_registrations[i]->m_date);
                m_registrations[i] = reg;
            }
        }

        RegistrationList& operator=(const RegistrationList& rL) {
            if (this == &rL) {
                return *this;
            }

            m_capacity = rL.m_capacity;
            m_size = rL.m_size;
            m_registrations = new RegistrationPtr[m_capacity];
            for (std::size_t i =  0; i < m_size; ++i) {
                Registration* reg = new Registration(rL.m_registrations[i]->m_id, rL.m_registrations[i]->m_date);
                m_registrations[i] = reg;
            }

            return *this;
        }

        void insert(const std::string& id, const Date& date) {
            Registration* tempReg = new Registration(id, date);
            if (m_size < m_capacity) {
                std::size_t index = findIndex(tempReg);
                insertAt(tempReg, index);
                ++m_size;
            }
            else {
                throw std::exception();
            }
        }

        const Registration& at(std::size_t index) const {
            if (index >= m_size || index < 0) {
                throw std::out_of_range("Index is out of range");
            }

            return *m_registrations[index];
        }

        const Registration& operator[](std::size_t index) const {
            assert(index >= 0 && index <m_size);

            return *m_registrations[index];
        }

        bool empty() const {
            if (m_size == 0) {
                return true;
            }

            return false;
        }

        std::size_t capacity() const {
            return m_capacity;
        }

        std::size_t size() const {
            return m_size;
        }

        ~RegistrationList() {
            for (std::size_t i = 0; i < m_size; ++i) {
                delete m_registrations[i];
            }

            delete[] m_registrations;
        }

};

void readCapacity(std::size_t& n) {
    std::cout << "Capacity: ";
    std::cin >> n;
}

void insertRegistration(RegistrationList rL) {
    std::string id;
    unsigned int day;
    unsigned int month;
    unsigned int year;

    std::cout << "Id: ";
    std::cin >> id;
    
    while (true) {
        std::cout << "Date day: ";
        std::cin >> day;
        std::cout << "Date month: ";
        std::cin >> month;
        std::cout << "Date year: ";
        std::cin >> year;
        
        try {
            Date d(day, month, year);
            rL.insert(id, d);
            break;
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Try again." << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Regustration list is full, registration was not added." << std::endl;
            break;
        }
    }


}

void printRegistration(Registration reg) {
    std::cout << "ID: " << reg.m_id << std::endl;
    std::cout << "Date: " << reg.m_date.day() << "/" << reg.m_date.month() << "/" << reg.m_date.year() << std::endl;
}

void printAll(RegistrationList rL) {
    if (rL.empty()) {
        std::cout << "There are no registrations in the list." << std::endl;
    }
    else {
        for (std::size_t i = 0; i < rL.size(); ++i) {
            std::cout << "Registration " << i + 1 << ":" << std::endl; 
            printRegistration(rL[i]);
        }
    }
}

int main()
{
    std::size_t n;
    readCapacity(n);

    RegistrationList rL(n);

    for (std::size_t i = 0; i < n; ++i) {
        insertRegistration(rL);
    }

    printAll(rL);

	return 0;
}