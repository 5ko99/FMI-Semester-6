#include "Garage.h"

//Garage(std::size_t size) -- създава гараж с максимално място за паркиране size.

Garage::Garage(std::size_t size)
{
    vehicles = new Vehicle*[size];
    for(int i = 0; i < size; i++)
    {
        vehicles[i] = nullptr;
    }
    this->my_size = size;
    /// tuk trqbva
}
void Garage:: insert(Vehicle& v)
{
    int currSpaceTaken = 0;
    for(int i = 0; i<size(); i++)
    {
        currSpaceTaken+=vehicles[i]->space();
        if(vehicles[i]->registration() == v.registration())
            throw std::invalid_argument("Two vehicles with the same registration\n") ;
    }
    if((my_size - currSpaceTaken) < v.space())
        throw std::overflow_error("Not enough space\n") ;

    /// колко коли имаме в момента == колко коли можем да сложим
    if(size() >= my_size)
        throw std::overflow_error("Not enough memory\n") ;

    int i = 0;
    while(vehicles[i]!=nullptr)
    {
        i++;
    }
    // i will be the first non-null index
    vehicles[i] == &v;

   /* We have to check:
    1) If there is enough free space for the Vehicle v
    2) If there is a vehicle in the garage with the same reg as v
    3) If there is not enough memory in the garage?
        DOES that mean that I should check if the variable is
        larger than the capacity of the type, but then how to operate
        with a number larger than that that can be read?*/


}
void Garage::erase(const char* registration)
{
    // triem posredata i posledniq go slagame na negowoto mqsto
    for(int i = 0;i<size(); i++)
    {
        if(vehicles[i]->registration() == registration)
        {
            vehicles[i] = nullptr;
            vehicles[i] = vehicles[size()];
        }

    }
}
const Vehicle& Garage :: at(std::size_t pos) const
{
    if(pos < 0 || pos > size())
    {
        throw std::out_of_range("Invalid index");
    }
    return *vehicles[pos];
}

bool Garage::empty() const
{
    return size() == 0;
}
std::size_t Garage :: size() const
{
    size_t count = 0;
    int i = 0;
    while(vehicles[i]!=nullptr)
    {
        count++;
        i++;
    }

    return count;
}
void Garage::clear()
{
    /* because we know that all vehicles
    are "pushed" to the left we iterate the
    cycle only the number of cars times*/
    for(int i = 0; i< size(); i++)
    {
        vehicles[i] = nullptr;
    }
}
const Vehicle* Garage:: find(const char* registration) const
{
    size_t i;
    for( i = 0; i < size(); i++)
    {
        if(vehicles[i]->registration() == registration)
        {
            return vehicles[i];
        }
    }
    if(i == size()) return nullptr;
}

