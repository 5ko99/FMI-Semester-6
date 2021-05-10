cmake_minimum_required(VERSION 3.19)
project(Shapes)

set(CMAKE_CXX_STANDARD 20)

include_directories(Interfaces
        Shapes
        Shapes/Triangles
        Utilities)

add_executable(Shapes main.cpp
        Interfaces/ISerializable.hpp
        Interfaces/IShapeCloneable.hpp
        Interfaces/IDescribableShape.h
        Shapes/Rectangle.cpp
        Shapes/Rectangle.h
        Shapes/ShapesContainer.cpp
        Shapes/ShapesContainer.h
        Shapes/Square.cpp
        Shapes/Square.h
        Shapes/Triangles/EquilateralTriangle.cpp
        Shapes/Triangles/EquilateralTriangle.h
        Shapes/Triangles/IsoscelesTriangle.cpp
        Shapes/Triangles/Triangle.h
        Shapes/Triangles/Triangle.cpp
        Shapes/Triangles/IsoscelesTriangle.h
        Shapes/Triangles/ScaleneTriangle.cpp
        Shapes/Triangles/ScaleneTriangle.h
        )
