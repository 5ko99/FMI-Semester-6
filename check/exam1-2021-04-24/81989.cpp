
//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Данаил Владимиров Маджаров
// ФН: 81989
// Специалност: КН
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>

class IntBuffer
{
    int *array;

public:
    IntBuffer() = delete;
    IntBuffer(std::size_t size)
    {
        array = new int[size];
    }

    IntBuffer(std::size_t size, const IntBuffer &other)
    {
        try
        {
            array = new int[size];
            int lower;
            if (size <= sizeof(other.array) / 4)
            {
                lower = size;
            }
            else
            {
                lower = sizeof(other.array) / 4;
            }

            for (int i = 0; i < lower; i++)
            {
                array[i] = other.array[i];
            }
        }
        catch (std::runtime_error e)
        {
            throw new std::bad_alloc();
        }
    }

    int &at(std::size_t index)
    {
        if (index > sizeof(array) / 4)
        {
            throw new std::out_of_range("Index is out of range");
        }

        return array[index];
    }

    const int &at(std::size_t index) const
    {
        const int result = at(index);
        return result;
    }

    int &operator[](std::size_t index)
    {
        assert(index < sizeof(array) / 4);
        return array[index];
    }

    const int &operator[](std::size_t index) const
    {
        assert(index < sizeof(array) / 4);
        const int result = array[index];
        return result;
    }

    std::size_t size() const
    {
        return sizeof(array) / 4;
    }

    void copy_from(const IntBuffer &other, std::size_t count)
    {
        if (this->size() < count || other.size() < count)
        {
            throw new std::out_of_range("Invalid count!");
        }

        for (int i = 0; i < count; i++)
        {
            this->array[i] = other.array[i];
        }
    }

    bool operator==(const IntBuffer &other) const
    {
        if (this->size() != other.size())
        {
            return false;
        }

        for (int i = 0; i < this->size(); i++)
        {
            if (this->array[i] != other.array[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator<(const IntBuffer &other) const
    {
        int lower;
        if (this->size() <= other.size())
        {
            lower = this->size();
        }
        else
        {
            lower = other.size();
        }

        for (int i = 0; i < lower; i++)
        {
            if (this->array[i] < other.array[i])
            {
                return true;
            }
            else if (this->array[i] == other.array[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }

    int *getArray()
    {
        return array;
    }

    ~IntBuffer()
    {
        delete[] array;
    }
};

class Set
{
    IntBuffer *elements;
    std::size_t used = 0;

public:
    Set()
    {
        elements = new IntBuffer(2);
    }

    void insert(int value)
    {
        for (int i = 0; i < elements->size(); i++)
        {
            if (value == elements->at(i))
            {
                throw new std::invalid_argument("Value already exists");
            }
        }

        for (int i = 0; i < elements->size(); i++)
        {
            if (used == 0)
            {
                elements->getArray()[used] = value;
                used++;
                return;
            }
            else if (used == elements->size() - 1)
            {
                IntBuffer saver(elements->size(), *elements);
                elements = new IntBuffer(elements->size() * 2, saver);
                for (int i = 0; i < saver.size(); i++)
                {
                    elements->at(i) = saver.at(i);
                }

                elements->at(used) = value;
                used++;
            }
        }

        for (int i = 0; i < elements->size() - 1; i++)
        {
            for (int j = i + 1; i < elements->size(); i++)
            {
                if (elements->at(i) > elements->at(j))
                {
                    int saved = elements->at(i);
                    elements->at(i) = elements->at(j);
                    elements->at(i) = saved;
                }
            }
        }
    }

    bool contains(int value) const
    {
        for (int i = 0; i <= used; i++)
        {
            if (elements->at(i) == value)
            {
                return true;
            }
        }

        return false;
    }

    std::size_t size() const
    {
        return used + 1;
    }
};

int main()
{
    size_t N;
    int input;

    do
    {
        std::cout << "Enter a positive N: " << std::endl;
        std::cin >> input;
    } while (input < 1);
    N = input;

    Set generated;
    for (int i = 0; i < N; i++)
    {
        generated.insert(std::rand());
    }
    
    return 0;
}