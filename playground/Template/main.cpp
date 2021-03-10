#include <iostream>

template<typename T,size_t N>
class Array {
private:
    T arr[N];
public:
    size_t getSize() const {
        return N;
    }
};



int main() {
    Array<float,10> arr;
    std::cout<<arr.getSize()<<std::endl;

    return 0;
}
