#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Link.h"

class Base{

   std::vector<Vehicle> vehicles;
   std::vector<Person> persons;
   std::vector<Link> links;

   public:

   Base(std::string file);
   Base();

   std::vector<Vehicle> getV();
   std::vector<Person> getP();
   std::vector<Link> getL();

   bool existReg(Registration r);
   bool existVeh(Vehicle v);
   bool existPer(Person p);

   void VEHICLE (Registration reg,std::string descr);
   void PERSON (std::string name, unsigned int id);
   void ACQUIRE (unsigned id, Registration reg);
   void RELEASE (unsigned id, Registration reg);
   void REMOVE_PER (unsigned int a);
   void REMOVE_VEH (std::string s);
   void SAVE (std::string s);
   void SHOW_PER ();
   void SHOW_VEH ();
   void SHOW_IDV (std::string s);
   void SHOW_IDP (unsigned int a);




};

