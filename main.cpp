#include <iostream>
#include <fstream>
#include "Geom.h"

int main() {
    std::ifstream input("distance4.in");
    std::ofstream output("distance4.out");
    Point point;
    Segment segment;
    input >> point.x >> point.y >> segment.a.x >> segment.a.y >> segment.b.x >> segment.b.y;
    output << Geom::pointToSegmentDist(point, segment) << std::endl;
    return 0;
}

