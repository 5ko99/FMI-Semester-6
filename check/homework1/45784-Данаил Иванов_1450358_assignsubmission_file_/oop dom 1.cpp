#include <iostream>
#include <cstring>
using namespace std;
class Mystring {
public:

    Mystring();

    Mystring(const char* str);

    Mystring() = delete;

    Mystring() = default;
   
        Mystring(const char* str);
       
            const char& at(std::size_t pos);

          
        char& operator[](std::size_t pos)
        {
            assert(pos < used);
            return data[pos];
        }
        


