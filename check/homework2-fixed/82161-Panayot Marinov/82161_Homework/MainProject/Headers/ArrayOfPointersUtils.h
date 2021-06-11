#pragma once
#ifndef ARRAY_OF_POINTERS_UTILS_H
#define ARRAY_OF_POINTERS_UTILS_H

#include <cstddef>

template<typename T>
class ArrayOfPointersUtils {
public:
    static T** assignArray(size_t size);
    static void clearArray(T** array);
    static void increaseCapacity(T** array, size_t capacity);
    static void copyArray(T** arr1, T** arr2, size_t size);
};

#endif /* ARRAY_OF_POINTERS_UTILS_H */
