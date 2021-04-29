// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Виктор Николаев Нолев
// ФН: 45641
// Специалност: Информатика
// Курс: 2.
// Административна група: 1.
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 09:30
// Кой компилатор използвате: GCC
//

//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <cstddef>
#include <cstdlib>
#include <stdexcept>


/// IntBuffer class
class IntBuffer {
private:
    int *m_elements;
    std::size_t m_size;
    std::size_t m_capacity;

    void freeMemory();

    bool sameElements(const IntBuffer &other) const;

public:
    IntBuffer() = delete;

    IntBuffer(std::size_t size);

    IntBuffer(const IntBuffer &other);

    IntBuffer &operator=(const IntBuffer &other);

    ~IntBuffer();

    IntBuffer(std::size_t size, const IntBuffer &other);

    int &at(std::size_t index);

    const int &at(std::size_t index) const;

    int &operator[](std::size_t index);

    const int &operator[](std::size_t index) const;

    std::size_t size() const;

    void copy_from(const IntBuffer &other, std::size_t count);

    bool operator==(const IntBuffer &other) const;

    bool operator<(const IntBuffer &other) const;
};

IntBuffer::IntBuffer(std::size_t size) {
    try {
        m_elements = new int[size];
    } catch (std::bad_alloc &ex) {
        delete[] m_elements;
        throw;
    }

    m_size = size;
    m_capacity = size;
}

IntBuffer::IntBuffer(std::size_t size, const IntBuffer &other) {

    IntBuffer arr(size);
    std::size_t N = std::min(size, other.m_size);
    copy_from(other, N);
}

int &IntBuffer::at(std::size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Index is invalid!");
    }
//    return m_elements[index];
    return m_elements[index];
}

const int &IntBuffer::at(std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Index is invalid!");
    }
    return m_elements[index];
}

int &IntBuffer::operator[](std::size_t index) {
    assert(index < m_size);
    return m_elements[index];
}

const int &IntBuffer::operator[](std::size_t index) const {
    assert(index < m_size);
    return m_elements[index];
}

std::size_t IntBuffer::size() const {
    return m_capacity;
}

void IntBuffer::copy_from(const IntBuffer &other, std::size_t count) {
    if (other.m_size < count ||
        m_size < count) {
        throw std::out_of_range("Invalid value for count!");
    }

    // TODO This creates a shallow copy???
    for (int i = 0; i < count; ++i) {
        int element = other.m_elements[i];
        m_elements[i] = element;
    }

    m_size = other.m_size;
    m_elements = other.m_elements;
}

IntBuffer::IntBuffer(const IntBuffer &other) {
    copy_from(other, other.m_size);
}

IntBuffer &IntBuffer::operator=(const IntBuffer &other) {
    if (this != &other) {
        freeMemory();
        copy_from(other, other.m_size);
    }
    return *this;
}

IntBuffer::~IntBuffer() {
    freeMemory();
}

void IntBuffer::freeMemory() {
    /* for (int i = 0; i < m_size; ++i) {
         delete[] m_elements[i];
     }*/
    delete[] m_elements;
}

bool IntBuffer::operator==(const IntBuffer &other) const {
    return sameElements(other);
}

bool IntBuffer::sameElements(const IntBuffer &other) const {
    if (m_size != other.m_size) {
        return false;
    }

    for (int i = 0; i < m_size; ++i) {
        if (m_elements[i] != other.m_elements[i]) {
            return false;
        }
    }
    return true;
}

// TODO Check logic
bool IntBuffer::operator<(const IntBuffer &other) const {
    std::size_t n = std::min(m_size, other.m_size);
    for (int i = 0; i < n; ++i) {
        if (m_elements[i] > other.m_elements[i]) {
            return false;
        }
    }
    return true;
}

/// Set class
class Set {
private:
    IntBuffer **elements;
    std::size_t capacity;

    std::size_t elementsCount;

    bool isUnique(int value);

    /// Doubles the capacity of Set object
    void resize();

    void freeMemory();

    void copyFrom(const Set &other);

public:
    Set();

    Set(const Set &other);

    Set &operator=(const Set &other);

    ~Set();

    void insert(int value);

    std::size_t size() const;
};

Set::Set() {
    capacity = 2;
    elementsCount = 0;
    // Try-catch block for safety?
    elements = new IntBuffer *[capacity];

}

Set::Set(const Set &other) {
    copyFrom(other);
}

Set &Set::operator=(const Set &other) {
    if (this != &other) {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Set::~Set() {
    freeMemory();
}

void Set::insert(int value) {
    if (!isUnique(value)) {
        return;
    }

    if (elementsCount + 1 > capacity) {
        try {
            resize();
        } catch (std::bad_alloc &ex) {
            return;
        }
    }

    // Search for proper position to insert in sorted elements
    size_t i;
    for (i = elementsCount; i > 0; --i) {
        if (*elements[i] < value) {
            break;
        }
        // TODO Check logic
        *elements[i] = *elements[i - 1];
    }
    // We have found index to insert sorted
    *elements[i] = value;
    ++elementsCount;
}

bool Set::isUnique(int value) {
    for (int i = 0; i < elementsCount; ++i) {
        if (*elements[i] == value) {
            return false;
        }
    }
    return true;
}

void Set::resize() {
    IntBuffer **buffer;
    try {
        buffer = new IntBuffer *[capacity * 2];
    } catch (std::bad_alloc &ex) {
        // Return in valid state to achieve strong exception guarantee
        delete[] buffer;
        buffer = nullptr;
        throw;
    }

    // Now we can safely increase our members
    capacity *= 2;

    // Copy content of each element - do not point to same address :)
    for (int i = 0; i < elementsCount; ++i) {
        buffer[i] = elements[i];
    }
    delete[] elements;
    elements = buffer;
}

std::size_t Set::size() const {
    return elementsCount;
}

void Set::freeMemory() {
    for (int i = 0; i < elementsCount; ++i) {
        delete[] elements[i];
    }
//    delete[] elements;
}

void Set::copyFrom(const Set &other) {
    // New variable in case of which accidentally size() iterates over each element :)
    std::size_t otherSize = other.size();
    for (int i = 0; i < otherSize; ++i) {
        // Probably the whole class may be refactored :)
        insert(other.elements[i]->at(i));
    }
}

int main() {

    Set set;
    set.insert(1);
    set.insert(2);
    std::cout << "Works?\n";
    return 0;
}