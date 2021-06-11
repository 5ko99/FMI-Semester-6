# Testing library
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG  v2.13.6)
FetchContent_MakeAvailable(catch)
# Adds Catch2::Catch2

# compile the catch_main as separate target because it is so slow to compile
add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2)

add_executable(registration_test registration_test.cpp)
target_link_libraries(registration_test PRIVATE catch_main vehicle)
add_test(NAME registration COMMAND registration_test) # Command can be a target

add_executable(vehicle_person_test vehicle_person_test.cpp)
target_link_libraries(vehicle_person_test PRIVATE catch_main vehicle person vehicle_factory person_factory)
add_test(NAME vehicle_person_test COMMAND vehicle_person_test) # Command can be a target