#include <vector>

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

///Forward class
class Vehicle;

class Person
{
private:
    std::string name;
    unsigned int id;
    std::vector<std::reference_wrapper<const Vehicle>> cars;


public:

    Person();

    Person(const std::string name, const unsigned int id);

    Person(const Person& person);

    Person& operator=(const Person& source);

    void addCar(const Vehicle& vehicle);

    friend std::ostream& operator<<(std::ostream &out, const Person &person);

    const std::string getName() const;

    const unsigned int getId() const;

    const bool ownCar(std::string reg);

    bool hasCar();

    void releaseCar(std::string reg);

    std::vector<std::string> getAllRegistrations();

    /*!void setCars(list<Vehicle> cars)
    {
        for(auto it = l.begin() ; it != l.end(). ; it++)
        {
            this->cars[it] = *it;
        }
    }*/

    /*!list<Vehicle> getCars()
    {
        return this->cars;
    }*/


    ~Person();

};


#endif // PERSON_H_INCLUDED
