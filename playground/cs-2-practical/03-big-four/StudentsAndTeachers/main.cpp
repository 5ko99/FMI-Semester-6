#include <iostream>
#include "Student.h"
#include "DynamicArray.h"
#include "catch.hpp"



int main() {
    DynamicArray<Student> arr;
    Student s1(45546, "Petko", "Informatics", 1),
            s2(45545, "Niki", "Informatics", 1),
            s3(50000, "Ivan", "Mathematics", 3),
            s4(60000, "Gosho", "Mathematics and Informatics", 4),
            s5(60003, "Ivan", "Mathematics and Informatics", 8);;
    arr.add(Student{45546,"Petko","Informatics",1});
    arr.add(s2);
    arr.add(s3);
    arr.add(s4);
    arr.print();
    arr.remove(s4);
    arr.print();
    cout<<arr.contains(s5)<<endl;
    return 0;
}