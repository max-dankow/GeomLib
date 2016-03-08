#include <iostream>
#include <fstream>
#include <iomanip>
#include "Geom.h"

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    Vector2D<long> point;
    Segment<long> segment;
    input >> point.x >> point.y >> segment.a.x >> segment.a.y >> segment.b.x >> segment.b.y;
    output << std::fixed << std::setprecision(6) << Geom<long>::pointToSegmentDist(point, segment) << std::endl;
    return 0;
}

