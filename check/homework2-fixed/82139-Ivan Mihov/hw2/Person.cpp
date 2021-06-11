# include <iostream>
# include "Person.h"
# include <string>
# include <algorithm>
Person::Person(std::string name, unsigned int id) {
    this->name = name;
    this->id = id;
}

void Person::addVehicle( Vehicle* car) {
    for (std::size_t i = 0; i < this->arr.size(); i++) {
        if (arr[i]->getRegistration() == car->getRegistration()) {
            throw std::invalid_argument("Can not have two Vehicles with the same registration");
        }
    } 
    this->arr.push_back(car);
}
void Person::removeVehicles() {
    std::size_t arrSize = arr.size();
    for (std::size_t i = 0; i < arrSize; i++) {
        arr[i]->eraseOwner();
    }
    this->arr.clear();
}
void Person::print()const {
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "id: " << this->id << std::endl;
    std::cout << ".............................\n";
    for (std::size_t i = 0; i < this->arr.size(); i++) {
        arr[i]->print();
    }
    std::cout << ".............................\n";

}
void Person::eraseAt(std::string vehicle) {
    std::size_t size = this->arr.size();
    bool notExist = true;// bool flag that shows if a vehicle with that registration is owned 
    for (std::size_t i = 0; i < size; i++) {
        if (arr[i]->getRegistration() == vehicle) {
            notExist = false;
            arr[i]->eraseOwner();
            std::swap(arr[i], arr[size-1]);
            arr.pop_back();
            break;
        }
        
    }
    if (notExist)
        throw std::runtime_error("this person does not own such a vehicle");
}
void Person::setName(const std::string& name) {
    this->name = name;
}
void Person::setId(const unsigned int id) {
    this->id = id;
}
std::string Person::getName()const {
    return this->name;
}
unsigned int Person::getId()const {
    return this->id;
}
Vehicle* Person::getVehicleAt(int n)const {
    if (n>=arr.size() )
        throw std::runtime_error("There are not enough Vehicles");
return this->arr[n];
}
std::size_t Person::vehicleCount()const {
    return this->arr.size();
}
