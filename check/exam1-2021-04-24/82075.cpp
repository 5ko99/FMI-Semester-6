//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Верони Костадинов
// ФН: 82075
// Специалност: КН
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 23.04.2021г.
// Начален час на контролното: <9:30>
// Кой компилатор използвате: <GCC>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

class IntBuffer
{
private:
    int *array;
    std::size_t length;

public:
    void copyAndCreate(const std::size_t el)
    {
        array = nullptr;
        int *newArray = new int[el + 1];
        this->array = newArray;
        length = el;
        delete[] newArray;
    }

    IntBuffer(std::size_t size)
    {
        int *newArray = new int[size + 1];
    }

    std::size_t size() const
    {
        return length;
    }

    void copy(const IntBuffer &arr)
    {
        int *tempArray = new int[arr.size()];
        this->array = tempArray;
        length = arr.size();
    }

    void clear()
    {
        if (array)
        {
            delete[] array;
        }
        length = 0;
    }

    ~IntBuffer()
    {
        clear();
    }

    IntBuffer(std::size_t size, const IntBuffer &other)
    {
        int *newArray = new int[size + 1];
        std::size_t n = 0;
        if (size <= other.size())
        {
            n = size;
            for (std::size_t j = 0; j <= n; j++)
            {
                newArray[j] = other.array[j];
            }
        }
        else if (size > other.size())
        {
            n = other.size();
            for (std::size_t j = 0; j < n; j++)
            {
                newArray[j] = other.array[j];
            }
        }
        else
        {
            throw std::out_of_range("Couldn't allocate memory");
        }
    }

    int &at(std::size_t index)
    {
        if (index < length)
        {
            return array[index];
        }
        else
        {
            throw std::out_of_range("Invalid index");
        }
    }

    const int &at(std::size_t index) const
    {
        if (index < length)
        {
            return array[index];
        }
        else
        {
            throw std::out_of_range("Invalid index ( constant func ) ");
        }
    }

    int &operator[](std::size_t index)
    {
        assert(index <= length && "bad position");
        return array[index];
    }

    const int &operator[](std::size_t index) const
    {
        assert(index <= length && "bad position");
        return array[index];
    }

    void copy_from(const IntBuffer &other, std::size_t count)
    {
        if (length < count || other.length < count)
        {
            throw std::out_of_range("invalid");
        }
        else
        {
            for (std::size_t i = 0; i <= count; i++)
            {
                this->array[i] = other.array[i];
            }
        }
    }

    bool operator==(const IntBuffer &other) const
    {
        int temp = 0;
        int temp2 = 0;
        if (other.length == length)
        {
            temp = 1;
        }
        else
        {
            temp = 0;
        }
        if (temp == 1)
        {
            for (std::size_t i = 0; i < length; i++)
            {
                if (other[i] == array[i])
                {
                    temp2 = 1;
                }
                else
                {
                    temp2 = 0;
                }
            }
        }

        if (temp == 1 && temp2 == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Set
{
private:
    int *numbers;        // temporary array to store non sorted numbers
    IntBuffer *elements; // sorted numbers
    std::size_t num_length;

public:
    Set()
    {
        int *tempSet = new int[0];
        tempSet = nullptr;
        elements = nullptr;
        numbers = nullptr;
    }

    void sort()
    {
        for (std::size_t i = 0; i < num_length; i++)
        {
            for (std::size_t j = 1; j <= num_length; j++)
            {
                if (numbers[i] > numbers[j])
                {
                    int temp = numbers[i];
                    numbers[i] = numbers[j];
                    numbers[j] = temp; //проверяваме и за случай че са равни или се повтарят и после запазваме сортираното множество в elements
                }                      // за жалост не ми остана време да го допиша
            }
        }
    }

    //void insert - compares value to every element of elements and puts it into place

    std::size_t size() const
    {
        return num_length;
    }
};

int main()
{
    std::cout << "test";

    return 0;
}