#ifndef GEOMLIB_GEOM_H
#define GEOMLIB_GEOM_H

#include <cmath>
#include <assert.h>
#include <stdexcept>

static const double STANDART_PRECISION = 0.000001;

class Vector2D {
public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) { }

    Vector2D(Vector2D from, Vector2D to) {
        *this = to - from;
    }

    double length() const {
        return sqrt(x * x + y * y);
    }

    Vector2D operator+(Vector2D other) {
        return Vector2D(this->x + other.x, this->y + other.y);
    }

    Vector2D operator-(Vector2D other) {
        return Vector2D(this->x - other.x, this->y - other.y);
    }

    static double exteriorProd(const Vector2D &a, const Vector2D &b) {
        return a.x * b.y - a.y * b.x;
    }

    static double scalarProd(const Vector2D &a, const Vector2D &b) {
        return a.x * b.x + a.y * b.y;
    }

    bool operator==(const Vector2D &other) const {
        return (fabs(this->x - other.x) < STANDART_PRECISION) && (fabs(this->y - other.y) < STANDART_PRECISION);
    }

    bool operator!=(const Vector2D &other) const {
        return !(*this == other);
    }

    double x, y;
};

typedef Vector2D Point;

class Segment {

public:
    Segment(const Point &a, const Point &b) : a(a), b(b) { }
    Segment() {}

    Point a, b;
};

class Geom {
public:
    static double pointToSegmentDist(Point point, Segment segment);
    static double pointToLineDist(Point point, Point lp1, Point lp2) ;
};

double Geom::pointToLineDist(Point point, Point lp1, Point lp2) {
    Vector2D dirVector(lp1, lp2);
    if (dirVector.length() == 0) {
        throw  std::invalid_argument("Direction vector in null.");
    }
    return Vector2D::exteriorProd(dirVector, point - lp1) / dirVector.length();
}

double Geom::pointToSegmentDist(Point point, Segment segment) {
    Vector2D ab(segment.a, segment.b);
    Vector2D ap(segment.a, point);
    Vector2D bp(segment.b, point);

    if (Vector2D::scalarProd(ab, ap) <= 0) {
        return ap.length();
    }
    if (Vector2D::scalarProd(ab, bp) >= 0) {
        return bp.length();
    }
    return pointToLineDist(point, segment.a, segment.b);
}


#endif //GEOMLIB_GEOM_H
