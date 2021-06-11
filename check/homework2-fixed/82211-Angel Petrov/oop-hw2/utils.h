#include <string>
#include "allocator.h"
#include "commands.h"

// checks if a file with the same name exists
bool exists(const std::string& name);

// cases for different commands
void vehicle(Allocator* alloc, Commands* cmnd);

void person(Allocator* alloc, Commands* cmnd);

void acquire(Allocator* alloc, Commands* cmnd);

void release(Allocator* alloc, Commands* cmnd);

void remove(Allocator* alloc, Commands* cmnd);

void save(Allocator* alloc, Commands* cmnd);

void show(Allocator* alloc, Commands* cmnd);

// loads input from file
void loadFile(Allocator* alloc, Commands* cmnd, std::string dir);

// reads vehicles without owners
void readVehicles(Allocator* alloc, Commands* cmnd, std::ifstream& in);

// reads people without vehicles
void readPeople(Allocator* alloc, Commands* cmnd, std::ifstream& in);

// reads people and vehicles who are related
void readRelatedObjects(Allocator* alloc, Commands* cmnd, std::ifstream& in);
