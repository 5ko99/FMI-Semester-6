#include "Garage.h"
#include <cassert>
#include <cstring>

//constructors
// +
Garage::Garage(std::size_t size)
{
    // създава гараж с максимално място за паркиране size.
    /* Като следствие от по-горното – гаражът НЕ БИВА 
     * да копира обектите в себе си, а да пази някакъв вид препратка 
     * (например указател) към превозните средства, които се пазят в него.
     */

    //Превозните средства съществуват независимо от гаража.
    //Той ги регистрира в себе си, но нито ги създава,
    //нито има грижата да ги унищожава.

    capacity = size;
    vehicle = new Vehicle *[capacity];
}

// +
Garage::~Garage()
{
    // Destructor
    delete[] vehicle;
    vehicle = nullptr;
}

/*******************************************************************/
// add delete
// +
void Garage::insert(Vehicle &v)
{
    // добавя превозното средство v в гаража. Ако операцията не успее (например няма достатъчно памет, в гаража няма повече място за паркиране, вече има кола със същия регистрационен номер), да се хвърля изключение. Операцията да дава strong exception guarantee.
    if (valid(v))
    {
        vehicle[numCars] = &v;
        numCars++;
    }
    else
    {
        throw std::invalid_argument("invalid input");
    }
}

// +
void Garage::erase(const char *registration)
{
    // премахва колата с регистрационен номер registration от гаража. Ако такава няма, да не се прави нищо. При премахването на кола от гаража е допустимо да се промени редът на останалите в гаража. Това условие ще ви позволи при премахване на елемент да поставите последния елемент от масива на мястото на премахнатия, вместо да правите left shift.

    for (size_t i = 0; i < numCars; ++i)
    {
        if (strcmp(this->vehicle[i]->registration(), registration) == 0)
        {
            vehicle[i] = vehicle[numCars - 1];
            numCars--;
            return;
        }
    }
}

/*******************************************************************/
// at []
// +
const Vehicle &Garage::at(std::size_t pos) const
{
    // достъп до елемента намиращ се на позиция pos. Ако такъв няма, да се хвърля изключение std::out_of_range.
    if (pos >= numCars || pos < 0)
    {
        throw std::out_of_range("index is out of range");
    }
    return *vehicle[pos];
}

// +
const Vehicle &Garage::operator[](std::size_t pos) const
{
    //!< достъп до елемента намиращ се на позиция pos. Функцията да не прави проверка за коректност дали pos е валидна позиция. (В debug режим assert-вайте дали pos е валидна позиция)
    assert(pos < numCars);
    return *vehicle[pos];
}

/*******************************************************************/
//mischevous
// +
bool Garage::empty() const
{
    // Проверява дали гаражът е празен
    return !numCars;
}

// +
std::size_t Garage::size() const
{
    // брой елементи (превозни средства) в гаража
    return numCars;
}

// +
void Garage::clear()
{
    // изчиства съдържанието на гаража. Това означава, че в него не се съдържа нито една кола. Капацитетът му обаче остава непроменен. Така в него могат отново да се добавят нови коли
    delete[] * vehicle;
    *vehicle = nullptr;
    numCars = 0;
}

/*******************************************************************/
// find
// +
const Vehicle *Garage::find(const char *registration) const
{
    // намира и връща превозното средство с регистрационен номер registration в гаража. Ако такова няма, да се върне nullptr.
    for (size_t i = 0; i < numCars; i++)
    {
        if (strcmp(this->vehicle[i]->registration(), registration) == 0)
            return vehicle[i];
    }
    return nullptr;
}

/*******************************************************************/
// +
void Garage::print()
{
    // prints out contents of Garage
    for (size_t i = 0; i < numCars; ++i)
    {
        std::cout << "Vehicle  " << i + 1 << ":" << std::endl;
        std::cout << "  Licence plate:  " << this->vehicle[i]->registration() << std::endl;
        std::cout << "  Description:  " << this->vehicle[i]->description() << std::endl;
        std::cout << "  Space:  " << this->vehicle[i]->space() << std::endl;
    }
    std::cout << std::endl;
}

/*******************************************************************/
// private functions

// ~
bool Garage::valid(Vehicle &v)
{
    // *Трябва да се отчита капацитетa и броят на вече добавните превозни средства.
    //  Освен това, в един гараж не може да има две коли с еднакви регистрационни номера.

    int volCars = 0;
    for (size_t i = 0; i < numCars; ++i)
    {
        volCars += vehicle[i]->space();
        //licence plate

        if (strcmp(vehicle[i]->registration(), v.registration()) == 0)
        {

            return false;
        }
    }

    //capacity
    if (volCars > capacity)
        return false;

    return true;
}
