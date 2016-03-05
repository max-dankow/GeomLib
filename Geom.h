#ifndef GEOMLIB_GEOM_H
#define GEOMLIB_GEOM_H

#include <cmath>
static const double STANDART_PRECISION = 0.000001;

class Vector2D {
public:
    Vector2D(double x, double y) : x(x), y(y) { }

    Vector2D(Vector2D from, Vector2D to) {
        *this = to - from;
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
private:
    double x,y;
};

typedef Vector2D Point;

class Segment {

public:
    Segment(const Point &a, const Point &b) : a(a), b(b) { }

    Point a, b;
};

class Geom {
public:
    static double pointToSegmentDist(Point point, Segment segment);
    static double pointToLineDist(Point point, Vector2D dirVector);
};

double Geom::pointToLineDist(Point point, Vector2D dirVe) {
    return 0;
}

double Geom::pointToSegmentDist(Point point, Segment segment) {
    Vector2D ab(segment.b, segment.a);
    Vector2D ap(segment.a, point);
    Vector2D bp(segment.b, point);
    return 0;
}


#endif //GEOMLIB_GEOM_H
