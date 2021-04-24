#include "MyString.h"

void String::copy(const String &other)
{
    this->length = other.length;
    this->memSize = other.memSize;
    this->characters = new char[this->memSize];
    for (std::size_t i = 0; i < this->length; i++)
    {
        characters[i] = other.characters[i];
    }
}

void String::erase()
{
    delete[] characters;
}

void String::checkLenght()
{
    if (this->length >= this->memSize)
    {
        char *temp = new char[memSize];
        for (std::size_t i = 0; i < length; i++)
        {
            temp[i] = this->characters[i];
        }
        this->erase();
        this->memSize = this->memSize * 2;
        this->characters = new char[this->memSize];
        for (std::size_t i = 0; i < length; i++)
        {
            characters[i] = temp[i];
        }
        delete[] temp;
    }
}

String::String()
{
    this->characters = nullptr;
    this->length = 0;
    this->memSize = 0;
}

String::String(const String &other)
{
    this->copy(other);
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        this->erase();
        this->copy(other);
    }
    return *this;
}

String::String(const char *chars)
{
    this->length = 0;
    for (std::size_t i = 0; chars[i] != '\0'; i++)
        this->length++;
    this->memSize = length + 10;
    this->characters = new char[memSize];
    for (std::size_t i = 0; i < length; i++)
        this->characters[i] = chars[i];
}

String::~String()
{
    this->erase();
}

char &String::at(std::size_t pos)
{
    if (pos < 0 || pos >= this->length)
    {
        throw std::out_of_range("Given position of character is out of bounds!");
    }
    return this->characters[pos];
}

const char &String::at(std::size_t pos) const
{
    if (pos < 0 || pos >= this->length)
    {
        throw std::out_of_range("Given position of character is out of bounds!");
    }
    return this->characters[pos];
}

char &String::operator[](std::size_t pos)
{
   // assert(pos < 0 || pos >= this->length);
    return characters[pos];
}

const char &String::operator[](std::size_t pos) const
{
   // assert(pos < 0 || pos >= this->length);
    return characters[pos];
}

char &String::front()
{
   // assert(length == 0);
    return characters[0];
}

const char &String::front() const
{
   // assert(length == 0);
    return characters[0];
}

char &String::back()
{
   // assert(length == 0);
    return characters[length - 1];
}

const char &String::back() const
{
   // assert(length == 0);
    return characters[length - 1];
}

bool String::empty() const
{
    if (length == 0)
        return true;
    return false;
}

std::size_t String::size() const
{
    return this->length;
}

void String::clear()
{
    this->erase();
    this->characters = new char[memSize];
    this->length = 0;
}

void String::push_back(char c)
{
    this->checkLenght();
    this->characters[length] = c;
    length++;
}

void String::pop_back()
{
    //assert(length == 0);
    this->characters[length - 1] = '\0';
    length--;
}

String &String::operator+=(char c)
{
    checkLenght();
    characters[this->length] = c;
    this->length++;
    return *this;
}

String &String::operator+=(const String &other)
{
    char *temp = new char[this->memSize];
    for (std::size_t i = 0; i < this->length; i++)
    {
        temp[i] = this->characters[i];
    }

    this->erase();
    this->memSize = this->memSize + other.memSize;
    this->characters = new char[this->memSize];

    for (std::size_t i = 0; i < this->length; i++)
    {
        characters[i] = temp[i];
    }
    delete[] temp;

    for (std::size_t i = 0; i < other.length; i++)
    {
        characters[this->length + i] = other.characters[i];
    }
    this->length = this->length + other.length;

    return *this;
}

String String::operator+(char c) const
{
    String newString;
    newString.characters = new char[this->memSize + 2];
    newString.memSize = this->memSize + 2;
    newString.length = this->length + 1;
    for (std::size_t i = 0; i < this->length; i++)
    {
        newString.characters[i] = this->characters[i];
    }
    newString.characters[this->length] = c;
    return newString;
}

String String::operator+(const String &other) const
{
    String newString;
    newString.characters = new char[this->memSize + other.memSize];
    newString.memSize = this->memSize + other.memSize;
    newString.length = this->length + other.length;
    for (std::size_t i = 0; i < this->length; i++)
    {
        newString.characters[i] = this->characters[i];
    }
    for (std::size_t i = 0; i < other.length; i++)
    {
        newString.characters[this->length + i] = other.characters[i];
    }
    return newString;
}

const char *String::c_str() const
{
    char *newString = new char[this->length + 1];
    for (std::size_t i = 0; i < this->length; i++)
    {
        newString[i] = this->characters[i];
    }
    newString[this->length] = '\0';
    return newString;
}

bool String::operator==(const String &other) const
{
    for (int i = 0; i < this->length; i++)
        if (this->characters[i] != other.characters[i])
            return false;
    return true;
}

bool String::operator<(const String &other) const
{
    for (int i = 0; i < this->length && i < other.length; i++)
    {
        if ((int)this->characters[i] == (int)other.characters[i])
        {
            continue;
        }
        else
        {
            return (int)this->characters[i] - (int)other.characters[i] < 0 ? true : false;
        }
    }

    if (this->length < other.length)
    {
        return true;
    }
    else if (this->length > other.length)
    {
        return false;
    }

    return false;
}

void String::print()
{
    for (int i = 0; i < length; i++)
    {
        std::cout << characters[i];
    }
    std::cout << std::endl;
}
