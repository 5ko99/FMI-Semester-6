#include <iostream>
#include<vector>

template<class T>
void merge(std::vector<T>& arr, size_t l, size_t m, size_t r) {
    size_t n1 = m - l + 1;
    size_t n2 = r - m;

    std::vector<T> L(n1), R(n2);

    for(size_t i = 0; i<n1;++i)
        L[i] = arr[l+i];
    for(size_t i = 0; i<n2;++i)
        R[i] = arr[m + 1 + i];

    //initial index of first, second and merged array
    size_t i = 0; size_t j = 0; size_t k = l;
    while(i<n1 && j<n2) {
        if(L[i]<=R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while(i<n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while(j<n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

template<class T>
void mergeSortHelper(std::vector<T>& arr, size_t l, size_t r) {
    if(l<r) {
        size_t m = l + (r-l) / 2;
        mergeSortHelper(arr,l,m);
        mergeSortHelper(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

template<class T>
void mergeSort(std::vector<T>& arr) {
    mergeSortHelper(arr,0,arr.size()-1);
}

template<class T>
void printArray(const std::vector<T>& arr) {
    std::cout<<"[";
    for(int i=0;i<arr.size()-1;++i)
        std::cout<<arr[i]<<',';
    std::cout<<arr[arr.size()-1]<<"]\n";
}


int main() {
    std::vector<float> arr = {3.1415,2.36,4.2,2.4,6.8,354.1,589,-100,6.64};
    mergeSort(arr);
    printArray(arr);
    return 0;
}
