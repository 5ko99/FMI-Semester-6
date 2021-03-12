#pragma once

#include <cstdio>
#include <cmath>
struct Point2D {
    double x;
    double y;
};

inline double square(double);

inline double distance2D(Point2D a, Point2D b);

Point2D getClosetPointToCenter(Point2D*,size_t);
