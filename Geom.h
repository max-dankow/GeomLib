#ifndef GEOMLIB_GEOM_H
#define GEOMLIB_GEOM_H

#include <cmath>
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <vector>

static const double STANDART_PRECISION = 1e-7;

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

    Segment() { }

    Point a, b;
};

class Line {
public:
    Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) { }

    double a, b, c;
};

std::istream &operator>>(std::istream &input, Line &line) {
    double a, b, c;
    input >> a >> b >> c;
    line.a = a;
    line.b = b;
    line.c = c;
    return input;
}

class Geom {
public:
    static double pointToSegmentDist(Point point, Segment segment);

    static double pointToLineDist(Point point, Point lp1, Point lp2);

    static Point linesIntersection(const Line &firstLine, const Line &secondLine);

    static double signedArea(const std::vector<Vector2D> &points);

    static bool isConvex(const std::vector<Vector2D> &points);
};

double Geom::pointToLineDist(Point point, Point lp1, Point lp2) {
    Vector2D dirVector(lp1, lp2);
    if (dirVector.length() == 0) {
        throw std::invalid_argument("Direction vector in null");
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

Vector2D Geom::linesIntersection(const Line &firstLine, const Line &secondLine) {
    Point result;
    double denominator = firstLine.a * secondLine.b - secondLine.a * firstLine.b;
    if (fabs(denominator) < STANDART_PRECISION) {
        throw std::invalid_argument("Lines are parallel");
    }
    result.x = -(firstLine.c * secondLine.b - secondLine.c * firstLine.b) / denominator;
    result.y = -(firstLine.a * secondLine.c - secondLine.a * firstLine.c) / denominator;
    return result;
}

double Geom::signedArea(const std::vector<Vector2D> &points) {
    if (points.empty()) {
        return 0;
    }
    double sum = (points.back().x + points.front().x) * (points.back().y - points.front().y);
    for (size_t i = 0; i < points.size() - 1; ++i) {
        sum += (points[i].x + points[i + 1].x) * (points[i].y - points[i + 1].y);
    }
    return sum / 2;
}

bool Geom::isConvex(const std::vector<Vector2D> &points) {
    if (points.size() < 3) {
        throw std::invalid_argument("Polygon is empty");
    }
    bool positive = false, negative = false;

    for (size_t i = 0; i < points.size(); ++i) {
        Vector2D prevEdge(points[i % points.size()], points[(i + 1) % points.size()]);
        Vector2D nextEdge(points[(i + 1) % points.size()], points[(i + 2) % points.size()]);
        double prod = Vector2D::exteriorProd(prevEdge, nextEdge);
        if (fabs(prod) < STANDART_PRECISION) {
            continue;
        }
        if (prod > 0) {
            positive = true;
        }
        if (prod < 0) {
            negative = true;
        }
        if (positive && negative) {
            return false;
        }
    }

    if (positive || negative) {
        return true;
    } else {
        throw std::invalid_argument("Polygon is a line");
    }
}

#endif //GEOMLIB_GEOM_H
