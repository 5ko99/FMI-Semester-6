#include "DynamicArray.h"
#include "Student.h"

template<class T>
DynamicArray<T>::DynamicArray(size_t capacity) {
    this->capacity = capacity;
    size = 0;
    arr = new (std::nothrow) T[capacity];
    if(!arr) {
        size=-1;
        capacity=-1;
        arr= nullptr;
    }
}

template<typename T>
void DynamicArray<T>::add(const T& elem) {
    if (size >= capacity) {
        if(!increaseCapacity()) {
            std::cerr << "Not enough memory!" << std::endl;
            return;
        }
    }
    arr[size] = elem;
    size++;
}

template<typename T>
bool DynamicArray<T>::contains(const T& elem) const {
    return (containsNumber(elem) >= 0);
}

template<typename T>
bool DynamicArray<T>::remove(const T &elem) {
    int i = containsNumber(elem);
    if(i>=0) {
        swap(i,size-1);
        size--;
        return true;
    } else {
        return false;
    }
}

template<typename T>
void DynamicArray<T>::swap(int i,int j) {
    const T& temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template<typename T>
int DynamicArray<T>::containsNumber(const T& elem) const {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == elem) return i;
    }
    return -1;
}

template<typename T>
void DynamicArray<T>::print() const {
    for (size_t i = 0; i < size; i++) {
        cout <<'['<< arr[i] <<"]\n";
    }
    cout<<endl;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[]  arr;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) {
    capacity = other.capacity;
    size = other.size;
    arr = new (std::nothrow) T[other.capacity];
    if(arr) copyArray(arr,other.arr,other.size);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        T *newArr = new(std::nothrow) T[other.capacity];
        if (newArr) {
            delete[] arr;
            DynamicArray::copyArray(newArr, other.arr, other.size);
            arr = newArr;
            size = other.size;
            capacity = other.capacity;
        }
    }
    return *this;
}

template<typename T>
bool DynamicArray<T>::increaseCapacity() {
    capacity *= 2;
    T* numbersCopy = new (std::nothrow) T[capacity];
    if (numbersCopy) {
        copyArray(numbersCopy, arr, size);
        delete[] arr;
        arr = numbersCopy;
        return true;
    } else {
        capacity /= 2;
        return false;
    }
}

template<typename T>
void DynamicArray<T>::copyArray(T* destination, const T* source, const size_t& sourceSize) {
    for (size_t i = 0; i < sourceSize; i++) {
        destination[i] = source[i];
    }
}

template class DynamicArray<Student>;