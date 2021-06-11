//
// Created by pgpetrov on 21.05.21 Рі..
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "DB.h"
#include "CommandDispatcher.h"

int main(int argc, const char** argv) {
  DB db;

  if (argc == 2) { // load data from file
    std::ostringstream discard;
    //discard output
    //errors to std::cerr
    CommandDispatcher command_dispatcher(db, discard);
    std::ifstream file(argv[1]);
    while (file >> command_dispatcher) {}
  }

  CommandDispatcher command_dispatcher(db); // default is std::cout and std::cerr
  while (std::cin >> command_dispatcher) {}
}
