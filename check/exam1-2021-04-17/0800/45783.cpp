//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Веселин Христов Пенев
// ФН: 45783
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>3
#include <string>
#include <stdexcept>
#include <cstddef>
#include <cctype>

class Registration{

private:
    char regNumber[9];

    bool isValid(const char* str){
        bool validReg = true;
        size_t i = 0;
        for(; str[i]; i++){

            if(i == 0 || i == 1 || i == 6 || i == 7){
                if(!isalpha(str[i])){
                    validReg = false;
                }
            }
            if(i == 2 || i == 3 || i == 4 || i == 5){
                if(!isdigit(str[i])){
                    validReg = false;
                }
            }

        }

        if(i != 8){
            validReg = false;
        }

        return validReg;
    }

public:

    Registration() = delete;

    Registration(const char* str){

        if(isValid(str)){
            for(size_t j = 0; j < 8; j++){
                regNumber[j] = str[j];
            }
        }else{
            throw std::invalid_argument("Invalid registration number.");
        }


    }

    Registration& operator=(const char* str){
        if(isValid(str)){
            for(size_t j = 0; j < 8; j++){
                regNumber[j] = str[j];
            }
        }else{
            throw std::invalid_argument("Invalid registration number.");
        }
    }

    bool operator==(const char* str) const{
        size_t size = 0;
        for(; str[size]; size++){ }
        if(size != 8) return false;
        for(size_t i = 0; i < 8; i++){
            if(str[i] != regNumber[i]){
                return false;
            }
        }
        return true;

    }

    const char* toString() const{

        char* str = new char[9];

        for(size_t i = 0; i < 8; i++){
            str[i] = regNumber[i];
        }

        str[8] = '\0';

        return str;

    }

};

class Vehicle{
public:

    const Registration* regnum;
    std::string description;

    Vehicle() = delete;

    Vehicle(const char* regnum_, const char* description_){
        regnum = new Registration(regnum_);
        description = description_;
    }

};

class VehicleList {
private:
    std::size_t count;
    std::size_t capacity_;
    Vehicle** vehicles;

public:

    VehicleList() = delete;

    VehicleList(size_t capacity){
        this->count = 0;
        this->capacity_ = capacity;
        this->vehicles = new Vehicle*[capacity_];
    }

    VehicleList& operator=(VehicleList vList){
        this->count = vList.count;
        this->capacity_ = vList.capacity_;
        this->vehicles = new Vehicle*[vList.capacity_];
        for(size_t listIndex = 0 ; listIndex < vList.count; listIndex++){

            size_t descSize = 0;
            while((*vList.vehicles[listIndex]).description[descSize++]){}


            char desc[] = "";
            vehicles[listIndex] = new Vehicle((*(*vList.vehicles[listIndex]).regnum).toString(), desc);

        }
    }

    ~VehicleList(){
        for(size_t i = 0; i < this->count; i++){
            delete this->vehicles[i];
        }
        delete[] this->vehicles;
    }

    void insert(const char* regnum, const char* description){


        try{
            if(this->count + 1 >= this->capacity_){
                throw std::invalid_argument("No space");
            }
            Vehicle* v = new Vehicle(regnum, description);
            this->vehicles[this->count++] = v;
        }catch(std::bad_alloc e){
            return;
        }catch(std::exception e){
            return;
        }
    }

    const Vehicle& at(std::size_t index) const{
        if(index >= count){
            throw std::out_of_range("Out of range");
        }
        return *vehicles[index];
    }

    const Vehicle& operator[](std::size_t index) const{
        assert(index < this->count);
        return *vehicles[index];
    }

    bool empty() const{
        return this->count == 0;
    }

    std::size_t capacity() const{
        return this->capacity_;
    }

    std::size_t size() const{
        return this->count;
    }

    const Vehicle* find(const char* regnum) const{
        for(size_t vehicleIndex = 0; vehicleIndex < this->count; vehicleIndex++){
            if(*(*this->vehicles[vehicleIndex]).regnum == regnum){
                return this->vehicles[vehicleIndex];
            }
        }
        return nullptr;
    }

};

int main()
{

    size_t size_ = 0;

    std::cin >> size_;

    VehicleList vehicleList(size_);

    bool isSuccessful = true;

    for(size_t vehicleIndex = 0; vehicleIndex < size_;){

        isSuccessful = true;

        char* inputRegNumber = nullptr;
        std::cin.getline(inputRegNumber, 8);

        char* inputDescirption;
        std::cin.getline(inputDescirption, 100);

        try{
            vehicleList.insert(inputRegNumber, inputDescirption);
        }catch(std::invalid_argument){
            isSuccessful = false;
            std::cout << "Invalid vehicle information. Please try again: \n";
            continue;
        }

        if(isSuccessful){
            vehicleIndex++;
        }

    }

    while(true){

        std::cout << "check for: \n";

        char* inputRegNumber = nullptr;
        std::cin.getline(inputRegNumber, 8);

        const Vehicle* result = vehicleList.find(inputRegNumber);

        if(result == nullptr){
            std::cout << "Not found";
        }else{
            std::cout << "Found";
        }

    }

	return 0;
}
