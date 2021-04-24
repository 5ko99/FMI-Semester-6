#define _CRT_SECURE_NO_WARNINGS // visual studio-specific

#include <iostream>
#include <cctype>
#include <string>
#include <cassert>
#include <cstring>

class Registration
{
    char reg[9];

private:
    bool isValid(const char *str)
    {
        size_t len = strlen(str);

        return len >= 7 &&
               len <= 8 &&
               isalpha(str[len - 1]) &&
               isalpha(str[len - 2]) &&
               isdigit(str[len - 3]) &&
               isdigit(str[len - 4]) &&
               isdigit(str[len - 5]) &&
               isdigit(str[len - 6]) &&
               isalpha(str[len - 7]) &&
               (len == 7 || isalpha(str[len - 8]));
    }

public:
    Registration(const char *str)
    {
        if (!isValid(str))
            throw std::exception();
        strcpy(reg, str);
    }

    Registration &operator=(const char *str)
    {
        if (!isValid(str))
            throw std::exception();
        strcpy(reg, str);
    }

    bool operator==(const char *str) const
    {
        return strcmp(reg, str) == 0;
    }

    const char *toString() const
    {
        return reg;
    }
};

class Vehicle
{
public:
    const Registration regnum;
    const std::string description;

    Vehicle(const char *regnum, const char *description)
        : regnum(regnum), description(description)
    {
    }
};

class VehicleList
{
    Vehicle **vehicles = nullptr;
    size_t allocated = 0;
    size_t used = 0;

private:
    Vehicle **clone(Vehicle **vehicles, size_t size, size_t used)
    {
        assert(used < size);

        Vehicle **copy = new Vehicle *[size];

        for (size_t i = 0; i < used; ++i)
            copy[i] = new Vehicle(*vehicles[i]);

        return copy;
    }

public:
    VehicleList(std::size_t capacity)
        : allocated(capacity)
    {
        vehicles = new Vehicle *[capacity];
    }

    VehicleList(const VehicleList &other)
    {
        vehicles = clone(other.vehicles, other.allocated, other.used);
        allocated = other.allocated;
        used = other.used;
    }

    ~VehicleList()
    {
        for (size_t i = 0; i < used; ++i)
            delete vehicles[i];

        delete[] vehicles;
    }

    VehicleList &operator=(const VehicleList &other)
    {
        if (this != &other)
        {
            Vehicle **copy = clone(other.vehicles, other.allocated, other.used);
            delete[] vehicles;
            vehicles = copy;
            allocated = other.allocated;
            used = other.used;
        }

        return *this;
    }

    void insert(const char *regnum, const char *description)
    {
        if (used >= allocated)
            throw std::exception();

        if (find(regnum))
            throw std::exception();

        vehicles[used] = new Vehicle(regnum, description);
        ++used;
    }

    const Vehicle &at(size_t index) const
    {
        if (index >= used)
            throw std::out_of_range("no such vehicle");
        return *vehicles[index];
    }

    const Vehicle &Fst(size_t index) const
    {
        assert(index < used);
        return *vehicles[index];
    }

    bool empty() const
    {
        return used == 0;
    }

    std::size_t capacity() const
    {
        return allocated;
    }

    std::size_t size() const
    {
        return used;
    }

    const Vehicle *find(const char *regnum) const
    {
        for (size_t i = 0; i < used; ++i)
            if (vehicles[i]->regnum == regnum)
                return vehicles[i];

        return nullptr;
    }
};

int main()
{
    size_t size;
    std::cout << "Enter list size: ";
    std::cin >> size;
    std::cin.ignore(); // flush the new line

    VehicleList vl(size);

    for (size_t i = 0; i < size; ++i)
    {
        char regnum[9];
        char description[100];

        std::cout << "\nEnter the data for vehicle " << i << ":\n";

        std::cout << "  registration: ";
        std::cin.getline(regnum, 9);
        std::cout << "  description: ";
        std::cin.getline(description, 100);

        try
        {
            vl.insert(regnum, description);
        }
        catch (...)
        {
            std::cout << "You entered invalid data! Try again.\n";
            --i;
        }
    }

    std::cout << "\nThe list is created and contains " << vl.size() << " vehicle(s)\n";

    char regnum[9];
    std::cout << "\nEnter a registration number to search for:";
    std::cin.getline(regnum, 9);

    std::cout << (vl.find(regnum) ? "Vehicle exists\n" : "Vehicle DOES NOT exist\n");
    return 0;
}