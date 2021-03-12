#include <iostream>
#include "Point2D.h"

void fillArray(Point2D *points, size_t size) {
    for(size_t i=0;i<size;++i) {
        std::cin>>points[i].x>>points[i].y;
    }
}

int main() {
    size_t size;
    std::cin>>size;
    auto *points = new (std::nothrow) Point2D[size];
    if(points== nullptr) return 1;
    fillArray(points,size);
    Point2D closest = getClosetPointToCenter(points,size);
    std::cout<<"Closest point to center is ("<<closest.x<<','<<closest.y<<")\n";
    delete[] points;
    return 0;
}
