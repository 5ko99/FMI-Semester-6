// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Яни Вълканов Дренчев
// ФН:45518
// Специалност: Информатика
// Курс: Прекъснал (2.)
// Административна група: Прекъснал
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <8:00>
// Кой компилатор използвате: <Clang>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Registration {
private:
    char registration[9];

    bool checkRegistrationNumber(const char *);

public:
    Registration(const char *);

    Registration &operator=(const char *);

    bool operator==(const char *) const;

    const char *toString() const;
};

Registration::Registration(const char *str) {
    if (checkRegistrationNumber(str)) {
        strcpy(registration, str);
    } else {
        throw std::exception();
    }
}

bool Registration::checkRegistrationNumber(const char *str) {
    bool isValid = true;
    if (!isalpha(str[0])) {
        isValid = false;
        return isValid;
    }
    if (isalpha(str[1])) {
        for (int i = 2; i < 6; ++i) {
            if (!isdigit(str[i])) {
                isValid = false;
                return isValid;
            }
        }
        for (int i = 6; i < 8; ++i) {
            if (!isalpha(str[i])) {
                isValid = false;
                return isValid;
            }
        }
    } else {
        for (int i = 1; i < 5; ++i) {
            if (!isdigit(str[i])) {
                isValid = false;
                return isValid;
            }
        }
        for (int i = 5; i < 7; ++i) {
            if (!isalpha(str[i])) {
                isValid = false;
                return isValid;
            }
        }
    }
    return isValid;
}

Registration &Registration::operator=(const char *str) {
    if (strcmp(registration, str) != 0) {
        strcpy(registration, str);
    }
    return *this;
}

bool Registration::operator==(const char *str) const {
    return strcmp(registration, str) == 0;
}

const char *Registration::toString() const {
    return registration;
}

class Vehicle {
public:
    const Registration *regNum;
    const std::string *description;

public:
    Vehicle(const char *_regNum, const std::string& _description);

    ~Vehicle();
};

Vehicle::Vehicle(const char *_regNum, const std::string& _description) {
    regNum = new Registration{_regNum};
    description = &_description;
}

Vehicle::~Vehicle() {
    delete [] regNum;
}

class VehicleList {
private:
    std::size_t capacity;
    std::size_t currCapacity;
    Vehicle **cars;

    void copy(const VehicleList &list);

    void destroy();

public:
    ~VehicleList();

    VehicleList(std::size_t);

    VehicleList &operator=(const VehicleList &);

    void insert(const char *, const char *);

    const Vehicle &at(std::size_t index) const;

    const Vehicle &operator[](std::size_t index) const;

    bool empty() const;

    std::size_t capacicty() const;

    std::size_t size() const;

    const Vehicle *find(const char *regnum) const;
};

VehicleList::VehicleList(std::size_t _capacity) {
    capacity = _capacity;
    currCapacity = 0;
    cars = new Vehicle *[capacity];
    for (int i = 0; i < capacity; ++i) {
        cars[i] = nullptr;
    }
}

VehicleList::~VehicleList() {
    destroy();
}

VehicleList &VehicleList::operator=(const VehicleList &other) {
    if (this == &other) {
        return *this;
    }
    destroy();
    copy(other);
    return *this;
}

void VehicleList::destroy() {
    for (int i = 0; i < capacity; ++i) {
        delete cars[i];
    }
    delete[] cars;
}

void VehicleList::copy(const VehicleList &list) {
    destroy();
    capacity = list.capacity;
    currCapacity = list.currCapacity;
    cars = new Vehicle *[capacity];

    for (int i = 0; i < currCapacity; ++i) {
        cars[i] = new Vehicle(list[i]);
    }
}

const Vehicle &VehicleList::operator[](std::size_t index) const {
    assert(index < currCapacity);
    return *cars[index];
}

const Vehicle &VehicleList::at(std::size_t index) const {
    if (index >= currCapacity) {
        throw std::out_of_range("Invalid position");
    }
    return *cars[index];
}

bool VehicleList::empty() const {
    return currCapacity == 0;
}

std::size_t VehicleList::capacicty() const {
    return capacity;
}

std::size_t VehicleList::size() const {
    return currCapacity;
}

const Vehicle *VehicleList::find(const char *regnum) const {
    for (int i = 0; i < currCapacity; ++i) {
        if (strcmp(cars[i]->regNum->toString(), regnum) == 0) {
            return cars[i];
        }
    }
    return nullptr;
}

void VehicleList::insert(const char *regNum, const char *desc) {
    if (find(regNum)){
        throw std::exception();
    }
    if (currCapacity +1 > capacity){
        throw std::exception();
    }
    Vehicle test{regNum, desc};
    std::string descString;
    descString = desc;
    for (int i = 0; i < capacity; ++i) {
        if (cars[i] != nullptr){
            cars[i] = &test;
            break;
        }
    }
    currCapacity++;
}

int main() {
    std::string regNumber;
    char* arrayRegNumber;
    char* descriptionArray;
    std::string description;
    std::cout << "Welcome to Yani Drenchev's KR1" << "\n";
    std::cout << "Please enter number N for capacity" << "\n";
    size_t n = 0;
    std::cin >> n;
    VehicleList list {n};
    std::cout << "Please enter " << n << " Cars" << "\n";

    for (int i = 0; i < n; ++i) {
        bool isVehicleCreated = false;
        while(!isVehicleCreated) {
            std::cout << "Please enter car number " << i << "'s reg number" << "\n";
            std::cin >> regNumber;
            arrayRegNumber = new char[regNumber.size()];
            for (int j = 0; j < regNumber.size(); ++j) {
                arrayRegNumber[j] = regNumber.at(j);
            }
            std::cout << "Please enter car number " << i << "'s description" << "\n";
            std::cin >> description;
            descriptionArray = new char[regNumber.size()];
            for (int j = 0; j < description.size(); ++j) {
                descriptionArray[j] = description.at(j);
            }
            try {
                list.insert(arrayRegNumber, descriptionArray);
                isVehicleCreated = true;
            } catch (...) {
                isVehicleCreated = false;
            }
        }

    }

    std::cout << "You can search for car or type exit in order to exit the program" << "\n";
    std::string command;

    while(true){
        std::cin >> command;
        if (command == "exit"){
            return 0;
        }
        char *numberToSearch = new char [command.size()];
        for (int i = 0; i < command.size(); ++i) {
            numberToSearch[i] = command[i];
        }
        if(list.find(numberToSearch)){
            std::cout << "CAR is there";
        }else{
            std::cout << "Car is not there";
        }
    }
}