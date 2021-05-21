#include <iostream>
#include<vector>

template<class T>
void heapify(std::vector<T> &arr, size_t n, size_t idx) {
    size_t largest = idx;
    size_t left = 2*idx + 1;
    size_t right = 2*idx + 2;

    //if left child is largest then root(largest)
    if(left < n && arr[left]>arr[largest])
        largest = left;
    // same check for largest
    if(right<n && arr[right] > arr[largest])
        largest=right;
    //if largest is not the root then swap - put largest at the top
    if(largest != idx) {
        std::swap(arr[idx],arr[largest]);
        //heapify the subtree
        heapify(arr,n,largest);
    }
}

template<class T>
void heapSort(std::vector<T> &arr) {
    for (int i = arr.size() / 2 - 1; i >= 0; --i)
        heapify(arr,arr.size(),i);

    for (int i = arr.size() - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

template<class T>
void printArray(const std::vector<T> &arr) {
    std::cout<<"[";
    for(const auto& el : arr)
        std::cout<<el<<',';
    std::cout<<"]\n";
}

int main() {
    std::vector<short> arr1 = {3,1,2};
    heapSort(arr1);
    printArray(arr1);
    std::vector<short> arr = {5,6,1,-3,8,97,24,248,2,-356,47,647,-36,9};
    heapSort(arr);
    printArray(arr);
    return 0;
}
