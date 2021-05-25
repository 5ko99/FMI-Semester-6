//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име:Синан Мехмед
// ФН:82050
// Специалност:Компютърни науки
// Курс:2
// Административна група:2
// Ден, в който се явявате на контролното: 24.04.2021.
// Начален час на контролното: 9:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

class IntBuffer
{
private:
    std::size_t bufferSize;
    int *data;

public:
    IntBuffer(std::size_t size);
    IntBuffer(std::size_t size, const IntBuffer &other);

    IntBuffer(const IntBuffer &other);
    IntBuffer &operator=(const IntBuffer &other);
    ~IntBuffer();

    int &at(std::size_t index);
    const int &at(std::size_t index) const;
    int &operator[](std::size_t index);
    std::size_t size() const;
    void copy_from(const IntBuffer &other, std::size_t count);
    bool operator==(const IntBuffer &other) const;
    bool operator<(const IntBuffer &other) const;

private:
    void copy(const IntBuffer &other);
};

IntBuffer::IntBuffer(std::size_t size) : bufferSize(size)
{
    try
    {
        data = new int[size];
    }
    catch (std::bad_alloc &ex)
    {
        std::cerr << ex.what();
    }
}

void IntBuffer::copy(const IntBuffer &other)
{
    try
    {
        data = new int[other.bufferSize];
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what() << '\n';
    }
    for (size_t i = 0; i < other.bufferSize; i++)
    {
        data[i] = other.data[i];
    }
    bufferSize = other.bufferSize;
}

IntBuffer::IntBuffer(std::size_t size, const IntBuffer &other)
{
    size_t n = (bufferSize < other.bufferSize) ? bufferSize : other.bufferSize;
    try
    {
        data = new int[n];
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what() << '\n';
    }

    copy_from(other, n);
}

IntBuffer::IntBuffer(const IntBuffer &other)
{
    copy(other);
}

IntBuffer &IntBuffer::operator=(const IntBuffer &other)
{
    if (this != &other)
    {
        delete[] data;
        copy(other);
    }
    return *this;
}

IntBuffer::~IntBuffer()
{
    delete[] data;
}

int &IntBuffer::at(std::size_t index)
{
    if (index > bufferSize)
    {
        throw std::out_of_range("Index is out of range...");
    }
    return data[index];
}

const int &IntBuffer::at(std::size_t index) const
{
    if (index > bufferSize)
    {
        throw std::out_of_range("Index is out of range...");
    }
    return data[index];
}

int &IntBuffer::operator[](std::size_t index)
{
    assert(index < bufferSize);
    return data[index];
}

std::size_t IntBuffer::size() const
{
    return bufferSize;
}

void IntBuffer::copy_from(const IntBuffer &other, std::size_t count)
{
    if (count > bufferSize || count > other.bufferSize)
    {
        throw std::out_of_range("Count is out of range.");
    }

    for (size_t i = 0; i < count; i++)
    {
        data[i] = other.data[i];
    }
}

bool IntBuffer::operator==(const IntBuffer &other) const
{
    if (bufferSize == other.bufferSize)
    {
        size_t i = 0;
        while (i < bufferSize)
        {
            if (data[i] == other.data[i])
            {
                i++;
            }
        }
        if (i == bufferSize)
        {
            return true;
        }
    }
    return false;
}

bool IntBuffer::operator<(const IntBuffer &other) const
{
    //
}

class Set
{
private:
    IntBuffer elements;
    std::size_t capacity;
    std::size_t used;

public:
    Set();
    void insert(int value);
    bool contains(int value) const;
    std::size_t size() const;
};

Set::Set()
{
    capacity = 2;
    IntBuffer(capacity);
    used = 0;
}

void Set::insert(int value)
{
    if (contains(value))
    {
        return;
    }

    if (capacity <= used)
    {
        IntBuffer newBuffer(capacity);
        capacity *= 2;
        try
        {
            newBuffer(capacity);
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        newBuffer.copy_from(elements, elements.size());
        elements = newBuffer;
    }
    elements[used] = value;
    used++;
}

bool Set::contains(int value) const
{
    /*
    //binSearch
    size_t size = used;
    int tmp = elements[size / 2];
    if (value == tmp)
    {
        return true;
    }

    if (value > tmp)
    {
        return contains(elements + size / 2, size / 2, value);
    }
    return contains(elements, size / 2, value);
    //*/
}

std::size_t Set::size() const
{
    return elements.size();
}

int main()
{
    Set generated;
    std::size_t n;
    std::cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int num = std::rand();
        generated.insert(num);
    }

    Set G;
    int num;
    for (size_t i; i; i++)
    {
        std::cin >> num;
        if (generated.contains(num))
        {
            std::cout << "Contains";
            G.insert(num);
        }
        std::cout << "No";
        if (G.size() == generated.size())
        {
            std::cout << "Stop";
            return 0;
        }
    }

    return 0;
}
