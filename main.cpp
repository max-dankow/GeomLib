#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Geom.h"

int main() {
    std::ifstream input("polygon.in");
    std::ofstream output("polygon.out");
    size_t pointNumber;
    input >> pointNumber;
    std::vector<Vector2D> points;
    points.reserve(pointNumber);

    for (size_t i = 0; i < pointNumber; ++i) {
        long x, y;
        input >> x >> y;
        points.push_back(Vector2D(x, y));
    }
//    if ()
    output << std::fixed << std::setprecision(10) << (Geom::isConvex(points) ? "YES" : "NO") << std::endl;
    return 0;
}

