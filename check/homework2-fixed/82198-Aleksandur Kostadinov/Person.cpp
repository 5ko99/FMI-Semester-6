#include "VehicleAndPerson.h"

std::vector<Person> Person::existing_people;
size_t Person::count_of_existing_people = 0;

void Person::swap(size_t i, size_t j, std::vector<Person> &people)
{
    if (i != j)
    {
        Person temp(people[i]);
        people[i] = people[j];
        people[j] = temp;
    }
}

Person::Person()
{
    this->name = "";
    this->person_id = 0;
}
Person::Person(std::string name, unsigned int id)
{
    try
    {
        if (name.length() < 1)
        {
            throw std::length_error("");
        }

        if (id == 0)
        {
            throw 404;
        }

        this->name = name;
        this->person_id = id;

        if (in_existing_people(*this))
        {
            clear();
        }
    }
    catch (std::length_error)
    {
        std::cerr << "Initialization failed! Please enter a name!" << '\n';

        clear();
    }
    catch (int)
    {
        std::cerr << "Initialization failed! Please enter a valid id!" << '\n';

        clear();
    }
    catch (...)
    {
        std::cerr << "Initialization failed! An Error has occurred!" << '\n';

        clear();
    }

    if (!in_existing_people(*this) && this->name.length() >= 1 && person_id != 0)
    {
        existing_people.push_back(*this);
        count_of_existing_people++;
        std::cout << "Person created!\n";
    }
}

Person::Person(const Person &other)
{
    copy(other);
}

Person &Person::operator=(const Person &other)
{
    if (this != &other)
    {
        copy(other);
    }

    return *this;
}

void Person::add_vehicle(Vehicle &vehicle)
{
    if (!in_vehicles(vehicle))
    {
        vehicle.add_owner(*this);
    }
}

void Person::copy(const Person &other)
{
    try
    {
        this->name = other.name;
        this->person_id = other.person_id;
        this->vehicles = other.vehicles;
    }
    catch (...)
    {
        std::cerr << "Copying failed! Returning default values! " << '\n';
        this->clear();
    }
}

bool Person::in_vehicles(const Vehicle &vehicle) const
{
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        if ((this->vehicles[i]) == vehicle)
        {
            std::cout << "This vehicle is in the person's vehicles\n";
            return true;
        }
    }

    return false;
}

void Person::clear()
{
    this->person_id = 0;
    this->name = "";
    this->vehicles.clear();
}

bool Person::in_existing_people(const Person &person)
{
    if (count_of_existing_people > 0)
    {
        for (size_t i = 0; i < count_of_existing_people; i++)
        {
            try
            {
                if (existing_people[i] == person)
                {
                    throw std::invalid_argument("");
                }
            }
            catch (std::invalid_argument)
            {
                std::cerr << "This person already exists!!" << '\n';
                return true;
            }
        }
    }

    return false;
}

void Person::print_person(unsigned int id)
{
    for (size_t i = 0; i < existing_people.size(); i++)
    {
        if (id == existing_people[i].person_id)
        {
            std::cout << existing_people[i].name << " : ";
            print_vehicles(existing_people[i]);
            std::cout << "\n";
            return;
        }
    }

    std::cout << "Person not found!\n";
}

bool Person::operator==(const Person &other)
{
    return this->person_id == other.person_id;
}

void Person::print_all_people()
{
    for (size_t i = 0; i < count_of_existing_people; i++)
    {
        std::cout << existing_people[i].name << " " << existing_people[i].person_id << "\n";
    }
}

void Person::print_vehicles(const Person &person)
{
    for (size_t i = 0; i < person.vehicles.size(); i++)
    {
        std::cout << person.vehicles[i].get_desc() << " " << (person.vehicles[i].get_id().get_registration()) << " | ";
    }
    std::cout << "\n";
}

void Person::remove_person(unsigned int id)
{
    try
    {
        for (size_t i = 0; i < count_of_existing_people; i++)
        {
            if (id == existing_people[i].get_id())
            {
                if (get_all_vehicles(&existing_people[i]).size() > 0)
                {
                    std::cout << "This person owns " << get_all_vehicles(&existing_people[i]).size() << " vehicles. ";
                    std::cout << "Are you sure about removing this person?\n Yes : No\n";

                    std::string yes_no;
                    std::getline(std::cin, yes_no);
                    yes_no = Validation::to_upper_all(yes_no);
                    
                    if (yes_no == "YES")
                    {
                        for (size_t j = 0; j < existing_people[i].vehicles.size(); j++)
                        {
                            for (size_t k = 0; k < Vehicle::existing_vehicles.size(); k++)
                            {
                                if (existing_people[i].vehicles[j] == Vehicle::existing_vehicles[k])
                                {
                                    Vehicle::existing_vehicles[k].set_owner(nullptr);
                                }
                            }
                        }

                        std::cout << existing_people[i].get_name() << " " << existing_people[i].get_id() << " was removed!\n";
                        //  swap_vehicles(i, count_of_existing_people - 1);
                        swap(i, count_of_existing_people - 1, existing_people);

                        existing_people.pop_back();

                        count_of_existing_people--;
                    }
                    else if (yes_no != "YES" && yes_no != "NO")
                    {
                        std::cout << "Invalid answer! The person remains in the database!\n";
                    }
                }
                else
                {
                    std::cout << existing_people[i].get_name() << " " << existing_people[i].get_id() << " was removed!\n";
                    // swap_vehicles(i, count_of_existing_people - 1);
                    swap(i, count_of_existing_people - 1, existing_people);

                    for (size_t j = 0; j < existing_people[i].vehicles.size(); j++)
                    {
                        for (size_t k = 0; k < Vehicle::existing_vehicles.size(); k++)
                        {
                            if (existing_people[i].vehicles[j] == Vehicle::existing_vehicles[k])
                            {
                                Vehicle::existing_vehicles[k].set_owner(&existing_people[i]);
                            }
                        }
                    }
                    existing_people.pop_back();

                    count_of_existing_people--;
                }

                return;
            }
        }

        throw std::invalid_argument("");
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Person not found!" << '\n';
    }
}
