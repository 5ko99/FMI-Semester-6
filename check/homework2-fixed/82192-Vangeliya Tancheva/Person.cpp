#include <string>
#include <functional>

#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
    Person::Person()
    {

    }

    Person::Person(const std::string name, const unsigned int id)
    {
        this->name = name;
        this->id = id;
    }

    Person::Person(const Person& person)
    {
        name = person.name;
        id = person.id;

    }

    ///MyString& operator=(const MyString& source);
    Person& Person::operator=(const Person& source)
    {
        if(this == &source)
        {
            return *this;
        }

        name = source.name;
        id = source.id;

        return *this;

    }

    void Person::addCar(const Vehicle& vehicle)
    {
        cars.push_back(vehicle);
    }

    const std::string Person::getName() const
    {
        return name;
    }

    const unsigned int Person::getId() const
    {
        return id;
    }

    const bool Person::ownCar(std::string reg)
    {
        bool answer = false;
        ///Validate if person owns the car with registration reg
        for(std::vector<std::reference_wrapper<const Vehicle>>::iterator it = cars.begin(); it != cars.end(); it++)
        {
            if(it->get().getRegistration().compare(reg) == 0)
            {
                answer = true;
            }
        }

        return answer;
    }

    bool Person::hasCar()
    {
        return !cars.empty();
    }

    void Person::releaseCar(std::string reg)
    {
        unsigned int index;
        unsigned int i = 0;
        for(std::vector<std::reference_wrapper<const Vehicle>>::iterator it = cars.begin(); it != cars.end(); it++, i++)
        {
            if(it->get().getRegistration().compare(reg) == 0)
            {
                index = i;
            }
        }

        cars.erase(cars.begin() + index);
    }

    std::vector<std::string> Person::getAllRegistrations()
    {
        std::vector<std::string> temp_vec;

        for(std::vector<std::reference_wrapper<const Vehicle>>::iterator it = cars.begin(); it != cars.end(); it++)
        {
            temp_vec.push_back(it->get().getRegistration());
        }

        return temp_vec;
    }


    Person::~Person()
    {

    }
