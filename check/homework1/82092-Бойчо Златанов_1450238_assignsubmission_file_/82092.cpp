#include<iostream>
#include<cstring>

class Mystring
{
  public:
   Mystring();
   Mystring(const char* str);
   ~Mystring();
   void print();
  char& at(std::size_t pos);
  char& front();
  char& back();
  bool empty() const;
  std::size_t size() const;
  void clear();
  void push_back(char c);
  void pop_back();
  const char* c_str() const;
  char& operator [] (std::size_t pos)
  {
    std::cout<<"Operator called"<<std::endl;
    return my_string[pos - 1];
  }

Mystring& operator+=(char c)
{
    this->push_back(c);
    return *this;
}

Mystring& operator+=(const Mystring& rhs)
{
    int sz = strlen(rhs.my_string);
    for(int i=0;i<sz;i++)
    {
        this->push_back(rhs.my_string[i]);
    }

    return *this;
}

Mystring operator+(char c) const
{
    Mystring copy_str(my_string);
    copy_str+=c;
    return copy_str;
}

Mystring operator+(const Mystring& rhs) const
{
  Mystring str3(my_string);
  str3+= rhs;
  return str3;
}

bool operator==(const Mystring &rhs) const
{
  int size = strlen(my_string);
  if(size != strlen(rhs.my_string))
  {
    return 0;
  }
  for ( int i = 0; i < size; i++)
  {
    if(my_string[i] != rhs.my_string[i])
    {
      return 0;
    }
  }
  return 1;

}


  private:
  char *my_string;
  int allocated_space;

};

Mystring::Mystring()
{
  my_string = nullptr;
  allocated_space = 0;
}

Mystring::Mystring(const char* str)
{
  std::cout<<" "<<std::endl;
  int size = strlen(str);
  allocated_space = size + 1;
  this -> my_string = new char[allocated_space];
  this -> my_string [allocated_space - 1] = '\0';
 for(int i = 0; i < strlen(str); i++)
 {
   my_string[i] = str[i];
 }
}

Mystring::~Mystring()
{
  std::cout<<std::endl;
    delete[] my_string;
    my_string = nullptr;
}

char& Mystring::at(std::size_t pos)
{
  std::cout<<"The position of the element is = ";
  return my_string[pos-1];
}


  char& Mystring::front()
  {
    std::cout<<"Function front = ";
    return my_string[0];
  }

 char& Mystring::back()
{
    int sz = strlen(my_string);
    return my_string[sz - 1];
}
bool Mystring::empty() const
{
  std::cout<<"If the string is empty = ";
  if(strlen(my_string) == 0)
  {
    return true;
  }
  return false;
}

void Mystring::print()
{
  std::cout<<this->my_string;
}

std::size_t Mystring::size() const
{
  return strlen(my_string);
}

void Mystring::clear()
{
  my_string[0] = '\0';
  std::cout<<"The string is empty ! ";
}

void Mystring::push_back(char c)
{
   int sz = strlen(my_string);
   if(sz + 1 < allocated_space)
   {
     my_string[sz] = c;
     my_string[sz + 1] = '\0';
   }
   else {
    char* new_String = new char[sz + 2];
    for(int i = 0 ; i < sz; i++)
    {
        new_String[i] = my_string[i];
    }
    delete [] my_string;

    new_String[sz] = c;
    new_String[sz + 1] = '\0';
    my_string = new_String;

}
}

void Mystring::pop_back()
{
   int size = strlen(my_string);
   my_string[size - 1] = '\0';
}

const char*  Mystring::c_str() const
{
   return my_string;
}

class Vehicle
{
  private:
  Mystring _registration;
  Mystring _description;
  std::size_t _space;

public:
  Vehicle(const char* registration, const char* description, std::size_t space)
  :_registration(registration),_description(description),_space(space)
  {}
  const char* registration() const;



};
const char* Vehicle::registration() const
{
  return _registration.c_str();
}



int main()
{

    Mystring L ("Money team");
    Mystring Q ("Money team");

    std::cout<<std::endl;
    std::cout<<L.at(2);
    std::cout<<std::endl;
    L.at(2) = ('K');
    std::cout<<L.at(2);
    std::cout<<L.front();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<L.back();
    std::cout<<std::endl;
    std::cout<<L.empty();
    std::cout<<std::endl;
    std::cout<<L.size();
    std::cout<<std::endl;
    L.print();
    std::cout<<std::endl;
    L.push_back('1');
    L.print();
    L.pop_back();
    L.print();
    L +=('S');
    L.print();
    L += Q;
    L.print();
    Mystring k = (L+'9');
    k.print();
    k = L + Q;
    k.print();
    std::cout<<L.c_str();
    k.print();

    Vehicle car("1232","Blue",100);
    std::cout<<car.registration();


    return 0;
}