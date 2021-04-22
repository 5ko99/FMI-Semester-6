#include "myString.hpp"
#include <exception>
#include <iostream>
#include <cassert>
#include<new>

const char nullChar = '\0';

//helper functions
char* allocateDinamycArray(std::size_t size)
{
    char *array = nullptr;

    try
    {
        array = new char[size];
    }
    catch (const std::bad_alloc& e) 
    {
        std::cout << "Allocation failed: " << e.what() << '\n';
        return nullptr;
    }
    
    return array;
}

size_t strlen(const char* string)
{
    if (string == nullptr)
    {
        return 0;
    }

    size_t lenght = 0;
    while (string[lenght])
    {
        ++lenght;
    }  
    
    return lenght;
}

void stringCopy(char* destination, const char* source)
{
    int possition = 0;
    while(source[possition]) 
    {
        destination[possition] = source[possition];
        ++possition;
    }
    destination[possition] = '\0';
}

//constructor functionality
MyString::MyString()
{
    string = nullptr;
    lenght = 0;
}

MyString::MyString(const char *string)
{
    size_t stringLenght = strlen(string) + 1;
    this->string = allocateDinamycArray(stringLenght);

    if (this->string != nullptr)
    {
        stringCopy(this->string, string);
        lenght = stringLenght - 1;
    }
    else
    {
        lenght = 0;
    }
}

//destructor functionality
MyString::~MyString()
{
    delete[] string;
}

//assigment operator functionality
MyString& MyString::operator=(const MyString &source)
{
    if (source.string == nullptr)
    {
        string = source.string;

        if (string != nullptr)
        {
            delete[] string;
        }
        
        lenght = 0;
    }
    else
    {
        char *result = allocateDinamycArray(source.lenght+1);

        if(result != nullptr)
        {
            stringCopy(result, source.string);

            delete[] string;

            string = result;
            lenght = source.lenght;
        }
    }

    return *this;
}

//concatenate operators functionality-
MyString MyString::operator+(char c) const
{
    MyString result;
    size_t resultLenght = lenght + 2;

    result.string = allocateDinamycArray(resultLenght);

    if(result.string != nullptr)
    {
        if(string != nullptr)
        {
            stringCopy(result.string, string);
        }
        
        result.string[lenght] = c;
        result.string[lenght + 1] = nullChar;

        result.lenght = resultLenght - 1;
    }
    else
    {
        result = *this;
    }

    return result;
}

MyString MyString::operator+(const MyString &rhs) const
{
    MyString result;

    size_t resultLenght = size() + rhs.size() + 1;

    result.string= allocateDinamycArray(resultLenght);

    if (result.string != nullptr && rhs.string != nullptr)
    {
        if(string != nullptr)
        {
            stringCopy(result.string, string);
        }
        
        for(int counter = size(); counter < resultLenght - 1; ++counter)
        {
            result.string[counter] = rhs.string[counter - this->size()];
        }

        result.string[resultLenght - 1] = nullChar;
        result.lenght = resultLenght - 1;
    }
    else
    {
        result = *this;
    }

    return result;

}

MyString& MyString::operator+=(char c)
{
    size_t resultLenght = size() + 2;
    char *result = allocateDinamycArray(resultLenght);

    if (result != nullptr)
    {
        if (string != nullptr)
        {
            stringCopy(result, string);
        }
        
        result[size()] = c;
        result[size() + 1] = nullChar;

        if (string != nullptr)
        {
            delete[] string;
        }
         
        string = result;
        lenght = resultLenght - 1;
    }
    
    return *this;
}

MyString& MyString::operator+=(const MyString &rhs)
{
    if (rhs.string != nullptr)
    {
        const size_t resultLenght = size() + rhs.size() +1;
        char *result = allocateDinamycArray(resultLenght);

        if (result != nullptr)
        {      
            if (string != nullptr)
            {
                stringCopy(result, string);
            }
            
            for (int counter = size(); counter < resultLenght; ++counter)
            {
                result[counter] = rhs[counter - size()];
            }

            result[resultLenght] = nullChar;

            if (string != nullptr)
            {
                delete[] string;
            }
            
            string = result;
            lenght = resultLenght-1;
        }
    }

    return *this;
}

//accessing element functionality
char& MyString::at(std::size_t position)
{
    
    if (position > lenght+1 || position < 1)
    {
        throw std::out_of_range("the index is incorrect");
    }
    else
    {
        return string[position-1];
    }  
}

const char& MyString::at(std::size_t position) const
{
    if (position > lenght+1 || position < 1)
    {
        throw std::out_of_range("the index is incorrect");
    }
    else
    {
        return string[position-1];
    }  
}

//accessing element operator functionality
char& MyString::operator[](std::size_t position)
{
    assert((position <= lenght && position >= 0) && "the position isn't range");

    return string[position];
}

const char& MyString::operator[](std::size_t position) const
{
    assert((position <= lenght && position >= 0) && "the position is in range");

    return string[position];
}

//identity operator functionality
bool MyString::operator==(const MyString &rhs) const
{
    if(lenght != rhs.lenght)
    {
        return false;
    }
    else
    {
        for (int counter = 0; counter < size(); ++counter)
        {
            if (string[counter] != rhs[counter])
            {
                return false;
            }
            
        }

        return true;
    }
}

//access first element
char& MyString::front()
{
    assert(lenght > 0 && "the string is not empty");

    return string[0];
}

const char& MyString::front() const
{
    assert(lenght > 0 && "the string is not empty");

    return string[0];
}

//access last element
char& MyString::back()
{
    assert(lenght > 0 && "the string is not empty");

    return string[lenght - 1];
}

const char& MyString::back() const
{
    assert(lenght > 0 && "the string is not empty");

    return string[lenght - 1];
}

//check if string is empty
bool MyString::empty() const
{
    if(lenght == 0)
    {
        return true;
    }

    return false;
}

//retrun string lenght
std::size_t MyString::size() const
{
    return lenght;
}

//clear string
void MyString::clear()
{
    delete[] string;

    string = nullptr;
    lenght = 0;
}

//remove last element
void MyString::pop_back()
{
    assert(lenght > 1 && "the string is empty");

    size_t resultSize = size() - 1;
    if (resultSize < 0)
    {
        resultSize = 0;
    }

    char *result = allocateDinamycArray(resultSize);

    if (result != nullptr)
    {   
        string[size()-1] = nullChar;   
        stringCopy(result, this->string);
        delete[] string;
        string = result;
        lenght = resultSize;
    }

}

//add char at last index
void MyString::push_back(char c)
{
    size_t resultLenght = size() + 2;
    char *result = allocateDinamycArray(resultLenght);

    if(result != nullptr)
    {
        if(string != nullptr)
        {
            stringCopy(result, string);
        }
        
        result[size()] = c;
        result[size() + 1] = nullChar;

        if (string != nullptr)
        {
            delete[] string;
        }
        
        string = result;
        lenght = resultLenght -1;
    }
}

//return pointer to string in new array
const char* MyString::c_str() const
{
    return string;
}