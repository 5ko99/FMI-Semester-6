#include <assert.h>

#include <cstring>
#include <iostream>

#include "Headers/ExampleProgram.hpp"
#include "Headers/Garage.hpp"
#include "Headers/MyString.hpp"
#include "Headers/Vehicle.hpp"

//#define NDEBUG

int main() {
    try {
        garageManager();
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << std::endl;
    } catch (const std::logic_error& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
    }

    return 0;
}

// NOTES
// EXECUTABLE COMMANDS
// g++ .\main.cpp MyString.cpp Vehicle.cpp Garage.cpp
// g++ .\CatchTests.cpp MyString.cpp Vehicle.cpp Garage.cpp .\catch2\catch2.cpp