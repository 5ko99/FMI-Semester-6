#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

class Vehicle
{
private:
    Registration* registration;
    std::string description;
    std::vector<std::reference_wrapper<const Person>> owner;

public:
    Vehicle();

    Vehicle(Registration* reg, const std::string descript);

    Vehicle(const Vehicle& vehicle);

    Vehicle& operator=(const Vehicle& source);

    void addOwner(Person& person);

    const std::string getRegistration() const;

    const std::string getDescription() const;

    void releaseOwner(Person &person);

    bool hasOwner();

    const unsigned int getOwnerId();

    friend std::ostream& operator<<(std::ostream &out, const Vehicle &vehicle);

    ~Vehicle();
};

#endif // VEHICLE_H_INCLUDED
