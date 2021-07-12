cmake_minimum_required(VERSION 3.19)
project(ElectronicsTable)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ElectronicsTable
        Cell.cpp
        Cell.h
        CellType.h
        CommandParser.cpp
        CommandParser.h
        CommandType.h
        DocumentHandler.cpp
        DocumentHandler.h
        DoubleType.cpp
        DoubleType.h
        FormulaType.cpp
        FormulaType.h
        IntegerType.cpp
        IntegerType.h
        main.cpp
        Pair.h
        StringHelper.cpp
        StringHelper.h
        StringType.cpp
        StringType.h
        Table.cpp
        Table.h
        termcolor.hpp)
