#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Geom.h"

int main() {
    std::ifstream input("hull.in");
    std::ofstream output("hull.out");
    size_t pointNumber;
    input >> pointNumber;
    std::vector<Vector2D> points;
    points.reserve(pointNumber);

    for (size_t i = 0; i < pointNumber; ++i) {
        long x, y;
        input >> x >> y;
        points.push_back(Vector2D(x, y));
    }
    auto hull = Geom::getHull(points);
    output << hull.size() << std::endl;
    for (Vector2D p : hull) {
        output << long(p.x) << ' ' << long(p.y) << std::endl;
    }
    //output << std::fixed << std::setprecision(10) << (Geom::isConvex(points) ? "YES" : "NO") << std::endl;
    return 0;
}

