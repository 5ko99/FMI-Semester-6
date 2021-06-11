#pragma once
#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <cstddef>

template<typename T>
class ArrayUtils {
public:
    static T* assignArray(size_t size);
    static void increaseCapacity(T* array, size_t capacity);
    static void copyArray(T* arr1, T* arr2, size_t size);
};

#endif /* ARRAYUTILS_H */
