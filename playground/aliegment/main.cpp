#include <iostream>
using std::cout;
using std::endl;

struct A {
    char a;
    int b;
    char c;
};

struct B {
    int b;
    char a;
    char c;
};

int main() {
    cout<<sizeof(int)<<endl;
    cout<<sizeof(char)<<endl;
    cout<<sizeof(A)<<endl;
    cout<<sizeof(B)<<endl;

    A array1[1000];
    B array2[1000];

    std::cout << "Array with 1000 elements of type A is: " << sizeof(array1) << " bytes\n";
    std::cout << "Array with 1000 elements of type B is: " << sizeof(array2) << " bytes\n";
    return 0;
}
