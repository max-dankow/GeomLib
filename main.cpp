#include <iostream>
#include <fstream>
#include <iomanip>
#include "Geom.h"

int main() {
    std::ifstream input("intersec1.in");
    std::ofstream output("intersec1.out");
//    Point point;
//    Segment segment;
    Line firstLine, secondLine;
    input >> firstLine >> secondLine;
    Vector2D point = Geom::linesIntersection(firstLine, secondLine);
    output << std::fixed << std::setprecision(10) << point.x << ' ' << point.y << std::endl;
    return 0;
}

