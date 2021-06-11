#ifndef Registration_H
#define Registration_H
#include <iostream>
#include <cstring>

class Registration
{

public:
  Registration();
  Registration(const Registration &);
  ~Registration();

  bool operator==(const std::string &);
  void setNumberPlate();
  std::string getNumberPlate();

private:
  bool validationOfNumberPlate(char[]);
  char numberPlate[9];
};

#include "Registration.cpp"
#endif
