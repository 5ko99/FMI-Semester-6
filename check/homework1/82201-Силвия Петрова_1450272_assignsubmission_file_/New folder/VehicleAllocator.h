#pragma once
#include "Vehicle.h"

class VehicleAllocator
{

public:
    // Създава празен алокатор
    VehicleAllocator();

    // Унищожава алокатора и освобождава заделените от него обекти
    // (т.е. трябва да се пази информация за всички
    // създадени до момента обекти)
    ~VehicleAllocator();

    // Създава нов Vehicle Обект, като го съхранява в контейнера
    // и връща указател към него. Според нуждите ви, може да
    // връща и константен указател
    Vehicle allocate(const char *registration, const char *description, std::size_t space);

    Vehicle back();

private:
    // Тук трябва да има подходящи членове, които позволяват да пазите
    // всички създадени Vehicle обекти.
    Vehicle **vehicle = nullptr;
    size_t numVehicles = 0;
    size_t allocatedCapacity = 0;

    void expand();
};