#include <cstring>
#include <cassert>
#include "MyString.h"

MyString::MyString()
{
    //set default values
    lenght = 0;

    try
    {
        string = new char[1];
        string[0] = '\0';
    }
    catch(const std::bad_alloc& err)
    {
        throw err;
    }
}

MyString::MyString(const char *str)
{
    //set lenght
    lenght = strlen(str);

    //allocate memory with lenght + 1 chars for terminating null
    try
    {
        string = new char[lenght + 1];

        //copy char*
        strcpy(string, str);
    }
    catch (const std::bad_alloc &err)
    {
        throw err;
    }
}

MyString::MyString(const MyString &other)
{
    //set lenght
    lenght = other.lenght;

    //allocate memory
    try
    {
        string = new char[lenght + 1];

        //copy char*
        strcpy(string, other.string);
    }
    catch (const std::bad_alloc &err)
    {
        throw err;
    }
}

char &MyString::at(std::size_t pos)
{
    //get char at position and throw error when out of range
    if (pos >= lenght)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return string[pos];
    }
}

const char &MyString::at(std::size_t pos) const
{
    //get char at position for constants and throw error when out of range
    if (pos >= lenght)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return string[pos];
    }
}

char &MyString::operator[](std::size_t pos)
{
    //get at position pos
    assert(pos < lenght);

    return string[pos];
}

const char &MyString::operator[](std::size_t pos) const
{
    //get at position pos for constant
    assert(pos < lenght);

    return string[pos];
}

char &MyString::front()
{
    //get first letter
    assert(string[0] != '\0');

    return string[0];
}

const char &MyString::front() const
{
    //get first letter for constant
    assert(string[0] != '\0');

    return string[0];
}

char &MyString::back()
{
    //get last letter
    assert(string[0] != '\0');

    return string[lenght - 1];
}

const char &MyString::back() const
{
    //get last letter for constant
    assert(string[0] != '\0');

    return string[lenght - 1];
}

bool MyString::empty() const
{
    //check if first letter is empty symbol
    return (string[0] == '\0');
}

std::size_t MyString::size() const
{
    //get size
    return lenght;
}

void MyString::clear()
{
    //set string to default values
    try
    {
        char* new_string = new char[1];
        new_string[0] = '\0';

        delete[] string;

        string = new_string;
        lenght = 0;
    }
    catch(const std::bad_alloc& err)
    {
        std::cout << "Error: " << err.what() << '\n';
    }
}

void MyString::push_back(char c)
{
    //create new dynamic char[]
    char *new_string = nullptr;
    try
    {
        new_string = new char[lenght + 2];
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << '\n';
        return;
    }

    //copy old char[] to new one, add symbol c and terminating symbol
    strcpy(new_string, string);
    new_string[lenght] = c;
    new_string[lenght + 1] = '\0';

    //delete old char[]
    delete[] string;

    //assign the new values
    string = new_string;
    lenght++;
}

void MyString::pop_back()
{
    //check if string is empty
    if (empty())
    {
        throw std::length_error("No letters to delete!");
    }

    //create new dynamic char[]
    char *new_string = nullptr;
    try
    {
        new_string = new char[lenght];
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << '\n';
        return;
    }

    //remove last symbol and copy to new one
    string[lenght - 1] = '\0';
    strcpy(new_string, string);

    //delete old char[]
    delete[] string;

    //assign the new values
    string = new_string;
    lenght--;
}

MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        //set lenght and copy string
        try
        {
            char *new_string = new char[other.lenght + 1];
            strcpy(new_string, other.string);

            delete[] this->string;

            this->string = new_string;
            this->lenght = other.lenght;
        }
        catch (const std::bad_alloc &err)
        {
            std::cout << "Error: " << err.what() << std::endl;
        }
    }

    return (*this);
}

MyString &MyString::operator+=(char c)
{
    //push back letter c
    push_back(c);

    return *this;
}

MyString &MyString::operator+=(MyString &rhs)
{
    try
    {
        //allocate memory
        char *new_string = new char[this->lenght + rhs.lenght + 1];

        //create concatenated string
        strcpy(new_string, this->string);
        strcat(new_string, rhs.string);
        new_string[this->lenght + rhs.lenght] = '\0';

        //delete old string
        delete[] this->string;

        //assign the new values
        this->string = new_string;
        this->lenght += rhs.lenght;
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << '\n';
    }

    return *this;
}

MyString MyString::operator+(char c) const
{
    //create new string and push c
    MyString new_string(*this);
    new_string.push_back(c);

    return new_string;
}

MyString MyString::operator+(const MyString &rhs) const
{
    try
    {
        //allocate memory
        char *new_string = new char[this->lenght + rhs.lenght + 1];

        //create concatenated string
        strcpy(new_string, this->string);
        strcat(new_string, rhs.string);
        new_string[this->lenght + rhs.lenght] = '\0';
        MyString concatenated(new_string);

        //delete old string
        delete[] new_string;

        return concatenated;
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << '\n';
        MyString empty;
        return empty;
    }
}

const char *MyString::c_str() const
{
    //return pointer to string
    return string;
}

bool MyString::operator==(const MyString &rhs) const
{
    //compare strings
    return (strcmp(string, rhs.string) == 0);
}

bool MyString::operator<(const MyString &rhs) const
{
    //compare strings
    return (strcmp(string, rhs.string) < 0);
}

MyString::~MyString()
{
    //delete dynamic array
    delete[] string;
}
