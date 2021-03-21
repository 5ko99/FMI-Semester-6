#include "Point2D.h"

inline double square(double x) {
    return x*x;
}

inline double distance2D(Point2D a, Point2D b) {
    return sqrt(square(a.x-b.x)+square(a.y-b.y));
}

Point2D getClosetPointToCenter(Point2D *points,size_t size) {
    Point2D center = {0,0};
    Point2D closest = points[0];
    double minDistance = distance2D(center,closest);

    for(size_t i=0;i<size;++i) {
        double currentDistance = distance2D(center, closest);
        if(currentDistance<minDistance) {
            minDistance = currentDistance;
            closest=points[i];
        }
    }
    return closest;
}