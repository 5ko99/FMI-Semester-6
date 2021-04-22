//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Румен Георгиев Азманов
// ФН: 82176
// Специалност: Компютърни науки
// Курс: Първи 1
// Административна група: Трета 3
// Ден, в който се явявате на контролното: 17.04.2021г.
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>  //класа std::string
//
#include <cstddef>  //(за работа със std::size_t)
#include <cstdint>  // (за работа със uint8_t и uint16_t).
#include <stdexcept>  //(за работа с класовете за изключения).

class Date {
   private:
    std::uint8_t day_Date;
    std::uint8_t month_Date;
    std::uint16_t year_Date;

    bool verificationOfDate(unsigned int day, unsigned int month,
                            unsigned int year) {
        bool leapYear = false;
        if (year % 4 == 0 || (year % 4 != 0 && year % 100 == 0)) {
            leapYear = true;
        }
        if (year % 4 == 0 && year % 100 == 0 && year % 400 != 0) {
            leapYear = false;
        }

        if (month < 1 || month > 12) {
            return false;
        }

        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12: {
                if (day < 1 || day > 31) {
                    return false;
                }
            } break;
            case 4:
            case 6:
            case 9:
            case 11: {
                if (day < 1 || day > 30) {
                    return false;
                }
            } break;
            case 2: {
                if (leapYear == true && day < 1 || day > 29) {
                    return false;
                }
                if (leapYear == false && day < 1 || day > 28) {
                    return false;
                }
            } break;

            default:
                break;
        }
        return true;
    }

   public:
    Date(unsigned int day, unsigned int month, unsigned int year) {
        if (verificationOfDate(day, month, year) == false) {
            throw std::invalid_argument("Invalid date!");
        }
        day_Date = day;
        month_Date = month;
        year_Date = year;
    }

    unsigned int day() const {
        unsigned int dateOfMonthFormat = day_Date;
        return dateOfMonthFormat;
    }

    unsigned int month() const {
        unsigned int monthFormat = month_Date;
        return monthFormat;
    }

    unsigned int year() const {
        unsigned int yearFormat = year_Date;
        return yearFormat;
    }

    bool operator==(const Date& rhs) const {
        if (day_Date == this->day_Date && month_Date == this->month_Date &&
            year_Date == this->year_Date) {
            return true;
        } else
            return false;
    }

    bool operator<(const Date& rhs) const {
        if (year_Date < this->year_Date) {
            return true;
        }
        if (year_Date == this->year_Date && month_Date < this->month_Date) {
            return true;
        }
        if (year_Date == this->year_Date && month_Date == this->month_Date &&
            day_Date < this->day_Date) {
            return true;
        }
        return false;
    }
};

class Registration {
   public:
    std::string id_Registration;
    Date* date_Registration;

   public:
    Registration(const std::string& id, const Date& date) {
        id_Registration = id;
        date_Registration = nullptr;
        date_Registration = new Date(date);
    }

    bool operator==(const Registration& rhs) const {
        if (id_Registration == rhs.id_Registration &&
            date_Registration == rhs.date_Registration) {
            return true;
        }
    }

    bool operator<(const Registration& rhs) const {
        if (id_Registration < rhs.id_Registration ||
            (id_Registration == rhs.id_Registration &&
             date_Registration < rhs.date_Registration)) {
            return true;
        }
    }
};

class RegistrationList {
   private:
    std::size_t capacity_registrations;
    std::size_t size_registrations;
    Registration** registrations;

   public:
    RegistrationList(std::size_t capacity) {
        capacity_registrations = capacity;
        size_registrations = 0;
        registrations = new Registration*[capacity];
    }

    void copy(const RegistrationList other) {
        capacity_registrations = other.capacity_registrations;
        size_registrations = other.size_registrations;
        for (size_t i = 0; i < size_registrations; i++) {
            registrations[i] = other.registrations[i];
        }
    }

    RegistrationList& operator=(const RegistrationList other) {
        capacity_registrations = other.capacity_registrations;
        size_registrations = other.size_registrations;
        for (size_t i = 0; i < size_registrations; i++) {
            registrations[i] = other.registrations[i];
        }
        return *this;
    }

    ~RegistrationList() { delete[] registrations; }

    void insert(const std::string& id, const Date& date) {
        bool insterted = false;
        if (size_registrations >= capacity_registrations) {
            throw std::exception();
        }

        std::cout << size_registrations << std::endl;

        if (size_registrations == 0 && capacity_registrations > 0) {
            registrations[0] = new Registration(id, date);
            std::cout << "insert in 0" << std::endl;
            ++size_registrations;
            insterted = true;
        }
        // } else {
        //     for (size_t i = 0; i < size_registrations; ++i) {
        //         std::cout << "true"
        //                   << (vehicle.id_Registration <
        //                       registrations[i]->id_Registration)
        //                   << std::endl;
        //         if (vehicle.id_Registration <
        //             registrations[i]->id_Registration) {
        //             for (size_t j = size_registrations; j < i; --j) {
        //                 registrations[j + 1] = registrations[j];
        //             }

        //             registrations[i] = &vehicle;
        //             insterted = true;
        //             std::cout << "insert in i" << std::endl;
        //         }
        //     }
        // }
        if (insterted == false) {
            registrations[size_registrations] = new Registration(id, date);
            std::cout << "insert in " << size_registrations << std::endl;
            ++size_registrations;
            insterted = true;
        }
        std::cout << size_registrations << std::endl;
    }

    const Registration& at(std::size_t index) const {
        if (index < 0 || index > size_registrations + 1) {
            throw std::out_of_range("Out of range access!");
        }
        return *registrations[index];
    }

    const Registration& operator[](std::size_t index) const {
        assert(index > 0 && index < size_registrations + 1);
        return *registrations[index];
    }

    bool empty() const { return registrations[0] == nullptr; }

    std::size_t capacity() const { return capacity_registrations; }

    std::size_t size() const { return size_registrations; }
};

int main() {
    try {
        int n;
        std::cin >> n;
        RegistrationList list(n);
        std::uint8_t day_Date;
        std::uint8_t month_Date;
        std::uint16_t year_Date;
        std::string id_Registration;
        for (size_t i = 0; i < n; i++) {
            std::cin >> day_Date;
            std::cin >> month_Date;
            std::cin >> year_Date;
            std::cin >> id_Registration;
            Date date1(day_Date, month_Date, year_Date);
            list.insert(id_Registration, date1);
        }
        for (size_t i = 0; i < n; i++) {
            std::cout << list.at(n).id_Registration
                      << list.at(n).date_Registration << std::endl;
        }

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    } catch (const std::exception) {
    }

    std::cout << "END!!!" << std::endl;
    return 0;
}