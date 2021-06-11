#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <vector>

class Person
{
public:
    Person(const char *str_name, unsigned int &id_number);
    Person();
    ~Person() {};

    void setID(unsigned int id_set);
    void setName(const char *str);
    std::string getPersonName() const;
    int getID() const;
    void printPerson() const;
    void printPersonSmallInfo() const;
    void addNewRegNumber(const char *str);
    int numberOfVehicles() const;
    bool removeVehicle(const char *str);

private:
    std::string name;
    unsigned int id;
    std::vector<std::string> regcars;
};

Person::Person(const char *str_name, unsigned int &id_number)
{
    name=convertToString(str_name, strsize(str_name));
    id=id_number;
}
Person::Person()
    : name(""), id(0)
{

}

void Person::printPerson() const
{
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"ID: "<<id<<std::endl;

    int sz=numberOfVehicles(), i;
    for(i=0; i<sz; i++)
    {
        std::cout<<i<<": "<<regcars[i]<<std::endl;
    }
}
void Person::printPersonSmallInfo() const
{
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"ID: "<<id<<std::endl;
}

void Person::setID(unsigned int id_set)
{
    id=id_set;
}
void Person::setName(const char *str)
{
    name=convertToString(str, strsize(str));
}

std::string Person::getPersonName() const
{
    return name;
}

int Person::getID() const
{
    return id;
}

void Person::addNewRegNumber(const char *str)
{
    regcars.push_back(convertToString(str, strsize(str)));
}

int Person::numberOfVehicles() const
{
    return regcars.size();
}

bool Person::removeVehicle(const char *str)
{
    int sz=numberOfVehicles(), i;
    std::string regnumber=convertToString(str, strsize(str));
    for(i=0; i<sz; i++)
    {
        if(regcars[i]==regnumber)
        {
            std::cout<<getPersonName()<<"-registration number "<<regnumber<<" has been removed!"<<std::endl;
            regcars.erase(regcars.begin() + i);
            return true;
        }
    }
    return false;
}

#endif // PERSON_H_INCLUDED
