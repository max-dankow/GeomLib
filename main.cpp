#include <iostream>
#include "Geom.h"

int main() {
    Segment segment(Point(0, 4), Point(2, 3));
    Point point(2, 5);
    std::cout << Geom::pointToSegmentDist(point, segment);
    return 0;
}

