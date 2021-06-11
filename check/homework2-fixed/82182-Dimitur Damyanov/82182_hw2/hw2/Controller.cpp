#include "Registration.hpp"
#include "Person.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"
#include <algorithm>
#include <fstream>
#include <cstring>
#include "utils.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Controller::~Controller()
{
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        delete vehicles[i];
    }

    for (size_t i = 0; i < people.size(); i++)
    {
        delete people[i];
    }

    cout << "DELETED" << endl;
}

Person* Controller::find(unsigned int id)
{
    for (std::vector<Person*>::iterator it = people.begin(); it != people.end(); it++)
    {
        if((**it).getId() == id)
        {
            return *it;
        }
    }

    return nullptr;
}

Vehicle* Controller::find(const Registration& reg)
{
    for (std::vector<Vehicle*>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
    {
        if((**it).getRegistration() == reg)
        {
            return *it;
        }
    }

    return nullptr;
}

std::vector<Person*>::iterator Controller::findIterator(unsigned int id)
{
    for (std::vector<Person*>::iterator it = people.begin(); it != people.end(); it++)
    {
        if((**it).getId() == id)
        {
            return it;
        }
    }

    return people.end();
}

std::vector<Vehicle*>::iterator Controller::findIterator(const Registration& reg)
{
    for (std::vector<Vehicle*>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
    {
        if((**it).getRegistration() == reg)
        {
            return it;
        }
    }

    return vehicles.end();
}

Person* Controller::findPersonByVehicle(Registration& reg)
{
    for (auto it = people.begin(); it != people.end(); it++)
    {
        if((**it).has(reg))
        {
            return *it;
        }
    }

    return nullptr;
}

Vehicle& Controller::create(const Registration& reg, const string& desc)
{
    if(find(reg))
    {
        throw std::invalid_argument("Vehicle with this registration already exists.");
    }

    vehicles.push_back(new Vehicle(reg, desc));

    return *(vehicles.back());
}

Person& Controller::create(const string& name, unsigned int id)
{
    if(find(id))
    {
        throw std::invalid_argument("Person with this id already exists.");
    }

    people.push_back(new Person(name, id));

    return *(people.back());
}

void Controller::acquire(unsigned int id, const Registration& reg)
{
    Person* p = find(id);
    Vehicle* v = find(reg);

    if(!v)
    {
        throw std::invalid_argument("Vehicle with this registration doesn't exist.");
    }

    if(!p)
    {
        throw std::invalid_argument("Person with this id doesn't exist.");
    }

    p->addVehicle(v);
}

void Controller::release(unsigned int id, const Registration& reg)
{
    Person* p = find(id);
    Vehicle* v = find(reg);

    if(!v)
    {
        throw std::invalid_argument("Vehicle with this registration doesn't exist.");
    }

    if(!p)
    {
        throw std::invalid_argument("Person with this id doesn't exist.");
    }

    p->removeVehicle(reg);
}

bool Controller::remove(unsigned int id, bool interactive)
{
    std::vector<Person*>::iterator p_it = findIterator(id);

    if(p_it != people.end())
    {
        bool confirmation = true;

        if(interactive && (**p_it).getVehiclesCount())
        {
            cout << "Owner field in all associated vehicles will be set to null, do you want to proceed? (Y/n)";
            confirmation = getConfirmation();
        }

        if(confirmation)
        {
            (**p_it).clear();
            people.erase(p_it);
            return true;
        }
    }
    else
    {
        throw std::invalid_argument("Person with this id doesn't exist.");
    }
    return false;
}

void Controller::remove(const Registration& reg, bool interactive)
{
    std::vector<Vehicle*>::iterator v_it = findIterator(reg);

    if(v_it != vehicles.end())
    {
        bool confirmation = true;
        auto owner = (*v_it)->getOwner();

        if(interactive && owner)
        {
            cout << "This vehicle will be unlinked from owner, do you want to proceed? (Y/n)";
            confirmation = getConfirmation();
        }

        if(confirmation)
        {
            if(owner)
            {
                owner->removeVehicle((*v_it)->getRegistration());
            }

            vehicles.erase(v_it);
        }
    }
    else
    {
        throw std::invalid_argument("Vehicle with this registration doesn't exist.");
    }
}

void Controller::show(string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);

    if(s == "VEHICLES")
    {
        if(vehicles.size())
        {
            for (std::vector<Vehicle*>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
            {
                cout << **it << endl;
            }
        }
        else{
            cout << "- no vehicles to show." << endl;
        }
    }
    else if(s == "PEOPLE")
    {
        if(people.size())
        {
            for (std::vector<Person*>::iterator it = people.begin(); it != people.end(); it++)
            {
                cout << **it << endl;
            }
        }
        else
        {
            cout << "- no people to show." << endl;
        }
    }
    else
    {
        Vehicle* v = find(s);
        if(!v)
        {
            throw std::invalid_argument("Vehicle with this registration doesn't exist.");
        }

        cout << *v << endl;
    }
}

void Controller::show(unsigned int id)
{
    Person* p = find(id);

    if(!p)
    {
        throw std::invalid_argument("Person with this id doesn't exist.");
    }

    cout << *p << endl;
    p->printVehicles();
}

bool Controller::save(const string& path)
{
    std::ifstream in(path);
    bool confirmation = true;

    if(in.good())
    {
        cout << "File will be overridden, do you want to proceed? (Y/n)";

        skipWhitespaces(cin);

        confirmation = getConfirmation();
    }

    if(confirmation)
    {
        std::ofstream out;
        out.open(path);

        for (std::vector<Person*>::iterator it = people.begin(); it != people.end(); it++)
        {
            out << "PERSON " << '\"' << (*it)->getName() << '\"' << ' ' << (*it)->getId() << '\n';
        }

        for (std::vector<Vehicle*>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
        {
            out << "VEHICLE " << (*it)->getRegistration() << ' ' << (*it)->getDescription() << '\n';

            Person* owner = (*it)->getOwner();

            if(owner)
            {
                out << "ACQUIRE " << owner->getId() << ' ' << (*it)->getRegistration() << '\n';
            }
        }

        out.close();

        return true;
    }

    return false;
}

void Controller::load(const string& path)
{
    std::ifstream src;
    src.open(path, std::ios::in);

    if(!src)
    {
        throw std::invalid_argument("File doesn't exist.");
    }

    cout << "Importing from " << path << endl;

    run(src, true);

    cout << "End of import" << endl;
}

void Controller::run(std::istream& src, bool interactive)
{
    while(!src.eof())
    {
        try
        {
            string command;
            src >> command;

            std::transform(command.begin(), command.end(), command.begin(), ::tolower);

            if (command == "vehicle")
            {
                string reg;
                src >> reg;

                skipWhitespaces(src);

                string desc = inputString(src);

                Vehicle& v = create(reg, desc);

                if(interactive)
                {
                    cout << v << endl;
                }
            }
            else if (command == "person")
            {
                string name = inputString(src);

                unsigned int id;
                src >> id;

                Person& p = create(name, id);

                if(interactive)
                {
                    cout << p << endl;
                }
            }
            else if (command == "acquire")
            {
                unsigned int id;
                src >> id;

                skipWhitespaces(src);

                string reg;
                src >> reg;

                acquire(id, reg);

                Person* p = find(id);
                Vehicle* v = find(reg);

                if(interactive)
                {
                    cout << "- " << p->getName() << " acquired vehicle " << v->getRegistration() << endl;
                }
            }
            else if (command == "release")
            {
                unsigned int id;
                src >> id;

                string reg;
                src >> reg;

                release(id, reg);

                Person* p = find(id);

                if(interactive)
                {
                    cout << "- " << p->getName() << " released vehicle " << reg << endl;
                }
            }
            else if (command == "remove")
            {
                string str;
                src >> str;

                if(isNumber(str))
                {
                    unsigned int id = std::stoi(str);

                    string name = find(id)->getName();

                    bool success = remove(id, interactive);

                    if(interactive && success)
                    {
                        cout << "- removed " << name << endl;
                    }
                }
                else{
                    string reg = find(str)->getRegistration().getString();

                    remove(str, interactive);

                    if(interactive)
                    {
                        cout << "- removed " << reg << endl;
                    }
                }
            }
            else if (command == "save")
            {
                string path = inputString(src);
                bool success = save(path);

                if(interactive)
                {
                    if(success)
                    {
                        cout << "Data saved in " << path << endl;
                    }
                    else{
                        cout << "Failed to save data in " << path << endl;
                    }
                }
            }
            else if (command == "show")
            {
                string str;
                src >> str;

                if(isNumber(str))
                {
                    unsigned int id = std::stoi(str);
                    show(id);
                }
                else
                {
                    show(str);
                }
            }
            else{
                if(interactive)
                {
                    if(command.length() == 1 && command[0] != '\0')
                    {
                        cout << "Invalid command: \"" << command << "\"" << endl;
                    }
                }
            }
        }
        catch(std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

Controller& Controller::getInstance()
{
    static Controller instance;
    return instance;
}
