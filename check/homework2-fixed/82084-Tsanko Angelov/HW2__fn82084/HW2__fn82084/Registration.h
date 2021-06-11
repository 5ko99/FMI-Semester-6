#ifndef __Registration__HH
#define __Registration__HH

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

class Registration
{
  private:
  std::string registration;

  void copy(const Registration &other);
  void clean();

  public:
  Registration();
  Registration(const Registration &other);
  Registration &operator=(const Registration &other);
  ~Registration();
  Registration(std::string _registration);
  std::string getRegistration() const;
  bool valid_symbol();
};

#endif
