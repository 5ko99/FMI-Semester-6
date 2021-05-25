
// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Цанко Ангелов
// ФН:82084
// Специалност:Компютърни науки
// Курс:2
// Административна група:4
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class IntBuffer
{
    private:
    int *array;
    int temp_size;
    int capacity;

    void copy(const IntBuffer &other)
    {
        temp_size = other.temp_size;
        capacity = other.capacity;
        int *array = new int[capacity];
        for (int i = 0; i < capacity; i++)
        {
            array[i] = other.array[i];
        }
    }
    void clean()
    {
        delete[] array;
    }

    public:
    IntBuffer(const IntBuffer &other)
    {
        copy(other);
    }

    IntBuffer &operator=(const IntBuffer &other)
    {
        if (this != &other)
        {
            clean();
            copy(other);
        }

        return *this;
    }

    ~IntBuffer()
    {
        clean();
    }

    IntBuffer(std::size_t size)
    {
        int *array = new int[size];
    }

    IntBuffer(std::size_t size, const IntBuffer& other)
    {
        int *array = new int[size];
        for (int i = 0; i < size; i++)
        {
            array[i] = other.array[i];
        }
    }

    int& at(std::size_t index)
    {
        if (index > temp_size)
        {
            throw std::out_of_range("Invalid index!");
        }
        return array[index];
    }

    const int& at(std::size_t index) const
    {
        if (index > temp_size)
        {
            throw std::out_of_range("Invalid index!");
        }
        return array[index];
    }

    int& operator[](std::size_t index)
    {
        #ifdef _DEBUG
        assert(index < temp_size);
        #endif

        return array[index];
    }

    const int& operator[](std::size_t index) const
    {
        #ifdef _DEBUG
        assert(index < temp_size);
        #endif

        return array[index];
    }

    std::size_t size() const
    {
        return this->temp_size;
    }

    void copy_from(const IntBuffer& other, std::size_t count)
    {
        if (capacity < count || other.capacity < count)
        {
            throw std::out_of_range("Out of range");
        }

        for (int i = 0; i < count; i++)
        {
            array[i] = other.array[i];
        }
    }

    bool operator==(const IntBuffer& other) const
    {
        if (temp_size != other.temp_size)
        {
            return false;
        }

        for (int i = 0; i < temp_size; i++)
        {
            if (array[i] != other.array[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator<(const IntBuffer& other) const
    {
        int temp;

        if (temp_size > other.temp_size)
        {
            temp = other.temp_size;
        }
        else
        {
            temp = temp_size;
        }
        
        for (int i = 0; i < temp; i++)
        {
            if (array[i] == other.array[i])
            {
                continue;
            }

            if (array[i] > other.array[i])
            {
                return other.array < array;
            }

            if (array[i] < other.array[i])
            {
                return array < other.array;
            }

        }

        return false;
    }

    void sort()
    {
        for (int i = 0; i < temp_size - 1; i++)
        {
            for (int j = 1; j < temp_size; j++)
            {
                if (array[i] > array[j])
                {
                    int temp;
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    void setCapacity(int _capacity)
    {
        capacity = _capacity;
    }

    int getCapacity() const
    {
        return this->capacity;
    }

    void setTemp_size(int _temp_size)
    {
        temp_size = _temp_size;
    }

    int getTemp_size() const
    {
        return this->temp_size;
    }

};

class Set 
{
    private:
    IntBuffer elements;

    public:
    Set() = default;
    

    void insert(int value)
    {
        if (elements.getTemp_size() >= elements.getCapacity())
        {
            IntBuffer new_elements(2*(elements.getCapacity()));
            for (int i = 0; i < elements.getCapacity(); i++)
            {
                new_elements[i] = elements[i];
            }
            
            elements = new_elements;
        }

        int temp_size_elements = elements.getTemp_size();
        elements[temp_size_elements + 1] = value;
    }

    std::size_t size() const
    {
        return this->elements.getTemp_size();
    }

};



int main()
{
    
	return 0;
}