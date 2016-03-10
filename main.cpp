#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Geom.h"

void solveTanget(Vector2D point, Vector2D center, long radius, std::ostream &output) {
    // Точка на окружности.
    if (fabs((center.x - point.x) * (center.x - point.x) + (center.y - point.y) * (center.y - point.y) -
             radius * radius) < STANDART_PRECISION) {
        output << 1 << std::endl << point.x << ' ' << point.y << std::endl;
        return;
    }
    // Точка внутри окружности.
    if ((point - center).length() < radius) {
        output << 0;
        return;
    }
    // Точка все окружности.
    double R = (point - center).length();
    double l = sqrt(R * R - radius * radius);
    double h = l * radius / R;
    double a = sqrt(l * l - h * h);
    Vector2D po(point, center);
    Vector2D pa = po * (a/R);
    Vector2D ortogonal(pa.y, -pa.x);
    ortogonal = ortogonal * (h / ortogonal.length());
    Vector2D p1 = point + pa + ortogonal;
    Vector2D p2 = point + pa - ortogonal;
    Vector2D p3 = point + pa;
    output << 2 << std::endl;
    output << p3.x << ' ' << p3.y << std::endl;
    output << a << ' ' << h << std::endl;
    output << p1.x << ' ' << p1.y << std::endl;
    output << p2.x << ' ' << p2.y << std::endl;
}

int main() {
    std::ifstream input("tangent.in");
    std::ofstream output("tangent.out");
    Vector2D point, center;
    long radius;
    input >> center.x >> center.y >> radius >> point.x >> point.y;
    output << std::setprecision(10);
    solveTanget(point, center, radius, output);
    return 0;
}

