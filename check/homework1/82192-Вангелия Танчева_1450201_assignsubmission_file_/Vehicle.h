#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

class Vehicle
{

private:
    MyString car_licence_plate;
    MyString car_description;
    size_t car_park_space;

public:
    ///Constructor with arguments
    Vehicle(const char* registration, const char* description,
        size_t space);

    //~Vehicle();

    const char* registration() const;

    const char* description() const;

    size_t space() const;
};

#endif // VEHICLE_H_INCLUDED
