add_executable(main_app "main.cpp")
target_link_libraries(main_app PRIVATE vehicle person person_factory vehicle_factory command_parser)
