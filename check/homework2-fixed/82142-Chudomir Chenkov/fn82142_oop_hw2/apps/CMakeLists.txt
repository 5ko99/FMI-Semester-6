add_executable(main main.cpp app.cpp)

target_compile_features(main PRIVATE cxx_std_11)

target_link_libraries(main PRIVATE mylib)

target_include_directories(main PRIVATE include)
