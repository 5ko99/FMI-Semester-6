//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Ивайло Недялков Атанасов
// ФН: 45763
// Специалност: информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.4.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: LLVM
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

class Registration{
private:
    char regArr[9];
    
    bool regIsValid(const char* str){
        size_t len = 0;
        while(str[len]!='\0'){
            len++;
        }
        if(len == 7 || len == 8){
            for(int i=0; i<len; i++){
                if( ((str[i]<'0' || str[i]>'9') && (str[i]<'A' || str[i]>'Z')) ){
                    return false;
                }
            }
            if(!(str[1]<'A' || str[1]>'Z')){
                for(int i=2;i<=5;i++)
                    if(str[i]<'0' || str[i]>'9')
                        return false;
            }
            if((str[1]<'A' || str[1]>'Z')){
                for(int i=1;i<=4;i++)
                    if(str[i]<'0' || str[i]>'9')
                        return false;
                if(len == 8) return false;
            }
            
        } else return false;
        
        return true;
    }
public:
    Registration() = delete;
    
    Registration(const char* str){
        size_t len = strlen(str);
        if(regIsValid(str)){
            for(int i=0; i<len; i++){
                regArr[i] = str[i];
            }
            regArr[len] = '\0';
        } else throw std::exception();
    }
    
    Registration& operator=(const char* str){
        size_t len = strlen(str);
        if(regIsValid(str)){
            for(int i=0; i<len; i++){
                regArr[i] = str[i];
            }
            regArr[len] = '\0';
        } else throw std::exception();
        
        return *this;
    }
    
    bool operator==(const char* str) const{
        bool areSame = true;
        for(int i=0;i<strlen(str); i++){
            if(str[i] != this->regArr[i])areSame = false;
        }
        return areSame;
    }
    const char* toString() const{
        return regArr;
    }
};

class Vehicle{
public:
    Registration regnum;
    std::string description;
    
    Vehicle() = delete;
    Vehicle(const char* regnum, const char* description): regnum(regnum){
        this->description = description;
    }
};

class VehicleList{
private:
    Vehicle** _vehiArr;
    std::size_t _capacity;
    std::size_t _vehiCount;
public:
    
    VehicleList(std::size_t capacity){
        _vehiArr = new Vehicle*[capacity];
        _capacity = capacity;
        _vehiCount = 0;
    }
    ~VehicleList(){
        for(int i=0; i<_vehiCount; i++){
            delete _vehiArr[i];
        }
        delete[] _vehiArr;
    }
    
    VehicleList(VehicleList& v){
        copy(v);
    }
    VehicleList& operator=(VehicleList& rhs){
        copy(rhs);
        return *this;
    }
    
    void copy(VehicleList& v){
        Vehicle** buffer = new Vehicle*[v._capacity];
        for(int i=0; i<v._capacity; i++){
            buffer[i] = v._vehiArr[i];
        }
        
        for(int i=0;i<_vehiCount;i++){
            delete _vehiArr[i];
        }
        delete[] _vehiArr;
        
        _vehiArr = buffer;
        _capacity = v._capacity;
        _vehiCount = v._vehiCount;
    }
    
    void insert(const char* regnum, const char* description){
        for(int i=0;i<_vehiCount;i++){
            if(_vehiArr[i]->regnum == regnum){
                throw std::exception();
            }
        }
        if(_vehiCount+1 > _capacity) throw std::exception();
        
        Vehicle* buffer = new Vehicle(regnum, description);
        _vehiArr[_vehiCount] = buffer;
        _vehiCount++;
    }
    
    const Vehicle& at(std::size_t index) const{
        if(index >= _vehiCount) throw std::out_of_range("out of range");
        return *_vehiArr[index];
    }
    
    const Vehicle& operator[](std::size_t index) const {
        assert(index<=_vehiCount);
        return *_vehiArr[index];
    }
    
    bool empty() const{
        return _vehiCount==0;
    }
    std::size_t capacity() const {
        return _capacity;
    }
    std::size_t size() const{
        return _vehiCount;
    }
    
    const Vehicle* find(const char* regnum) const{
        for(int i=0;i<_vehiCount; i++){
            if(_vehiArr[i]->regnum == regnum)
                return _vehiArr[i];
        }
        return nullptr;
    }
};

int main(){
    
    int capacity = 0;
    cout<<"capacity: ";
    cin>>capacity;
    
    VehicleList vl(capacity);
    for(int i=0; i<capacity; i++){
            char reg[9];
            char desc[50];
            //cout<<"------------"<<endl;
            //cout<<"registration: ";
            cin>>reg;
            //cout<<"description: ";
            cin>>desc;
            
            cin.get();
        try{
            vl.insert(reg, desc);
        } catch (const std::exception &e){
            cout<<"invalid vehicle data, please try again"<<endl;
            i--;
        }
    }
    
    cout<<endl;
    char regStr[9];
    cout<<"search for vehicle: ";
    cin>>regStr;
    try{
        const Vehicle* v = vl.find(regStr);
        if(v == nullptr)cout<<"vehicle was not found"<<endl;
        else cout<<"Vehicle with registration "<<regStr<<" and description ("<<v->description<<") was found"<<endl;
    } catch(const std::exception &e){
        cout<<"registration number you tried to search is invalid"<<endl;
    }
    
    return 0;
}
