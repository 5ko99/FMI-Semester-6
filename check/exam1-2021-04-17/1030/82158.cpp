//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Христо Жаблянов
// ФН: 82158
// Специалност: Компютърни Науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::size_t;
using std::uint16_t;
using std::uint8_t;

class Date {
  private:
    uint8_t d;
    uint8_t m;
    uint16_t y;

  public:
    Date(unsigned int _d = 1, unsigned int _m = 1, unsigned int _y = 1) {
        if (_m < 1 || _m > 12) throw std::invalid_argument("Invalid month");
        if (_d == 0) throw std::invalid_argument("Invalid day - 0");

        switch (_m) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (_d > 31) throw std::invalid_argument("Invalid day - more than 31");
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (_d > 30) throw std::invalid_argument("Invalid day - more than 30");
                break;
            default:
                uint8_t lim;
                if (_y % 4 != 0)
                    lim = 28;
                else if (_y % 100 != 0)
                    lim = 29;
                else if (_y % 400 != 0)
                    lim = 28;
                else
                    lim = 29;

                if (_d > lim) throw std::invalid_argument("Invalid day");
                break;
        }

        this->d = _d;
        this->m = _m;
        this->y = _y;
    }

    Date(const Date& date) : d(date.d), m(date.m), y(date.y) {}

    unsigned int day() const { return d; }
    unsigned int month() const { return m; }
    unsigned int year() const { return y; }

    bool operator==(const Date& date) const {
        return d == date.d && m == date.m && y == date.y;
    }

    bool operator<(const Date& date) const {
        if (y < date.y) return true;
        if (y > date.y) return false;

        if (m < date.m) return true;
        if (m > date.m) return false;

        if (d < date.d) return true;

        return false;
    }
};

class Registration {
  public:
    const std::string id;
    const Date date;

    Registration(const std::string& _id, const Date& _date) : id(_id), date(_date) {}

    Registration(const Registration& r) : id(r.id), date(r.date) {}

    bool operator==(const Registration& reg) const {
        return id == reg.id && date == reg.date;
    }

    bool operator<(const Registration& reg) const {
        if (date < reg.date) return true;
        if (date == reg.date && id < reg.id) return true;
        return false;
    }
};

class RegistrationList {
  private:
    Registration** registrations;
    const size_t cap;
    size_t len;

  public:
    RegistrationList(size_t capacity) : cap(capacity) {
        len = 0;
        try {
            registrations = new Registration*[cap];
        } catch (std::bad_alloc&) {
            registrations = nullptr;
            throw;
        }
    }

    RegistrationList(const RegistrationList& l) : cap(l.cap) {
        try {
            registrations = new Registration*[cap];
        } catch (std::bad_alloc&) {
            registrations = nullptr;
            throw;
        }
        len = l.len;

        for (size_t i = 0; i < len; i++) {
            Registration* r;
            try {
                r = new Registration(l[i].id, l[i].date);
            } catch (std::bad_alloc&) {
                len = i;
                throw;
            }

            registrations[i] = r;
        }
    }

    ~RegistrationList() {
        for (size_t i = 0; i < len; i++) delete registrations[i];
        delete[] registrations;
    }

    void insert(const std::string& id, const Date& date) {
        if (len == cap) throw std::overflow_error("List is full");

        Registration* r;
        try {
            r = new Registration(id, date);
        } catch (std::bad_alloc&) {
            throw;
        }

        bool flag = false;
        for (size_t i = 0; i < len; i++)
            if (*r < *registrations[i]) {
                for (size_t j = len; j > i; j--) registrations[j] = registrations[j - 1];
                registrations[i] = r;
                len++;

                flag = true;
                break;
            }

        if (!flag) {
            registrations[len] = r;
            len++;
        }
    }

    const Registration& at(std::size_t index) const {
        if (index >= len) throw std::out_of_range("index >= registration count");
        return *registrations[index];
    }

    const Registration& operator[](std::size_t index) const {
        assert(index < len);
        return *registrations[index];
    }

    bool empty() const { return len == 0; }

    size_t capacity() const { return cap; }

    size_t size() const { return len; }
};

int main() {
    size_t cap;
    cin >> cap;

    RegistrationList list(cap);

    cout << "Enter all registrations in format: [id] [day] [month] [year]\n";

    for (size_t i = 0; i < cap; i++) {
        cout << i << ": ";

        std::string reg;
        unsigned int day;
        unsigned int month;
        unsigned int year;
        cin >> reg >> day >> month >> year;

        Date date;
        try {
            date = Date(day, month, year);
        } catch (std::invalid_argument& e) {
            cout << e.what() << endl;
            i--;
            continue;
        }

        try {
            list.insert(reg, date);
        } catch (std::bad_alloc&) {
            cout << "Not enough memory. Not input will be accepted\n";
            break;
        } catch (std::exception& e) {
            cout << e.what() << endl;
            break;
        }
    }

    cout << list.size() << " items:\n";
    for (size_t i = 0; i < list.size(); i++)
        cout << "id: " << list[i].id << " date: " << list[i].date.day() << "."
             << list[i].date.month() << "." << list[i].date.year() << endl;

    return 0;
}