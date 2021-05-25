// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Мария Маркова
// ФН: 82012
// Специалност: КН
// Курс: 2
// Административна група: 2
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang>
// MinGW
// IDE : VS Code

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <cstdlib>

// Ще съм много благодарна, ако получа обратна връзка с коментар кое не е ок :)

class IntBuffer
{
private:
    int* data;
    std::size_t capacity = 0;
    std::size_t used = 0;

public:
    IntBuffer() = delete;
    IntBuffer(std::size_t size);
    IntBuffer(const IntBuffer& other);
    IntBuffer& operator =(const IntBuffer& other);
    
    IntBuffer(std::size_t size, const IntBuffer& other);
    int& at(std::size_t index);
    const int& at(std::size_t index) const;
    int& operator[](std::size_t index);
    const int& operator[](std::size_t index) const;
    std::size_t size() const;
    void copy_from(const IntBuffer& other, std::size_t count);
    bool operator==(const IntBuffer& other) const;
    bool operator<(const IntBuffer& other) const;
};


IntBuffer::IntBuffer(std::size_t size)
{
    data = new int[size];
    
    
    capacity = size;
    used = 0;
}

IntBuffer::IntBuffer(const IntBuffer& other)
{
    data = new int[other.capacity];
    for(std::size_t i = 0; i < other.used; ++i)
    {
        data[i] = other.data[i];
    }
    capacity = other.capacity;
    used = other.used;
}

IntBuffer& IntBuffer::operator =(const IntBuffer& other)
{
    if (this != &other)
    {
        int* buffer = new int[other.capacity];
        for (std::size_t i = 0; i < other.used; ++i)
        {
            buffer[i] = other.data[i];
        }

        delete data;
        data = buffer;

        used = other.used;
        capacity = other.capacity;
    }
    return *this;
}

IntBuffer::IntBuffer(std::size_t size, const IntBuffer& other)
{
    data = new int[size];
    int min = size > other.used? other.used : size;

    for(std::size_t i = 0; i < min; ++i)
    {
        data[i] = other.data[i];
    }

    capacity = size;
    used = min;
}

int& IntBuffer::at(std::size_t index)
{
    if (index >= capacity) 
        throw std::out_of_range("Too big index!");
    
    return data[index];
}

const int& IntBuffer::at(std::size_t index) const
{
    if (index >= capacity) 
        throw std::out_of_range("Too big index!");
    
    return data[index];
}

int& IntBuffer::operator[](std::size_t index)
{
    #ifdef DEBUG
    assert(index < used);
    #endif

    return data[index];
}

const int& IntBuffer::operator[](std::size_t index) const
{
    #ifdef DEBUG
    assert(index < used);
    #endif

    return data[index];
}

std::size_t IntBuffer::size() const
{
    return capacity;
}

void IntBuffer::copy_from(const IntBuffer& other, std::size_t count)
{
    if(capacity < count || other.capacity < count)
        throw std::out_of_range("Count is too big!");

    for (std::size_t i = 0; i < count; ++i)
    {
        data[i] = other.data[i];
    }
    // we dont change the capacity/used elements, we just change some values
}

bool IntBuffer::operator==(const IntBuffer& other) const
{
    if (capacity != other.capacity || used != other.used)
        return false;

    for(std::size_t i = 0; i < used; ++i)
    {
        if(data[i] != other.data[i])
            return false;
    }
    return true;
}

bool IntBuffer::operator<(const IntBuffer& other) const
{
    for(std::size_t i = 0; i < used; ++i)
    {
        if(data[i] >= other.data[i])
            return false;
    }
    return true;
}

class Set
{
    IntBuffer* elements;
    std::size_t capacity = 0;
    std::size_t used = 0;

public:
    Set();
    void insert(int value);
    bool contains(int value) const;
    std::size_t size() const;
};

Set::Set() : elements(nullptr)
{
    IntBuffer temp(2);
    elements = &temp;
    used = 0;
    capacity = 2;
}

void Set::insert(int value)
{
    //std::cout << contains(value);
    if(contains(value))
        return;

    //int s = elements->size();
   // std::cout << "S " << s << '\n';
    IntBuffer buffer(capacity * 2);
    //std::cout << this->size() << '\n';
   // std::cout << buffer.size() << '\n';

    if(used + 1 >= elements->size()) // gives strong ex. guarantee
    {

        for(std::size_t i = 0; i < used; ++i)
        {
            buffer[i] = elements->at(i);
            //std::cout << buffer[i] << " ";
        }

        delete elements;
        elements = &buffer;
        capacity *= 2;
    }
    
    used++;
    elements->at(used - 1) = value;
    //std::cout << elements->at(used - 1);

    for(std::size_t i = 0; i < used - 1; ++i)
    {
        int minInd = i;
        for(std::size_t j = i + 1; j < used; ++j)
        {
            if(elements->at(i) > elements->at(j))
                minInd = j;
        }

        if(minInd != i)
        {
            int temp = elements->at(minInd);
            elements->at(minInd) = elements->at(i);
            elements->at(i) = temp;
        }
    }
}

bool Set::contains(int value) const
{
    int left = 0;
    int right = used - 1;
    int mid = (left + right) / 2;

    // 1 2 3 4
    while(left <= right)
    {
        mid = (left + right) / 2;

        if (elements->at(mid) == value)
            return true;

        if (elements->at(mid) < value)
        {
            left = mid + 1;
        }

        if (elements->at(mid) > value)
        {
            right = mid - 1;
        }
    }
    return false;
}

std::size_t Set::size() const
{
    return used;
}

int main()
{
    IntBuffer a(3);
    a[0] = 0;
    a[1] = 123;
    a[2] = 2;
    std::cout << a.size() << std::endl;
    std::cout << a[1] << std::endl;

    Set b;
    std::cout << b.size() << std::endl;

    b.insert(4);
    b.insert(1);
    
    

	return 0;
}