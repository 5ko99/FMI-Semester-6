#include <iostream>

class A {
    int *arr;
    size_t len;
public:
    A(const int* _arr,size_t _len):len(_len) {
        arr = new int[len];
        for(size_t i=0;i<len;++i)
            arr[i]=_arr[i];
    }
    A(size_t _len):len(_len) {
        arr = new int[len];
    }
    ~A() {
        std::cout<<"Destructed!\n";
        delete[] arr;
    }

    void print() const {
        for(size_t i=0;i<len;++i)
            std::cout<<arr[i]<<' ';
        std::cout<<'\n';
    }
};

void f(int& n) {
    n*=n;
}

void g(const A& a) {
    a.print();
}

enum class COLOR {
    UNDEFINED = -1,
    RED,
    GREEN,
    BLUE
};

void h(const COLOR& col) {
    switch (col) {
        case COLOR::RED : std::cout<<"Red\n"; break;
        case COLOR::GREEN : std::cout<<"Green\n"; break;
        case COLOR::BLUE : std::cout<<"Blue\n"; break;
        default : std::cerr<<"Undefined color!\n";
    }
}

int main() {
    int len = 5;
    int arr[] = {1,2,3,4,5};
    A* a = new A(arr,len);
    g(*a);
    delete a;
    g(A(arr,len));
    f(len);
    std::cout<<len<<std::endl;
    std::cout<<"Enum tests\n";
    h(COLOR::GREEN);
    return 0;
}
