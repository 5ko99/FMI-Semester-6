#include <cassert>
#include "MyString.h"

MyString::MyString()
{
    this->string = "\0";
}

MyString::MyString(const char *string)
{
    if (!string)
    {
        throw std::invalid_argument("****The string cannot be initialised with a nullptr!****");
    }
    else
    {
        this->string = new char[Mystrlen(string)];
        Mystrcpy(this->string, string);
    }
}

MyString::MyString(const MyString &other)
{
    copy(other);
}

MyString::MyString(MyString &&other) noexcept
{
    this->string = other.string;
    other.string = nullptr;
}

MyString::~MyString()
{
    destroy();
}

MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}

MyString &MyString::operator=(MyString &&other) noexcept
{
    std::swap(this->string, other.string);
    return *this;
}

MyString &MyString::operator=(const char *other)
{
    if (!MystrcmpareEquality(this->string, other))
    {
        try
        {
            char *string = new char[Mystrlen(other)];
            destroy();

            Mystrcpy(string, other);
            this->string = string;
        }
        catch (std::bad_alloc())
        {
            std::cout << "****Caught bad allocation the initial object is returned!****\n";
        }
    }

    return *this;
}

MyString &MyString::operator+=(const MyString &other)
{
    try
    {
        char *newString = Mystrconcat(this->string, other.string);
        destroy();
        this->string = newString;
    }
    catch (std::bad_alloc)
    {
        std::cout << "****Allocation failed! Returning initial string!****\n";
    }

    return *this;
}

MyString MyString::operator+(const MyString &other) const
{
    MyString newString(Mystrconcat(this->string, other.string));

    return newString;
}

MyString &MyString::operator+=(const char c)
{
    try
    {
        char *newString = Mystrconcat(this->string, c);
        destroy();
        this->string = newString;
    }
    catch (std::bad_alloc)
    {
        std::cout << "****Allocation failed! Returning initial string!****\n";
    }

    return *this;
}

MyString MyString::operator+(const char c) const
{
    MyString newString(Mystrconcat(this->string, c));

    return newString;
}

bool MyString::operator==(const MyString &other) const
{
    return MystrcmpareEquality(this->string, other.string);
}

bool MyString::operator<(const MyString &other) const
{
    return MystrcmpareSmaller(this->string, other.string);
}

char &MyString::at(std::size_t index)
{
    if (index >= size())
    {
        std::cout << "\n";
        throw std::out_of_range("****Invalid index****");
    }

    return this->string[index];
}
const char &MyString::at(std::size_t index) const
{
    if (index >= size())
    {
        std::cout << "\n";
        throw std::out_of_range("****Invalid index****");
    }

    return this->string[index];
}

char &MyString::operator[](std::size_t index)
{

#ifdef DEBUG
    assert(index < size())
#endif


        return this->string[index];
}

const char &MyString::operator[](std::size_t index) const
{

#ifdef DEBUG
    assert(index < size())
#endif

        return this->string[index];
}

char &MyString::front()
{

#ifdef DEBUG
    assert(size())
#endif

        return this->string[0];
}

const char &MyString::front() const
{
#ifdef DEBUG
    assert(size())
#endif
        return this->string[0];
}

char &MyString::back()
{
#ifdef DEBUG
    assert(size())
#endif
        return this->string[size() - 1];
}

const char &MyString::back() const
{

#ifdef DEBUG
    assert(size())
#endif

        return this->string[size() - 1];
}

size_t MyString::size() const
{
    if (this->string && !onlyWhiteSpaces(this->string))
    {
        return Mystrlen(this->string);
    }

    return 0;
}

bool MyString::isEmpty() const
{
    return size() == 0;
}

void MyString::clear()
{
    for (size_t i = 0; i < size(); i++)
    {
        this->string[i] = ' ';
    }
}

void MyString::push_back(const char c)
{
    try
    {
        char *newString = Mystrconcat(this->string, c);
        destroy();
        this->string = newString;
    }
    catch (std::bad_alloc)
    {
        std::cout << "****Allocation failed! Returning initial string!****\n";
    }
}

void MyString::pop_back()
{

#ifdef DEBUG
    assert(size())
#endif

        this->string[size() - 1] = '\0';
}

const char *MyString::c_str() const
{
    if (size() > 0)
    {
        return this->string;
    }

    return nullptr;
}

void MyString::print() const
{
    std::cout << "\n";
    for (std::size_t i = 0; i < size(); i++)
    {
        std::cout << this->string[i];
    }
}

void MyString::copy(const MyString &other)
{
    this->string = new char[other.size()];
    Mystrcpy(this->string, other.string);
}

void MyString::destroy()
{
    if (this->string)
    {
        delete[] this->string;
    }
}