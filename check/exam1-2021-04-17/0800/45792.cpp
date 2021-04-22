//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Даниел Даниел Иванов
// ФН: 45792
// Специалност: Информатика
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00 <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC <посочете едно от Visual C++, GCC или Clang>
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

class Registration{
private:
    char registration[9];
public:
    Registration() = delete;
    Registration(const char* str);
    Registration& operator=(const char* str);
    bool operator==(const char* str) const;
    const char* toString() const;
};


bool isNumber(char a){
    return a<='9' && a>='0';
}

bool isSymbol(char a){
    return a>='A' && a<='Z';
}

bool oneSymFourNumsTwoSym(const char* str){
    return (isSymbol(str[0]) && isNumber(str[1]) && isNumber(str[2]) && isNumber(str[3]) && isNumber(str[4]) && isSymbol(str[5]) && isSymbol(str[6]));
}

bool twoSymFourNumsTwoSym(const char* str){
        return (isSymbol(str[0]) && isSymbol(str[1]) && isNumber(str[2]) && isNumber(str[3]) && isNumber(str[4]) && isNumber(str[5]) && isSymbol(str[6]) && isSymbol(str[7]));
};

bool isValidRegistration(const char* str){
    return oneSymFourNumsTwoSym(str) || twoSymFourNumsTwoSym(str);
}

Registration::Registration(const char *str) {
    if(!isValidRegistration(str)){
        throw std::exception();
    }
    strncpy(this->registration, str, 8);
}

Registration& Registration::operator=(const char* str){
    if(!isValidRegistration(str)){
        throw std::exception();
    }
    strncpy(this->registration, str, 8);
    return *this;
}
bool Registration::operator==(const char* str) const{
    size_t countTo = strlen(this->registration);
    for(int i=0; i<countTo; i++){
        if(str[i] != this->registration[i]){
            return 0;
        }
    }
    return 1;
}
const char* Registration::toString() const{
    size_t len = strlen(this->registration);
    char* result = new(std::nothrow) char[len];
    if(!result){
        std::cout << "No memory";
        return nullptr;
    }
    strncpy(result,this->registration,len);
    return result;
}













class Vehicle{
private:
    Registration regNum;
    std::string description;
public:
    Vehicle()=delete;
    Vehicle(const char* regnum, const char* description);
    const Registration getRegNum() const;
    const std::string getDesc() const;
    const char* stringToCharArr() const;
};

Vehicle::Vehicle(const char* regnum, const char* description)
    : regNum(Registration(regnum))
{
    this->description = description;
}

const Registration Vehicle::getRegNum() const{
    return this->regNum;
}
const std::string Vehicle::getDesc()const{
    return this->description;
}

const char* Vehicle::stringToCharArr() const{
    char* result = new (std::nothrow) char[32];
    for(int i=0; i<32; i++){
        result[i] = this->getDesc()[i];
    }
    return result;
}











class VehicleList{
private:
    std::size_t capacity;
    std::size_t currentIndex;
    Vehicle** vehicles;

public:
    VehicleList(std::size_t capacity);
    ~VehicleList();
    VehicleList(const VehicleList& l);
    VehicleList& operator=(const VehicleList& l);
    void insert(const char* regnum, const char* description);
    const Vehicle& at(std::size_t index) const;
    const Vehicle& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t getCapacity() const;
    std::size_t size() const;
    const Vehicle* find(const char* regnum) const;
};

VehicleList::VehicleList(std::size_t capacity){
    try {
        this->vehicles = new Vehicle *[capacity];
        this->capacity = capacity;
        this->currentIndex = 0;
    }
    catch(std::bad_alloc& e){
        std::cerr << "Not enough memory for the VehicleList.";
    }
}

VehicleList::~VehicleList(){
    for(int i=0; i<currentIndex; i++){
        delete[] this->vehicles[i];
    }
    delete[] this->vehicles;
}


VehicleList::VehicleList(const VehicleList& rhs){
    try {
        this->vehicles = new Vehicle *[this->capacity];
        this->capacity = rhs.capacity;
        this->currentIndex = rhs.currentIndex;
        for (int i = 0; i < this->currentIndex; i++) {
            this->vehicles[i] = new Vehicle(rhs.vehicles[i]->getRegNum().toString(), rhs.vehicles[i]->stringToCharArr());
        }
    }
    catch(std::bad_alloc &e){
        std::cerr << "No Memory. Reverting to old variant";
        this->vehicles = nullptr;
    }
}

VehicleList& VehicleList::operator=(const VehicleList& rhs){
    if(this == &rhs){
        return *this;
    }
    try {
        this->vehicles = new Vehicle *[rhs.capacity];
        this->capacity = rhs.capacity;
        this->currentIndex = rhs.currentIndex;
        for (int i = 0; i < this->currentIndex; i++) {
            this->vehicles[i] = new Vehicle(rhs.vehicles[i]->getRegNum().toString(), rhs.vehicles[i]->stringToCharArr());
        }
    }
    catch(std::bad_alloc &e){
        std::cerr << "No Memory. Reverting to old variant";
        this->vehicles = nullptr;
    }
    return *this;
}
void VehicleList::insert(const char* regnum, const char* description){
    try {
        for (int i = 0; i < currentIndex; i++) {
            if (strcmp(regnum, this->vehicles[i]->getRegNum().toString()) == 0) {
                throw std::invalid_argument("");
            }
        }
        if (this->currentIndex + 1 > capacity) {
            throw std::out_of_range("");
        }
        this->vehicles[this->currentIndex] = new Vehicle(regnum, description);
        this->currentIndex++;
    }
    catch(std::invalid_argument& e){
        std::cerr << "This Vehicle and some in the garage have the same regnum.";
        throw;
    }
    catch(std::out_of_range& e){
        std::cerr << "The Vehicle that you add exceeds the maximum capacity.";
        return;
    }
    catch(std::bad_alloc& e){
        std::cerr << "No Memory. Reverting to old variant";
        this->vehicles[this->currentIndex] = nullptr;
    }

}
const Vehicle& VehicleList::at(std::size_t index) const{
    if(index<0 && index>=this->currentIndex){
        throw std::out_of_range("");
    }
    return *this->vehicles[index];
}
const Vehicle& VehicleList::operator[](std::size_t index) const{
    assert(index>=0 && index<this->currentIndex);
    return *this->vehicles[index];
}
bool VehicleList::empty() const{
    return size() == 0;
}
std::size_t VehicleList::getCapacity() const{
    return this->capacity;
}
std::size_t VehicleList::size() const{
    return this->currentIndex;
}
const Vehicle* VehicleList::find(const char* regnum) const{
    for(int i=0; i<this->currentIndex; i++){
        if(strcmp(regnum, this->vehicles[i]->getRegNum().toString()) == 0){
            return this->vehicles[i];
        }
    }
    std::cout << "None vehicle with this regnum was found";
    return nullptr;
}









int main()
{
    int n;
    std::cout << "Enter a number to start: ";
    std::cin >> n;
    VehicleList vl(n);
    for(int i=0; i<n; i++){
        try {
            char *regNum = new (std::nothrow) char[9];
            char *description = new (std::nothrow) char[32];
            std::cout << "Enter regNum for car " << i + 1 << ": ";
            std::cin >> regNum;
            std::cout << "Enter description for car " << i + 1 << ": ";
            std::cin >> description;
            vl.insert(regNum, description);
        }
        catch(std::exception& e){
            std::cerr << "Not valid regNum, please try again." << std::endl;
            i--;
        }
        catch(std::invalid_argument& e){
            i--;
        }
        catch(...){
            std::cerr << "Error" << std::endl;
        }

    }
    int option = 0;
    while(option != 9){
        std::cout << "Welcome to the garagelist\n"
                  << "Enter 1 to search for a mobile\n"
                  << "Enter 9 to leave the app\n";
        std::cin >> option;
        switch(option){
            case 1:
            {
                char* regNumToSearch = new(std::nothrow) char[9];
                std::cout << "Enter a registration: ";
                std::cin >> regNumToSearch;
                const Vehicle* result = vl.find(regNumToSearch);
                std::cout << "Registration number: " << result->getRegNum().toString() << "\n";
                std::cout << "Description: " << result->getDesc() << "\n";
                break;
            }
            case 9:
                return 0;
            default:
                break;
        }
    }
    return 0;
}
