//Initial work time: ~4H15M
//Debugging time: ~5H
//Unit testing time: ~6 setting catch2 and not working... nice

#include "Garage.h"


using namespace std;

int main()
{
    Vehicle first = Vehicle("ne znam", "Golf 3-ka", 1);
    Vehicle second = Vehicle("montana", "Nike Air", 1);
    Vehicle third = Vehicle("burgas", "batka", 1);


    Garage home = Garage(3);
    try{
    home.insert(first);
    home.insert(second);
    home.insert(third);
    home.clear();
    
    
    }catch(const char* arr){
        cout << arr;
    }

    return 0;
}