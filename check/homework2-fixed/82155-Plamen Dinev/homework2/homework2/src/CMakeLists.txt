add_library(vehicle STATIC "vehicle.cpp" "registration.cpp")
target_compile_features(vehicle PUBLIC cxx_rvalue_references cxx_noexcept cxx_final)
target_include_directories(vehicle PUBLIC "../inc")
target_link_libraries(vehicle PUBLIC person)

add_library(person STATIC "person.cpp")
target_compile_features(person PUBLIC cxx_rvalue_references cxx_noexcept cxx_final)
target_include_directories(person PUBLIC "../inc")
target_link_libraries(person PUBLIC vehicle)

add_library(vehicle_factory STATIC "vehiclefactory.cpp")
target_compile_features(vehicle_factory PUBLIC cxx_rvalue_references cxx_noexcept cxx_final)
target_include_directories(vehicle_factory PUBLIC "../inc")
target_link_libraries(vehicle_factory PUBLIC vehicle)

add_library(person_factory STATIC "personfactory.cpp")
target_compile_features(person_factory PUBLIC cxx_rvalue_references cxx_noexcept cxx_final)
target_include_directories(person_factory PUBLIC "../inc")
target_link_libraries(person_factory PUBLIC person)

add_library(command_parser STATIC "commandparser.cpp")
target_compile_features(command_parser PUBLIC cxx_rvalue_references cxx_noexcept cxx_final)
target_include_directories(command_parser PUBLIC "../inc")
target_link_libraries(command_parser PUBLIC person vehicle person_factory vehicle_factory)