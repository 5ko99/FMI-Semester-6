#ifndef  GARAGE_H
#define  GARAGE_H
#include "Vehicle.h"
#include "MyString.h"


class Garage
{
public:
    Garage(std::size_t size);
    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(std::size_t pos) const;
    const Vehicle& operator[](std::size_t pos) const;
    bool empty() const ;
    std::size_t size() const;
    void clear() ;
    const Vehicle* find(const char* registration) const;
    ~Garage();
private:
    std::size_t capacity;
    Vehicle** vehicles;
    std::size_t vehiclescount;
};

#endif // GARAGE_H
