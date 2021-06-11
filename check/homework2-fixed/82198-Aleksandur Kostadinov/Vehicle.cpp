#include "VehicleAndPerson.h"

std::vector<Vehicle> Vehicle::existing_vehicles;
size_t Vehicle::count_of_existing_vehicles = 0;

void Vehicle::swap(size_t i, size_t j, std::vector<Vehicle> &vehicles)
{
    if (i != j)
    {
        Vehicle temp(vehicles[i]);
        vehicles[i] = vehicles[j];
        vehicles[j] = temp;
    }
}

Vehicle::Vehicle() : vehicle_id("")
{
    this->owner = nullptr;
    this->description = "";
}

Vehicle::Vehicle(std::string desc, const Registration &reg)
    : vehicle_id(reg)
{
    try
    {
        if (desc.length() < 1)
        {
            throw std::length_error("");
        }

        if (reg.get_registration().length() < 1)
        {
            throw std::invalid_argument("");
        }

        this->description = desc;
        this->owner = nullptr;

        if (in_existing_vehicles(*this))
        {
            clear();
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Initialization failed! Please enter a valid registration!" << '\n';
        clear();
    }
    catch (std::length_error)
    {
        std::cerr << "Initialization failed! Please enter a valid description!" << '\n';
        clear();
    }
    catch (int)
    {
        std::cerr << "Vehicle with this registration already exists!" << '\n';
        clear();
    }

    if (this->description.length() >= 1 && this->vehicle_id.get_registration().length() >= 1 && !in_existing_vehicles(*this))
    {
        existing_vehicles.push_back(*this);
        count_of_existing_vehicles++;
        std::cout << "Car created!\n";
    }
}

Vehicle::Vehicle(const Vehicle &other) : vehicle_id(other.vehicle_id)
{
    copy(other);
}

Vehicle &Vehicle::operator=(const Vehicle &other)
{
    if (this != &other)
    {
        copy(other);
    }

    return *this;
}
void Vehicle::add_owner(Person &person)
{
    try
    {
        if (!owner)
        {
            get_all_vehicles(&person).push_back(*this);
            set_owner(&person);
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "This car already has an owner! Ownership failed!" << '\n';
    }
}

void Vehicle::release_owner()
{

    if (owner)
    {
        for (size_t i = 0; i < get_all_vehicles(owner).size(); i++)
        {
            if (get_all_vehicles(owner)[i] == *this)
            {
                swap(i, get_all_vehicles(owner).size() - 1, get_all_vehicles(owner));
                get_all_vehicles(owner).pop_back();
                break;
                //swap_owners(i, get_all_vehicles(owner).size(), get_all_vehicles(owner));
            }
        }
    }

    owner = nullptr;
}

void Vehicle::set_owner(Person *person)
{
    this->owner = person;
}

bool Vehicle::is_free() const
{
    return owner == nullptr;
}

bool Vehicle::operator==(const Vehicle &other) const
{
    return this->vehicle_id == other.vehicle_id;
}

void Vehicle::copy(const Vehicle &other)
{
    try
    {
        this->description = other.description;
        this->vehicle_id = other.vehicle_id;

        if (other.owner)
        {
            Person *buffer = new Person(*other.owner);
            delete this->owner;
            this->owner = buffer;
        }
        else
        {
            this->owner = nullptr;
        }
    }
    catch (...)
    {
        std::cerr << "Copying failed! Returning default values! " << '\n';
        clear();
    }
}

bool Vehicle::in_existing_vehicles(const Vehicle &v)
{

    if (count_of_existing_vehicles > 0)
    {
        try
        {
            for (size_t i = 0; i < count_of_existing_vehicles; i++)
            {

                if (v == existing_vehicles[i])
                {
                    throw std::invalid_argument("");
                }
            }
        }
        catch (std::invalid_argument)
        {
            std::cerr << "This vehicle already exists!!" << '\n';
            return true;
        }
    }

    return false;
}

void Vehicle::clear()
{
    this->description = "";
    this->owner = nullptr;
    this->vehicle_id.clear();
}

void Vehicle::print_vehicle(const Registration &other)
{
    for (size_t i = 0; i < count_of_existing_vehicles; i++)
    {
        if (existing_vehicles[i].vehicle_id == other)
        {
            if (!existing_vehicles[i].is_free())
            {
                std::cout << existing_vehicles[i].get_desc() << " : "
                          << existing_vehicles[i].get_owner()->get_name() << " "
                          << existing_vehicles[i].get_owner()->get_id() << " ";

                // Person::print_vehicles(*(existing_vehicles[i].get_owner()));
            }
            else
            {
                std::cout << existing_vehicles[i].get_desc() << "\n";
            }

            std::cout << "\n";
            return;
        }
    }

    std::cout << "Vehicle not found!\n";
}

void Vehicle::print_all_vehicles()
{
    for (size_t i = 0; i < count_of_existing_vehicles; i++)
    {
        std::cout << existing_vehicles[i].get_desc() << " " << existing_vehicles[i].get_id().get_registration() << "\n";
    }
    std::cout << "\n";
}

void Vehicle::remove_vehicle(const Registration &id)
{
    try
    {
        for (size_t i = 0; i < count_of_existing_vehicles; i++)
        {
            if (id == existing_vehicles[i].get_id())
            {
                if (!existing_vehicles[i].is_free())
                {
                    std::cout << "This vehicle has an owner. "
                              << "Are you sure about removing it?\n Yes : No\n";
                              
                    std::string yes_no;
                    std::getline(std::cin, yes_no);
                    yes_no = Validation::to_upper_all(yes_no);

                    if (yes_no == "YES")
                    {
                        existing_vehicles[i].release_owner();
                        std::cout << existing_vehicles[i].get_desc() << " " << existing_vehicles[i].get_id().get_registration() << " was removed!\n";
                        //swap_owners(i, count_of_existing_vehicles - 1, existing_vehicles);
                        swap(i, count_of_existing_vehicles - 1, existing_vehicles);

                        existing_vehicles.pop_back();

                        count_of_existing_vehicles--;
                    }
                    else if (yes_no != "YES" && yes_no != "NO")
                    {
                        std::cout << "Invalid answer! The vehicle remains in the database!\n";
                    }
                }
                else
                {
                    existing_vehicles[i].release_owner();
                    std::cout << existing_vehicles[i].get_desc() << " " << existing_vehicles[i].get_id().get_registration() << " was removed!\n";
                    // swap_owners(i, count_of_existing_vehicles - 1, existing_vehicles);
                    swap(i, count_of_existing_vehicles - 1, existing_vehicles);

                    existing_vehicles.pop_back();

                    count_of_existing_vehicles--;
                }

                return;
            }
        }

        throw std::invalid_argument("");
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Vehicle not found!" << '\n';
    }
}
