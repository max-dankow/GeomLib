#ifndef GEOMLIB_GEOM_H
#define GEOMLIB_GEOM_H

#include <cmath>
#include <assert.h>
#include <stdexcept>

static const double STANDART_PRECISION = 0.000001;

template<typename T>
class Vector2D {
public:
    Vector2D(T x = 0, T y = 0) : x(x), y(y) { }

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

    static T exteriorProd(const Vector2D &a, const Vector2D &b) {
        return a.x * b.y - a.y * b.x;
    }

    static T scalarProd(const Vector2D &a, const Vector2D &b) {
        return a.x * b.x + a.y * b.y;
    }

    bool operator==(const Vector2D &other) const {
        return (fabs(this->x - other.x) < STANDART_PRECISION) && (fabs(this->y - other.y) < STANDART_PRECISION);
    }

    bool operator!=(const Vector2D &other) const {
        return !(*this == other);
    }

    T x, y;
};

template<typename T>
class Segment {
public:
    Segment(const Vector2D<T > &a, const Vector2D<T > &b) : a(a), b(b) { }

    Segment() { }

    Vector2D<T> a, b;
};

template<typename T>
class Geom {
public:
    static double pointToSegmentDist(Vector2D<T> point, Segment<T> segment);

    static double pointToLineDist(Vector2D<T> point, Vector2D<T> lp1, Vector2D<T> lp2);
};

template <typename T>
double Geom<T>::pointToLineDist(Vector2D<T> point, Vector2D<T> lp1, Vector2D<T> lp2) {
    Vector2D<T> dirVector(lp1, lp2);
    if (dirVector.length() == 0) {
        throw std::invalid_argument("Direction vector in null.");
    }
    return Vector2D<T>::exteriorProd(dirVector, point - lp1) / dirVector.length();
}

template <typename T>
double Geom<T>::pointToSegmentDist(Vector2D<T> point, Segment<T> segment) {
    Vector2D<T> ab(segment.a, segment.b);
    Vector2D<T> ap(segment.a, point);
    Vector2D<T> bp(segment.b, point);

    if (Vector2D<T>::scalarProd(ab, ap) <= 0) {
        return ap.length();
    }
    if (Vector2D<T>::scalarProd(ab, bp) >= 0) {
        return bp.length();
    }
    return pointToLineDist(point, segment.a, segment.b);
}


#endif //GEOMLIB_GEOM_H
