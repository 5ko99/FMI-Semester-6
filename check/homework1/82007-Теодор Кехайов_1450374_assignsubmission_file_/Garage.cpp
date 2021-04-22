#include "Garage.h"

/// създава гараж с максимално място за паркиране size
Garage::Garage(std::size_t size): space(size),vehicleCounter(0),occupiedSpace(0)
{
    vehicles = new Vehicle*[vehicleCounter+1];
    vehicles[vehicleCounter]= nullptr;
}

/// copy constructor
Garage::Garage(const Garage& garage): space(garage.space), vehicleCounter(garage.vehicleCounter),occupiedSpace(garage.occupiedSpace)
{
    vehicles = new Vehicle*[vehicleCounter+1];
    vehicles[vehicleCounter]= nullptr;
    for (int i = 0; i < vehicleCounter; i++)
    {
        vehicles[i]=garage.vehicles[i];
    }
}

/// copy assignment operator
Garage& Garage::operator= (const Garage& g)
{
    if (this != &g)
    {
        auto temp = new Vehicle*[g.space];
        for (std::size_t i = 0; i < g.vehicleCounter; i++)

               temp[i]=g.vehicles[i];

        delete [] vehicles;
        vehicles = temp;
        vehicleCounter = g.vehicleCounter;
        space = g.space;
    }

    return *this;
}

/// добавя превозното средство v в гаража
void Garage::insert(Vehicle& v)
{
    for (int i = 0; i < vehicleCounter; i++)
    {
        if(MyString(v.registration())==MyString(vehicles[i]->registration()))
            throw std::out_of_range("There is a vehicle with the same registration!");
    }

    if (occupiedSpace + v.space() > space)
            throw std::out_of_range("There is no enough space for this vehicle!");


    this->vehicles[vehicleCounter]=&v;
    this->vehicleCounter+=1;
    this->occupiedSpace+=v.space();

}

/// премахва колата с регистрационен номер registration от гаража
void Garage::erase(const char* registration)
{
    std::size_t temp=vehicleCounter;
    for (int i = 0; i < vehicleCounter; i++)
    {
        if(MyString(vehicles[i]->registration())==MyString(registration))
        {
            this->occupiedSpace-=vehicles[i]->space();
            vehicles[i]= nullptr;
            vehicles[i]=vehicles[vehicleCounter-1];
            vehicleCounter--;
        }
    }

}

/// достъп до елемента намиращ се на позиция pos
/// позиции от 0 до vehiclesCounter-1
const Vehicle& Garage::at(std::size_t pos) const
{
    if(pos>=vehicleCounter) throw std::out_of_range("Incorrect position of vehicle!");
    return *vehicles[pos];
}

///  достъп до елемента намиращ се на позиция pos
const Vehicle& Garage::operator[](std::size_t pos) const
{
    return *vehicles[pos];
}

/// Проверява дали гаражът е празен
bool Garage::empty() const
{
    if(occupiedSpace==0) return true;
    return false;
}

/// брой елементи (превозни средства) в гаража
std::size_t Garage::size() const
{
    return this->vehicleCounter;
}

/// изчиства съдържанието на гаража
void Garage::clear()
{
    for (int i = 0; i < vehicleCounter; i++)
    {
        vehicles[i]= nullptr;
    }
    vehicleCounter=0;
    occupiedSpace=0;
}

/// намира и връща превозното средство с регистрационен номер registration в гаража
const Vehicle* Garage::find(const char* registration) const
{
    for (int i = 0; i < vehicleCounter; i++)
    {
        if(MyString(vehicles[i]->registration())==MyString(registration))
            return vehicles[i];
    }

    return nullptr;
}

/// destructor
Garage::~Garage()
{
    delete [] vehicles;
}