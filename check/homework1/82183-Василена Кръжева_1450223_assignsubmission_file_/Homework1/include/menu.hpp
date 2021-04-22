#ifndef MENU_H
#define MENU_H

#include "vehicle.hpp"
#include "vehicleallocator.hpp"

//easier use of function pointer
typedef void (*Fun)(VehicleAllocator& vehicles);

struct Menu_Option
{
    int choice;
    char const * text;
    Fun function;
};

void create(VehicleAllocator& vehicles);
void add(VehicleAllocator& vehicles);
void remove(VehicleAllocator& vehicles);
void print(VehicleAllocator& vehicles);

void printMenu();
bool findFunc(VehicleAllocator& vehicles, int choice);

static const Menu_Option main_menu[] = {
    { 1, "Create vehicle", create},
    { 2, "Add vehicle to the garage", add},
    { 3, "Remove vehicle from the garage", remove},
    { 4, "Print the vehicles in the garage", print}
};

static const char separator[] = " ---------------------------------------- \n";
static const char menu_title[] = " Main Menu \n";

static const size_t options =
    sizeof(main_menu) / sizeof(main_menu[0]);

#endif