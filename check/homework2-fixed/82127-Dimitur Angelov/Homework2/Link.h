#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Vehicle.h"

class Link{

   Vehicle veh;
   Person p;

   public:

   Link(Vehicle veh,Person p);
   Link();
   Vehicle& getVehLink();
   Person& getPerLink();



};
