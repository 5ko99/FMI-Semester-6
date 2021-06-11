#include "../Headers/ArrayOfPointersUtils.h"
#include "../Headers/Vehicle.h"
#include <cstddef>
#include <iostream>

template<typename T>
T** ArrayOfPointersUtils<T>::assignArray(size_t size) {
	try {
		T** array = new T*[size];
		return array;
	}
	catch (std::bad_alloc e) {
		std::cerr << "Memory fault!" << std::endl;
		throw e; 
	}		
}

template<typename T>
void ArrayOfPointersUtils<T>::clearArray(T** array) {
	delete[] array;
}

template<typename T>
void ArrayOfPointersUtils<T>::copyArray(T** arr1, T** arr2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		arr1[i] = arr2[i];
	}
}

template<typename T>
void ArrayOfPointersUtils<T>::increaseCapacity(T** array, size_t capacity) {
    T** newArr = assignArray(capacity*2);
    copyArray(newArr, array, capacity);
    clearArray(array);
    array = newArr;
}

template class ArrayOfPointersUtils<Vehicle>;
