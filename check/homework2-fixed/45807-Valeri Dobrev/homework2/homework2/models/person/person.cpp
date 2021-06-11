#include "person.hpp"


Person::Person(const unsigned int id, const std::string& name): name(name), id(id){
}

Person::~Person(){
    this->vehicles.clear();
}

Person::Person(const Person& other): Person(other.id, other.name){
    for(Vehicle* v: other.vehicles){
        this->vehicles.push_back(v);
    }
}

Person& Person::operator=(const Person& other){
    if(this == &other) return *this;

    this->id = other.id;
    this->name = other.name;

    this->vehicles.clear();
    for(Vehicle* v: other.vehicles){
        this->vehicles.push_back(v);
    } 
    return *this;
}


bool Person::operator==(const unsigned id) const {
    return this->id == id;
}

const bool Person::needConfirmToDelete() const{
    return this->vehicles.size() != 0;
}

void Person::prepareForDelete(){
    for(Vehicle* v: this->vehicles){
        removeVehicle(v);
    }
}

const std::string& Person::getName()const{ return name;}

const unsigned& Person::getId() const{ return id; }

const std::string Person::getClassName(){ return "Person";}
const std::string Person::getIdToString()const{
    return std::to_string(id); 
}

const size_t Person::getNumberOfVehicles() const{ return this->vehicles.size(); }

const std::vector<Vehicle*>& Person::getVehicles() const{ return this->vehicles; }

void Person::addVehicle(Vehicle* vehicle){
    if(!vehicle) throw std::invalid_argument("Vehicle cannot be null!");
    vehicle->setOwner(this);
}
void Person::removeVehicle(Vehicle* vehicle){
    if(!vehicle) throw std::invalid_argument("Vehicle cannot be null!");
    if(!this->hasVehicle(vehicle)) throw std::invalid_argument("Vehicle not found!");
    vehicle->setOwner(nullptr);
}


void Person::add(Vehicle* vehicle){
    if(!vehicle) throw std::invalid_argument("Vehicle cannot be null!");
    this->vehicles.push_back(vehicle);
}
void Person::remove(Vehicle* vehicle){
    if(!vehicle) throw std::invalid_argument("Vehicle cannot be null!");
    for(unsigned int i = 0; i < this->vehicles.size();i++){
        if(this->vehicles[i]==vehicle){
            this->vehicles.erase(this->vehicles.begin()+i);
            return;
        }
    }
}

bool Person::hasVehicle(const Vehicle* vehicle)const{
    for(Vehicle* v : this->vehicles){
        if(v==vehicle) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os,const Person& p){
    os<<"ID: "<<p.id << " Name: "<<p.name<<"\nVehicles:\n";
    for(Vehicle* v : p.vehicles){
        os<<*v << "\n";
    } 
    return os;
}


