#include "myString.h"

char *MyString::memoryAlloc(const size_t &size)
{
    char *buffer = new char[size];

    return buffer;
}

MyString::MyString(const char *str)
{
    size_t len = strlen(str);

    try
    {
        this->data = memoryAlloc(len);
        strcpy(this->data, str);
        this->data[len] = '\0';
        this->length = len;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to initialize object " << e.what() << '\n';
        throw e;
    }
}

void MyString::copyFrom(const MyString &other)
{
    if (this != &other)
    {
        size_t len = other.length;
        try
        {
            this->data = memoryAlloc(len);
            strcpy(this->data, other.data);
            this->length = len;
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Failed to copy " << e.what() << '\n';
            throw e;
        }
    }
}

MyString::MyString(const MyString &other)
{
    this->copyFrom(other);
}

MyString &MyString::operator=(const MyString &other)
{
    delete[] this->data;
    this->copyFrom(other);
    return *this;
}

char &MyString::operator[](std::size_t pos)
{
    assert(pos < this->length);
    return this->data[pos];
}

const char &MyString::operator[](std::size_t pos) const
{
    assert(pos < this->length);
    return this->data[pos];
}

char &MyString::at(std::size_t pos)
{
    if (pos > this->length)
    {
        throw std::out_of_range("You're trying to access invalid position, bud");
    }
    else
    {
        return this->data[pos];
    }
}

const char &MyString::at(std::size_t pos) const
{
    if (pos > this->length)
    {
        throw std::out_of_range("You're trying to access invalid position, bud");
    }
    else
    {
        return this->data[pos];
    }
}

char &MyString::front()
{
    assert(!this->empty());
    return this->data[0];
}

const char &MyString::front() const
{
    assert(!this->empty());
    return this->data[0];
}

char &MyString::back()
{
    assert(!this->empty());
    return this->data[this->length - 1];
}

const char &MyString::back() const
{
    assert(!this->empty());
    return this->data[this->length - 1];
}

bool MyString::empty() const
{
    if (this->data == nullptr && this->length == 0)
        return true;
    else
        return false;
}

std::size_t MyString::size() const
{
    return this->length;
}

void MyString::clear()
{
    delete[] this->data;
    this->data = nullptr;
    this->length = 0;
}

void MyString::push_back(char c)
{
    try
    {
        char *buffer = new char[this->length + 1];

        if (!this->empty())
        {
            strcpy(buffer, this->data);
            buffer[this->length] = c;
            buffer[this->length + 1] = '\0';
            delete[] this->data;
        }
        else
        {
            buffer[0] = c;
            buffer[1] = '\0';
        }

        this->data = buffer;
        this->length += 1;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to push_back " << e.what() << '\n';
        throw e;
    }
}

MyString &MyString::operator+=(char c)
{
    this->push_back(c);
    return *this;
}

void MyString::pop_back()
{
    assert(this->length > 0);
    try
    {
        char *buffer = new char[this->length - 1];

        strcpy(buffer, this->data);
        buffer[this->length - 1] = '\0';
        delete[] this->data;

        this->data = buffer;
        this->length -= 1;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to pop_back " << e.what() << '\n';
        throw e;
    }
}

MyString &MyString::operator+=(const MyString &rhs)
{
    if (!rhs.empty())
    {
        try
        {
            char *buffer = new char[this->length + rhs.length];

            if (!this->empty())
            {
                strcpy(buffer, strcat(this->data, rhs.data));
                delete[] this->data;
            }
            else
            {
                strcpy(buffer, rhs.data);
            }

            this->data = buffer;
            this->length += rhs.length;
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Failed to concatenate " << e.what() << '\n';
            throw e;
        }
    }
    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString s(*this);
    s += c;

    return s;
}

MyString MyString::operator+(const MyString &rhs) const
{
    MyString s(*this);
    s += rhs;

    return s;
}

const char *MyString::c_str() const
{
    try
    {
        char *copy = new char[this->length];
        strcpy(copy, this->data);
        return copy;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to return copy array " << e.what() << '\n';
        throw e;
        return nullptr;
    }
}

bool MyString::operator==(const MyString &rhs) const
{
    return !strcmp(this->data, rhs.data);
}

bool MyString::operator<(const MyString &rhs) const
{
    if (this->length < rhs.length)
        return true;
    else if (this->length == rhs.length)
    {
        if (this->length == 0)
            return true;
        return strcmp(this->data, rhs.data);
    }
    else
        return false;
}

MyString::~MyString()
{
    delete[] this->data;
}

char *MyString::getData() const
{
    return this->data;
}
