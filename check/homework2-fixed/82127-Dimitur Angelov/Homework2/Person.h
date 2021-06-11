#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Registration.h"


class Person{

   std::string name;
   unsigned int id;
   std::vector<Registration> owned;

   public:

   Person(const std::string name,unsigned int id);
   Person();

   std::string& getName();
   unsigned int& getId();
   std::vector<Registration> getRegs();




};
