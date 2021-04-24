#include "VehicleVector.h"
#include <cstring>
#include <new>
VehicleVector::VehicleVector()
{
    arr = nullptr;
    m_size = 0;
    m_capacity = 0;
}
bool VehicleVector::push_back(Vehicle &v)
{
    for (int i = 0; i < m_size; ++i)
    {
        if (arr[i].m_registration == v.m_registration)
            return false;
    }
    if (m_size >= m_capacity)
    {
        if (m_capacity == 0)
            m_capacity = 1;
        else
            m_capacity *= 2;
        Vehicle *newarr = new (std::nothrow) Vehicle[m_capacity];
        if (newarr == nullptr)
        {
            return false;
        }
        for (int i = 0; i < m_size; ++i)
        {
            newarr[i] = arr[i];
        }
        delete[] arr;
        arr = newarr;
    }
    arr[m_size] = v;
    m_size++;
    return true;
}
Vehicle &VehicleVector::at(std::size_t pos) const
{
    return arr[pos];
}
std::size_t VehicleVector::erase(const char *registration)
{
    for (int i = 0; i < m_size; ++i)
    {
        const char *curRegistration = at(i).registration();
        if (strcmp(curRegistration, registration) == 0)
        {
            std::size_t curSpace = at(i).space();
            if (i != m_size - 1)
            {
                arr[i] = arr[m_size - 1];
            }
            m_size--;
            return curSpace;
        }
        delete[] curRegistration;
    }
    return -1;
}
void VehicleVector::clear()
{
    delete[] arr;
    arr = nullptr;
    m_size = 0;
    m_capacity = 0;
}
std::size_t VehicleVector::size() const
{
    return m_size;
}
VehicleVector &VehicleVector::operator=(const VehicleVector &other)
{
    if (this != &other)
    {
        delete[] arr;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        arr = new Vehicle[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}
VehicleVector::~VehicleVector()
{
    clear();
}