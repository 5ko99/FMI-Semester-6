//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Елеонора Емилова Цекова
// ФН: 45585
// Специалност: Информатика
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 9:30
// Кой компилатор използвате:  GCC
//

#include <iostream>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
using namespace std;

class  IntBuffer{
    int* arr;
public:
     IntBuffer(int* _arr){
        arr=new int[sizeof(_arr)];
        for(size_t i=0;i<sizeof(_arr);i++){
            arr[i]=_arr[i];
        }
     }
     IntBuffer(const IntBuffer& a){
        arr=new int[sizeof(a.arr)];
        for(size_t i=0;i<sizeof(a.arr);i++){
            arr[i]=a.arr[i];
        }
     }
    IntBuffer& operator=(const IntBuffer& a){
        if(this!=&a){
        delete[] arr;
        arr=new int[sizeof(a.arr)];
            for(size_t i=0;i<sizeof(a.arr);i++){
                arr[i]=a.arr[i];
            }
        }
        return *this;
    }
    ~IntBuffer(){
        delete[] arr;
    }
    int setArr(int* _arr){
        arr=new int[sizeof(_arr)];
        for(size_t i=0;i<sizeof(_arr);i++){
            arr[i]=_arr[i];
        }
    }
    int* getArr(){
        return arr;
    }
    IntBuffer(std::size_t size){
        arr=new int[size];
        if(!arr){
           throw std::bad_alloc{};
        }
    }
    IntBuffer(std::size_t size, const IntBuffer& other){
        arr=new int[size];
        int n;
        if(size>=sizeof(other)){
            for(size_t i=0;i<n;i++){
                arr[i]=other[i];
            }
        }
        else{
            throw std::bad_alloc{};
        }
    }
    int& at(std::size_t index){
        if(!index){
            throw std::out_of_range::exception{};
        }
        else{
            return arr[index];
        }
    }
    const int& at(std::size_t index) const{
        if(!index){
            throw std::out_of_range::exception{};
        }
        else{
            return arr[index];
        }
    }
    int& operator[](std::size_t index){
        return arr[index];
    }
    const int& operator[](std::size_t index) const{
        return arr[index];
    }
    std::size_t size() const{
        return sizeof(arr);
    }
    void copy_from(const IntBuffer& other, std::size_t count){
        if(sizeof(other)<count&&sizeof(arr)<count){
            for(size_t i=0;i<count;i++){
                arr[i]=other[i];
            }
        }
        else{
            throw std::out_of_range::exception{};
        }
    }
    bool operator==(const IntBuffer& other) const{
        size_t sum=0;
        size_t sum1=0;
        for(size_t i=0;i<sizeof(arr);i++){
            sum+=arr[i];
            sum1+=other[i];
        }
        if(sizeof(arr)==sizeof(other)&&sum==sum1){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator<(const IntBuffer& other) const{
        bool flag=true;
        size_t s=0;
        size_t k=0;
        for(size_t i=0;;i++){
            if(!arr){
                break;
            }
        }

    }
};


class Set{
    IntBuffer* elements;
public:
    Set(){
        elements=NULL;
    }
    void insert(int value){

    }
    bool contains(int value) const{
        bool flag=true;
        for(int i=0;;i++){
            if(!elements){
                break;
            }
            else if(elements[i]==value){
                return true;
            }
            else{
                flag=false;
            }
        }
        return flag;
    }
    std::size_t size() const{
        size_t s=0;
        for(size_t i=0;;i++){
            if(!elements){
                break;
            }
            s++;
        }
        return s;
    }
};




int main()
{
    return 0;
}
