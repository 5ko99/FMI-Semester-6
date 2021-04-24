#include <iostream>
#include <cassert>

class MyString
{
private:
    char* data;
    size_t used;
    size_t allocated;

public:

    MyString()
    {
        data = nullptr;
        used = 0;
        allocated = 0;
    }

    MyString(const MyString& arr)
    {
        strcpy(this->data, arr.data);
        this->used = arr.used;
        this->allocated = arr.allocated;
    }

    MyString& operator=(const MyString& arr)
    {
        if (this != &arr)
        {
            strcpy(this->data, arr.data);
            this->used = arr.used;
            this->allocated = arr.allocated;
        }

        return *this;
    }

    ~MyString()
    {
        delete[] data;
        data = nullptr;
        used = 0;
        allocated = 0;
    }

    MyString(const char* str)
    {
        int sizeOfArray = strlen(str);

        char* tmp = new char[sizeOfArray];
        strncpy(tmp, str, sizeOfArray);

        this->data = tmp;
        this->allocated = sizeOfArray;
        this->used = 0;
    }

    char& at(std::size_t pos)
    {
        if (pos < used)
        {
            throw std::out_of_range("Pos cannot be less than 0");
        }
        return data[pos];
    }

    const char& at(std::size_t pos) const
    {
        assert(pos < used);
        return data[pos];
    }

    char& operator[](std::size_t pos)
    {
        return data[pos];
    }

    const char& operator[](std::size_t pos) const
    {
        return data[pos];
    }

    char& front()
    {
        return data[0];
    }

    const char& front() const
    {
        return data[0];
    }

    char& back()
    {
        return data[allocated - 1];
    }

    const char& back() const
    {
        return data[allocated - 1];
    }

    bool empty() const
    {
        if (data[0] == '\0')
        {
            return true;
        }
        return false;
    }

    std::size_t size() const
    {
        return allocated;
    }

    void clear()
    {
        data[0] = '\0';
    }

    void push_back(char c)
    {
        char* tmp = new char[allocated + 1];
        for (size_t i = 0; i < allocated; i++)
        {
            tmp[i] = data[i];
        }
        tmp[allocated] = c;

        delete[] data;
        this->data = tmp;
        this->allocated += 1;
    }

    void pop_back()
    {
        char* tmp = new char[allocated - 1];
        for (size_t i = 0; i < allocated - 1; i++)
        {
            tmp[i] = data[i];
        }

        delete[] data;
        this->data = tmp;
        this->allocated -= 1;
        
    }

    MyString& operator+=(char c)
    {
        char* tmp = new char[allocated + 1];
        for (size_t i = 0; i < allocated; i++)
        {
            tmp[i] = data[i];
        }
        tmp[allocated] = c;

        delete[] data;
        this->data = tmp;
        this->allocated += 1;

        return *this;
    }

    MyString& operator+=(const MyString& rhs)
    {
        int sizeOfArray = rhs.allocated;
        int totalSize = allocated + sizeOfArray;
        char* tmp = new char[totalSize];
        for (size_t i = 0; i < allocated; i++)
        {
            tmp[i] = data[i];
        }

        int j = 0;
        for (size_t i = allocated; i < totalSize; i++)
        {
            tmp[i] = rhs[j];
            ++j;
        }
        
        delete[] data;
        this->data = tmp;
        this->allocated += sizeOfArray;

        return *this;
    }

    MyString operator+(char c) const
    {
        MyString newStr(*this);
        newStr.push_back(c);
        return newStr;
    }
    
    MyString operator+(const MyString& rhs) const 
    {
        MyString newStr(*this);
        newStr += rhs;
        return newStr;
    }

    const char* c_str() const
    {
        char* str = new char[allocated + 1];
        for (size_t i = 0; i < allocated; i++)
        {
            str[i] = data[i];
        }
        str[allocated] = '\0';

        return str;
    }

    bool operator==(const MyString& rhs) const
    {
        int sizeOfArray = rhs.allocated;
        if (sizeOfArray != allocated)
        {
            return false;
        }

        for (size_t i = 0; i < sizeOfArray; i++)
        {
            if (data[i] != rhs.data[i])
            {
                return false;
            }
        }
    }

    bool operator<(const MyString& rhs) const
    {
        int sizeOfArray = rhs.allocated;
        int smallerSize = allocated < sizeOfArray ? allocated : sizeOfArray;

        for (size_t i = 0; i < smallerSize; i++)
        {
            if (data[i] > rhs[i])
            {
                return true;
            }
        }

        return false;
    }
};

class Vehicle
{
private:
    MyString regNumber;
    MyString carDescription;
    size_t numParkSpaces;

public:
    Vehicle(const char* registration, const char* description, std::size_t space)
        :regNumber(registration), carDescription(description), numParkSpaces(space)
    {
    }

    const char* registration() const
    {
        return regNumber.c_str();
    }

    const char* description() const
    {
        return carDescription.c_str();
    }

    std::size_t space() const
    {
        return numParkSpaces;
    }

    Vehicle(const Vehicle& newVehicle) 
    {
        regNumber = newVehicle.regNumber;
        numParkSpaces = newVehicle.numParkSpaces;
        carDescription = newVehicle.carDescription;
    }
    
    ~Vehicle() 
    {
        regNumber.clear();
        carDescription.clear();
        numParkSpaces = 0;
    }
};

class Garage
{
private:
    size_t capacity;
    Vehicle** vehicles;
 
public:

    Garage(size_t size)
    {
        this->capacity = size;
    }
};

int main()
{

}
