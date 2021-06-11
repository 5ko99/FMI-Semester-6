#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

class Vehicle;
class Person;

class Registration
{
    std::string regnum{};

public:
    Registration() = delete;
    Registration(const std::string& reg)
    {
        unsigned len = reg.length();
        if(len == 7)
        {
            if(isalpha(reg[0]) && isdigit(reg[1]) && isdigit(reg[2]) && isdigit(reg[3]) && isdigit(reg[4]) && isalpha(reg[5]) && isalpha(reg[6]))
            {
                regnum = reg;
            }
        }
        else if(len == 8)
        {
            if(isalpha(reg[0]) && isalpha(reg[1]) && isdigit(reg[2]) && isdigit(reg[3]) && isdigit(reg[4]) && isdigit(reg[5]) && isalpha(reg[6]) && isalpha(reg[7]))
            {
                regnum = reg;
            }
            else
            {
                throw std::invalid_argument ("Wrong registration type!");
            }


        }
        else
        {
            throw std::invalid_argument ("The registration is more characters than allowed!");
        }

    }

    friend std::ostream& operator<<(std::ostream& out, const Registration& registration)
    {
        out << registration.regnum;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Registration& registration)
    {
        in >> registration.regnum;
        return in;
    }
    std::string getReg() const
    {
        return regnum;
    }

};

class Vehicle
{
    Registration registrNum;
    std::string description{};
    unsigned int owner{};

public:
    Vehicle( Registration& reg, const std::string& str, unsigned int person) : registrNum(reg), description(str), owner(person){}
    Vehicle( Registration& reg, const std::string& str) : registrNum(reg), description(str){}

    void printVehicle() const
    {
        std::cout<<"Registration: "<<registrNum.getReg()
                 <<"\nDescriprtion: "<< description
                 <<"\nOwner: "<<owner<<"\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Vehicle& car)
    {
        out << "Registration:" << car.registrNum << "\nDesctription: " << car.description << "\n Owner(id): " << car.owner;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Vehicle& car)
    {
        in >> car.registrNum >> car.description >> car.owner;
        return in;
    }
    std::string getRegistrNum() const
    {
        return registrNum.getReg();
    }

    void possession(const unsigned id)
    {
        owner  = id;
    }
    unsigned getOwner() const
    {
        return owner;
    }
};

class Person
{
    std::string name{};
    unsigned int UCN{};
    std::vector<Vehicle> vehicles{};

public:
    Person()=default;
    Person(const std::string& name, unsigned int num) : name(name), UCN(num){}

    unsigned int getUCN() const
    {
        return UCN;
    }

    std::vector<Vehicle>* getVehicles()
    {
        return &vehicles;
    }
    friend std::ostream& operator<<(std::ostream& out, const Person& person)
    {
        out << "Name: " << person.name << " UCN: " << person.UCN << " ";
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Person& person)
    {
        std::cout << "Name: ";
        in >> person.name;
        std::cout <<"UCN: ";
        in >> person.UCN;
        return in;
    }
    void addCar(Vehicle& car)
    {

        vehicles.push_back(car);
    }

    Vehicle* getVehicleByRegnum(const std::string& str)
    {
        for(int i = 0; i < vehicles.size(); ++i)
        {
            if(str == vehicles[i].getRegistrNum())
            {
                return &vehicles[i];
            }
        }
        return nullptr;
    }


    void deleteCar(const std::string& str)
    {
        Vehicle* newVehicle = getVehicleByRegnum(str);
        if(!newVehicle)
        {
            throw std::invalid_argument("trying to delete a not possessed car!");
        }
        int i=0;
        for(; i<vehicles.size(); ++i)
        {
            if(str == vehicles[i].getRegistrNum())
                break;
        }
        vehicles.erase(vehicles.begin() + i);
    }

};





class PeopleList
{
    std::vector<Person> people;

    Person* getPersonByUCN(const unsigned& ucn)
    {
        for(int i=0; i<people.size(); ++i)
        {
            if(people[i].getUCN() == ucn)
            {
                return &people[i];
            }
        }
        return nullptr;
    }

public:
    void printPeople() const
    {
        for(int i = 0; i < people.size() ;++i)
        {
            std::cout << people[i] <<"\n";
        }
    }
    void deletePerson(const unsigned id)
    {
        Person* newPerson = getPersonByUCN(id);
        if(newPerson)
        {
            int i=0;
            for( ; i<people.size(); ++i)
            {
                if(id == people[i].getUCN())
                {
                    break;
                }
            }

            std::vector<Vehicle> newV = *(people[i].getVehicles());
            for(int j =0; j < newV.size(); ++j)
            {
                people[0].addCar( newV[j] );
                newPerson->deleteCar(newV[j].getRegistrNum());
            }

            people.erase(people.begin() + i);
        }
        else
        {
            throw std::invalid_argument ("There is no such person to be deleted in this list!");
        }
    }
    friend std::ostream& operator<<(std::ostream& out, PeopleList& people_collection)
    {
        for(int i=0; i<people_collection.people.size(); i++)
        {
        std::cout << people_collection.people[i] << std::endl;
        out << people_collection.people[i] << std::endl;
        }
        return out;
    }


    friend PeopleList& operator<<(PeopleList& people_collection, const Person& person)
    {
        if(people_collection.getPersonByUCN(person.getUCN()))
        {
            throw std::invalid_argument ("This person is already in the list!");
        }

        people_collection.people.push_back(person);
        return people_collection;
    }
    bool operator!()
    {
        return people.empty();
    }

    void addPerson(const std::string& name, unsigned int id)
    {
        Person newPerson(name, id);
        people.push_back(newPerson);
    }

    void acquire(const unsigned id, const std::string& reg)
    {
        Person* newPerson = getPersonByUCN(id);
        Vehicle* newVehicle;
        if(!newPerson)
        {
            throw std::invalid_argument ("There is no such a person in the list!");
        }
        for(int i = 0; i < people.size(); ++i)
        {
            if(newVehicle = people[i].getVehicleByRegnum(reg))
                break;
        }
        if(!newVehicle)
        {
            throw std::invalid_argument("There is no such a car in the list!");
        }
        newPerson->addCar(*newVehicle);
        Person* oldOwner = getPersonByUCN(newVehicle->getOwner());
        oldOwner->deleteCar(reg);
        newPerson->addCar(*newVehicle);
        newVehicle->possession(id);
    }

    void release(unsigned const id, const std::string& reg)
    {
        Person* newPerson = getPersonByUCN(id);
        Vehicle* newVehicle;
        if(!newPerson)
        {
            throw std::invalid_argument ("There is no such a person in the list!");
        }
        for(int i = 0; i < people.size(); ++i)
        {
            if(newVehicle = people[i].getVehicleByRegnum(reg))
                break;
        }
        if(!newVehicle)
        {
            throw std::invalid_argument("There is no such a car in the list!");
        }

        people[0].addCar(*newVehicle);
        newPerson->deleteCar(reg);
    }

    template <typename T>
    void remove(const T& id)
    {
        if(typeid(id).name() == typeid(std::string).name())
        {
            Vehicle* newVehicle;
            if(newVehicle->getOwner()!=0)
            {
                std::string answer;
                std::cout<<"Are you sure you want to delete this vehicle(\"yes\" or \"no\")?\nAnswer: ";
                std::cin >> answer;
                if(answer == "yes")
                {
                    for(int i = 0; i < people.size(); ++i)
                    {
                        if(newVehicle = people[i].getVehicleByRegnum(id))
                            break;
                    }
                    if(!newVehicle)
                    {
                        throw std::invalid_argument("There is no such a car in the list!");
                    }
                    Person* newPerson = getPersonByUCN(newVehicle->getOwner());
                    newPerson->deleteCar(id);
                }
            }

        }
        else if(typeid(id).name() == typeid(unsigned).name())
        {
            std::string answer;
            std::cout<<"Are you sure you want to delete this person(\"yes\" or \"no\")?\nAnswer: ";
            std::cin >> answer;
            if(answer == "yes")
                deletePerson(id);
        }
    }

    template <typename T>
    void show(const T& comm)
    {
        if(typeid(comm).name() == typeid(std::string).name())
        {
            Registration newReg(comm);
            if(newReg.getReg()!="")
            {
                Vehicle* newVehicle;
                for(int i = 0; i < people.size(); ++i)
                {
                    if(newVehicle = people[i].getVehicleByRegnum(comm))
                        break;
                }
                if(!newVehicle)
                {
                    throw std::invalid_argument("There is no such a car in the list!");
                }
                std::cout << *newVehicle;
            }
            else if(comm=="people")
            {
                for(int i=0;i<people.size();++i)
                {
                    printPeople();
                }
                return;
            }
            else if(comm=="vehicles")
            {
                for(int i=0; i<people.size() ;++i)
                {
                    std::vector<Vehicle> newV = *(people[i].getVehicles());
                    for(int j=0; j < newV.size();++j)
                        std::cout << newV[j];
                }
                return;
            }

        }
        else if(typeid(comm).name() == typeid(unsigned).name())
        {
            Person* newPerson = getPersonByUCN(comm);
            std::vector<Vehicle> newV = newPerson->getVehicles();
            for(int j=0; j < newV.size();++j)
                        std::cout << newV[j];
        }
    }


    void addVehicle(Registration& reg, const std::string& descript)
    {
        std::string carId=reg.getReg();
        Vehicle* newVeh;
        for(int i = 0; i< people.size(); ++i)
        {
            newVeh = people[i].getVehicleByRegnum(carId);
            std::cout<<newVeh<<std::endl;
            if(!newVeh)
                break;
        }
        if(!newVeh)
        {
            Vehicle car(reg, descript);
            people[0].addCar(car);
        }
        else
            std::cout<<"This vehicle already in the list!\n";
    }

};

std::string tolower(const std::string& comm)
{
    std::string help= comm;
    for(int i=0;i<help.size();++i)
    {

        if(help[i]>='A' && help[i]<='Z')
        {
            help[i] = help[i]-'A'+'a';
        }
    }
    return help;
}

/*
моята идея беше да пазя информацията във вектор по следния начин:

/нулевата позиция на вектора, място на което се пазят превозните средства без собственици(при създаването) или тези които са били release-нати/
име(0)(showroom), 0, кола1, кола2, ....

име(1)(showroom), егн, кола1, кола2, ....
име(2)(showroom), егн, кола1, кола2, ....
        |
        |
        |
име(n)(showroom), егн, кола1, кола2, ....

*/


int main(int argc, char* argv[])
{
    PeopleList peopleCollection{};
    std::string file_name = "info.csv";
    if(argc == 2)
    {
        file_name = argv[1];
    }
    std::ifstream in{file_name};
    if(!in)
    {
        std::cout<<"Error opening file\n";
        return 0;
    }
    while(true)
    {
        Person person;
        in >> person;
        if(in.eof())
        {
            break;
        }
        peopleCollection << person;
    }

    while(true)
    {
        std::cout<<"If you want to stop the program type \"exit\"\n";
        std::cout<<"enter command:";
        std::string command;
        std::cin >> command;

        if(tolower(command) == "exit")
        {
            break;
        }
        if(tolower(command) == "vehicle")
        {
            std::string str;
            std::cin>>str;
            Registration registr(str);
            std::cin>>str;
            Vehicle veh(registr, str);
           peopleCollection.addVehicle(registr, str);

        }
        if(tolower(command) == "person")
        {
            std::string str;
            std::cin>>str;
            unsigned int id;
            std::cin>>id;
            Person person(str,id);
            peopleCollection << person;


        }
        if(tolower(command) == "acquire")
        {
            unsigned int id;
            std::cin>>id;
            std::string str;
            std::cin>>str;
            peopleCollection.acquire(id, str);
        }
        if(tolower(command) == "release")
        {
            unsigned int id;
            std::cin>>id;
            std::string str;
            std::cin>>str;
            peopleCollection.release(id, str);
        }
//        if(tolower(command) == "remove")
//        {
//            bool digit=true;
//            std::string str;
//            std::cin>>str;
//            char buffer[50];
//            for(int i=0;i<str.size(); ++i)
//            {
//                buffer[i] = str[i];
//                if(!isdigit(str[i]))
//                {
//
//                    digit = false;
//                    break;
//                }
//            }
//            unsigned id;
//            if(digit)
//         {
//              id = atoi(buffer);
//               peopleCollection.remove(id);
//            }
//            else{
//                peopleCollection.remove(str);
//            }
//
//
//        }
//
//        if(tolower(command) == "show")
//        {
//            bool digit=true;
//            std::string str;
//            std::cin>>str;
//            char buffer[50];
//            for(int i=0;i<str.size(); ++i)
//            {
//                buffer[i] = str[i];
//                if(!isdigit(str[i]))
//                {
//
//                    digit = false;
//                    break;
//                }
//            }
//            unsigned id;
//            if(digit)
//            {
//                id = atoi(buffer);
//                peopleCollection.show(id);
//            }
//            else{
//                peopleCollection.show(str);
//            }
//        }

    }

    in.close();
    std::ofstream out{file_name};
    out << peopleCollection;
    out.close();



    return 0;
}
