// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Божидар Иванов
// ФН: 82191
// Специалност: КН
// Курс: Пръви
// Административна група: Терта
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30?
// Кой компилатор използвате: gcc
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>

static constexpr uint8_t MONTH_DAYS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
    public:
        Date(unsigned int day, unsigned int month, unsigned int year) {
            if (month < 1 || month > 12)
                throw std::invalid_argument("invalid month");
            uint8_t febDays = 28;
            if (month == 2) {
                if (year % 4 == 0)
                    if (year % 100 == 0) {
                        if (year % 400 == 0) febDays = 29;
                    }
                    else
                        febDays = 28;
                if (day < 1 || day > febDays)
                    throw std::invalid_argument("invalid day");
                }
            else
                if (day < 1 || day > MONTH_DAYS[month - 1])
                    throw std::invalid_argument("invalid day");
            m_Day = day;
            m_Month = month;
            m_Year = year;
        }
        
        unsigned int day() const { return m_Day; }
        unsigned int month() const { return m_Month; }
        unsigned int year() const { return m_Year; }
    
        bool operator==(const Date& rhs) const {
            return m_Day == rhs.m_Day && m_Month == rhs.m_Month 
                && m_Year == rhs.m_Year;
        }
        
        bool operator<(const Date& rhs) const {
            if (m_Year != rhs.m_Year) return m_Year < rhs.m_Year;
            if (m_Month != rhs.m_Month) return m_Month < rhs.m_Month;
            return m_Day < rhs.m_Day;
        }
    private:
        std::uint8_t m_Day;
        std::uint8_t m_Month;
        std::uint16_t m_Year;
};

class Registration {
    public:
        Registration(const std::string& id, const Date& date) : id(id), date(date) { }
        
        bool operator==(const Registration& rhs) const {
            return date == rhs.date && id == rhs.id;
        }
        
        bool operator<(const Registration& rhs) const {
            if (date == rhs.date) return id < rhs.id;
            return date < rhs.date;
        }
        
        const std::string id;
        const Date date;
};

class RegistrationList {
    public:
        RegistrationList(std::size_t capacity) : m_Capacity(capacity), m_Size(0) { 
            m_Data = new Registration*[capacity];
        }
        
        RegistrationList(const RegistrationList& other) {
            m_Data = new Registration*[other.m_Capacity];
            for (uint32_t i = 0; i < other.m_Capacity; i++) {
                m_Data[i] = new Registration(other.m_Data[i]->id, other.m_Data[i]->date);
            }
            m_Capacity = other.m_Capacity;
            m_Size = other.m_Size;
        }
        
        RegistrationList(RegistrationList&& other) {
            m_Data = other.m_Data;
            m_Capacity = other.m_Capacity;
            m_Size = other.m_Size;
            other.m_Data = nullptr;
            other.m_Capacity = 0;
            other.m_Size = 0;
        }
        
        ~RegistrationList() {
            for (uint32_t i = 0; i < m_Size; i++)
                delete m_Data[i];
            delete[] m_Data;
        }
        
        // sorry not sorry
        void insert(const std::string& id, const Date& date)
        {
            if (m_Capacity == m_Size)
                throw std::exception();
            auto* obj = new Registration(id, date);
            if (m_Size == 0) {
                m_Data[m_Size++] = obj;
                return;
            }
            std::size_t idx = 0;
            while (idx < m_Size && *m_Data[idx] < *obj) {
                idx++;
            }
            for (size_t i = m_Size; i >= idx + 1; i--) { // move right
                m_Data[i] = m_Data[i-1];
            }
            m_Size++;
            m_Data[idx] = obj;
        }
        const Registration& at(std::size_t pos) const {
            if (pos > m_Size)
                throw std::out_of_range("index out of range");
            return *m_Data [pos];
        }
        const Registration& operator[](std::size_t idx) const {
            assert(idx < m_Size);
            return *m_Data[idx];
        };
        
        RegistrationList& operator=(const RegistrationList& rhs) {
            if (this != &rhs) {
                if (m_Data) {
                    for (uint32_t i = 0; i < m_Size; i++)
                        delete m_Data[i];
                    delete[] m_Data;
                }
                m_Data = new Registration * [rhs.m_Capacity];
                for (uint32_t i = 0; i < rhs.m_Capacity; i++) {
                    m_Data[i] = new Registration(rhs.m_Data[i]->id, rhs.m_Data[i]->date);
                }
                m_Capacity = rhs.m_Capacity;
                m_Size = rhs.m_Size;
            }
            return *this;
        }
        
        RegistrationList& operator=(RegistrationList&& rhs) {
            if (m_Data) {
                for (uint32_t i = 0; i < m_Size; i++)
                        delete m_Data[i];
                delete[] m_Data;
            }
            m_Data = rhs.m_Data;
            m_Capacity = rhs.m_Capacity;
            m_Size = rhs.m_Size;
            rhs.m_Data = nullptr;
            rhs.m_Capacity = 0;
            rhs.m_Size = 0;
            return *this;
        }
        
        bool empty() const { return m_Size == 0; }
        std::size_t capacity() const { return m_Capacity; }
        std::size_t size() const { return m_Size; }
        
    private:
        Registration** m_Data = nullptr;
        std::size_t m_Capacity;
        std::size_t m_Size;
};

int main()
{
    std::size_t n;
    RegistrationList* list;
    while (true) {
        std::cin >> n;
        try {
            list = new RegistrationList(n);
            std::cout << "list created." << std::endl;
            break;
        }
        catch (std::bad_alloc& ex) {
            std::cerr << "list size too big!. Try again." << std::endl;
        }
    }
    std::string id;
    unsigned int day, month, year;
    int inserted = 0;
    while (inserted != n) {
        std::cin >> id >> day >> month >> year;
        try {
            Date date{ day, month , year };
            list->insert(id, date);
            inserted++;
        }
        catch (std::invalid_argument& ex) {
            std::cout << "invalid date. " << ex.what() << std::endl;
            std::cin.clear();
        }
    }
    
    std::cout << "=========================" << std::endl;
    
    for (uint32_t i = 0; i < list->size(); i++) {
        const Registration& reg = list->at(i);
        std::cout << reg.id << "->(" << reg.date.day() << "/" << reg.date.month() << "/" << reg.date.year() << ")" << std::endl;
    }
    
    delete list;
	return 0;
}