#pragma once

#include <iostream>

using std::cout;
using std::endl;

template<class T>
class DynamicArray {
private:
    size_t capacity;
    size_t size;
    T* arr;

    static void copyArray(T* destination, const T* source, const size_t& sourceSize);
    bool increaseCapacity();
    int containsNumber(const T& elem) const;
    void swap(int i,int j);
public:
    DynamicArray(size_t capacity=16);
    ~DynamicArray();
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    void add(const T& elem);
    bool contains(const T& elem) const;
    void print() const;
    bool remove(const T& elem);
};