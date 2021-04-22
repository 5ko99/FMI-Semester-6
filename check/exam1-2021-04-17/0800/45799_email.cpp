// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Теодор Христов
// ФН: 45799
// Специалност: Информатика
// Курс:1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: g++
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

bool isRegistrationValid(const char *registration) {
    int len = strlen(registration);
    if(len == 7) {
        for (int i = 0; i < 7; ++i) {
            // 0 1 2 3 4 5 6
            // C 1 2 3 4 A B
            if(i == 0) {
                if(!isalpha(registration[i])){
                    return false;
                }
            }
            if(i >= 2 && i < 5){
                if(!isdigit(registration[i])){
                    return false;
                }
            }
            if(i >= 5){
                if(!isalpha(registration[i])){
                    return false;
                }
            }
        }
    } else if(len == 8){
        for (int i = 0; i < 8; ++i) {
            // 0 1 2 3 4 5 6 7
            // X Y 1 1 1 1 Y X
            if(i == 0 || i == 1) {
                if(!isalpha(registration[i])){
                    return false;
                }
            }
            if(i >= 2 && i < 6){
                if(!isdigit(registration[i])){
                    return false;
                }
            }
            if(i >= 6){
                if(!isalpha(registration[i])){
                    return false;
                }
            }
        }
    }


    return true;
}

class Registration {
private:
    char registration[9];

    void copy(const char *str);

public:
    Registration(const char *str);

    Registration &operator=(const char *str);

    bool operator==(const char *str) const;

    const char *toString() const;
};

void Registration::copy(const char *str) {
    if (!isRegistrationValid(str)) {
        throw std::invalid_argument("Not valid registration");
    }

    strcpy(this->registration, str);
}

Registration::Registration(const char *str) {
    this->copy(str);
}

Registration &Registration::operator=(const char *str) {
    this->copy(str);
    return *this;
}

bool Registration::operator==(const char *str) const {
    return !!strcmp(this->registration, str);
}

const char *Registration::toString() const {
    return registration;
}


class Vehicle {
public:
    Registration regnum = Registration("");
    std::string description;

    Vehicle(const char *regnum, const char *description);

    Vehicle &operator=(const Vehicle vhcl);
};

Vehicle::Vehicle(const char *regnum, const char *description) {
    this->regnum = Registration(regnum);
    this->description = description;
}

Vehicle &Vehicle::operator=(const Vehicle vhcl) {
    this->regnum = vhcl.regnum.toString();
    this->description = vhcl.description;
}


class VehicleList {
private:
    size_t slots;
    size_t lastIndex;
    Vehicle **vhcls;
public:
    VehicleList(std::size_t capacity);

    VehicleList(const VehicleList &vhclList);

    VehicleList &operator=(const VehicleList &vl);

    ~VehicleList();

    void insert(const char *regnum, const char *description);

    const Vehicle &at(std::size_t index) const;

    const Vehicle &operator[](std::size_t index) const;

    bool empty() const;

    std::size_t capacity() const;

    std::size_t size() const;

    const Vehicle *find(const char *regnum) const;
};

VehicleList::VehicleList(std::size_t capacity) {
    this->slots = capacity;
    this->lastIndex = 0;
    this->vhcls = new Vehicle *[capacity];
}

VehicleList::VehicleList(const VehicleList &vhclList) {
    this->slots = vhclList.slots;
    this->lastIndex = vhclList.lastIndex;
    this->vhcls = new Vehicle *[this->slots];

    for (int i = 0; i < lastIndex; ++i) {
        *this->vhcls[i] = *vhclList.vhcls[i];
    }
}

VehicleList &VehicleList::operator=(const VehicleList &vl) {
    this->slots = vl.slots;
    this->lastIndex = vl.lastIndex;

    for (int i = 0; i < lastIndex; ++i) {
        *this->vhcls[i] = *vl.vhcls[i];
    }
}

VehicleList::~VehicleList() {
    for (int i = 0; i < slots; ++i) {
        delete this->vhcls[i];
    }

    delete[] this->vhcls;
}

void VehicleList::insert(const char *regnum, const char *description) {
    if (slots <= lastIndex + 1) {
        throw std::invalid_argument("No space.");
    }
    if(find(regnum)) {
        throw std::invalid_argument("This vehicle already exists.");
    }
    if(!isRegistrationValid(regnum)){
        throw std::invalid_argument("Registration is not valid.");
    }

    Vehicle vhcl = Vehicle(regnum, description);
    this->vhcls[lastIndex]->regnum = regnum;
    this->vhcls[lastIndex]->description = description;
    this->lastIndex++;

}

const Vehicle &VehicleList::at(std::size_t index) const {
    if (index >= 0 && index < this->slots) {
        return *this->vhcls[index];
    } else {
        throw std::out_of_range("Invalid index.");
    }
}

const Vehicle &VehicleList::operator[](std::size_t index) const {
    assert(index >= 0 && index < this->slots);
    return *this->vhcls[index];
}

bool VehicleList::empty() const {
    return !!lastIndex;
}

std::size_t VehicleList::capacity() const {
    return this->slots;
}

std::size_t VehicleList::size() const {
    return lastIndex;
}

const Vehicle *VehicleList::find(const char *regnum) const {
    for (int i = 0; i < this->lastIndex; ++i) {
        if (strcmp(this->vhcls[i]->regnum.toString(), regnum) == 0) {
            return this->vhcls[i];
        }
    }

    return nullptr;
}

int main() {
    std::cout << "N: " << std::endl;
    int n;
    std::cin >> n;
    VehicleList vList = VehicleList(n);

    char tempReg[128];
    char tempDesc[128];
    for (int i = 0; i < n; ++i) {
        std::cout << "Registration: " << std::endl;
        std::cin.ignore();
        std::cin.getline(tempReg, 128);
        std::cout << "Desc: " << std::endl;
        std::cin.getline(tempDesc, 128);

        try{
            vList.insert(tempReg, tempDesc);
        } catch (std::invalid_argument e) {
            std::cout << e.what() << std::endl;
            i--;
        }
    }

    return 0;
}