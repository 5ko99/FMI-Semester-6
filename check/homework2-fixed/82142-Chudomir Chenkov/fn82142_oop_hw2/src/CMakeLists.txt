set(HEADER_LIST
    "${OOP-Assignment-2_SOURCE_DIR}/include/cmd.hpp"
    "${OOP-Assignment-2_SOURCE_DIR}/include/databasemanager.hpp"
    "${OOP-Assignment-2_SOURCE_DIR}/include/person.hpp"
    "${OOP-Assignment-2_SOURCE_DIR}/include/registration.hpp"
    "${OOP-Assignment-2_SOURCE_DIR}/include/utils.hpp"
    "${OOP-Assignment-2_SOURCE_DIR}/include/vehicle.hpp"
)

add_library(mylib
    cmd.cpp
    databasemanager.cpp
    person.cpp
    registration.cpp
    utils.cpp
    vehicle.cpp
    ${HEADER_LIST}
)

target_include_directories(mylib PUBLIC ${OOP-Assignment-2_SOURCE_DIR}/include)

target_compile_features(mylib PUBLIC cxx_std_11)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)
