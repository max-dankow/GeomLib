#include <gtest/gtest.h>
#include "../Geom.h"

TEST(Vector, Operations) {
    ASSERT_EQ(Vector2D(Vector2D(2, 1), Vector2D(-2, 0)), Vector2D(-4, -1));
    ASSERT_EQ(Vector2D(1, 2) - Vector2D(2, 1), Vector2D(-1, 1));
    ASSERT_EQ(Vector2D(7.5, -1) + Vector2D(2.4, 1), Vector2D(9.9, 0));
    // Скалярное произведение.
    ASSERT_EQ(Vector2D::scalarProd(Vector2D(1, 0), Vector2D(0, 100)), 0);
    ASSERT_EQ(Vector2D::scalarProd(Vector2D(1, 0), Vector2D(0, 100)), 0);
    ASSERT_EQ(Vector2D::scalarProd(Vector2D(9.2, 0.78), Vector2D(0, 4.444)), 3.46632);
    // Косое произведение.
    ASSERT_EQ(Vector2D::exteriorProd(Vector2D(1, 0), Vector2D(0, 100)), 100);
    ASSERT_EQ(Vector2D::exteriorProd(Vector2D(-8, 0), Vector2D(-8, -8)), 64);
    ASSERT_EQ(Vector2D::exteriorProd(Vector2D(1, 0), Vector2D(-100, 0)), 0);
    // Норма.
    ASSERT_EQ(Vector2D(3, -4).length(), 5);
    ASSERT_EQ(Vector2D(3, 0).length(), 3);
}

TEST(Vector, Comparation) {
    ASSERT_EQ(Vector2D(0, 1.0000000099), Vector2D(0.000000001, 1));
    ASSERT_NE(Vector2D(0, 1.0000000099), Vector2D(0.001000001, 1));
}

TEST(PointToLineDist, PointToLineDist) {
    ASSERT_EQ(0, Geom::pointToLineDist(Vector2D(10, 0), Vector2D(0, 0), Vector2D(1.9, 0)));
    ASSERT_EQ(0, Geom::pointToLineDist(Vector2D(10, 1), Vector2D(0, 0), Vector2D(10, 1)));
    ASSERT_EQ(1, Geom::pointToLineDist(Vector2D(10, -1), Vector2D(0, 0), Vector2D(1.98, 0)));
    ASSERT_EQ(16, Geom::pointToLineDist(Vector2D(10, 16), Vector2D(0, 0), Vector2D(0.3, 0)));
    ASSERT_EQ(2, Geom::pointToLineDist(Vector2D(2, 7), Vector2D(2, 5), Vector2D(4, 5)));
    ASSERT_EQ(0, Geom::pointToLineDist(Vector2D(0, 5), Vector2D(2, 5), Vector2D(4, 5)));
    EXPECT_THROW(Geom::pointToLineDist(Vector2D(10, 0), Vector2D(10, 20), Vector2D(10, 20)), std::invalid_argument);
}

TEST(PointToSegmentDist, PointToSegmentDist) {
    ASSERT_EQ(1, Geom::pointToSegmentDist(Vector2D(1, 5), Segment(Vector2D(0, 0), Vector2D(0, 10))));
    ASSERT_EQ(2.0, Geom::pointToSegmentDist(Vector2D(0, 4), Segment(Vector2D(2, 3), Vector2D(2, 5))));
    ASSERT_EQ(0, Geom::pointToSegmentDist(Vector2D(2, 3), Segment(Vector2D(2, 3), Vector2D(2, 5))));
    ASSERT_EQ(5, Geom::pointToSegmentDist(Vector2D(5, 9), Segment(Vector2D(2, 3), Vector2D(2, 5))));
    ASSERT_EQ(5, Geom::pointToSegmentDist(Vector2D(5, 9), Segment(Vector2D(-2, 5), Vector2D(2, 5))));
    ASSERT_EQ(0, Geom::pointToSegmentDist(Vector2D(5, 9), Segment(Vector2D(5, 9), Vector2D(2, 5))));
    ASSERT_TRUE(2.828427125 - Geom::pointToSegmentDist(Vector2D(0, 0), Segment(Vector2D(2, 2), Vector2D(2, 5))) < 0.000001);

    ASSERT_EQ(5, Geom::pointToSegmentDist(Vector2D(5, 1), Segment(Vector2D(2, 5), Vector2D(2, 5))));
    ASSERT_EQ(0, Geom::pointToSegmentDist(Vector2D(2, 5), Segment(Vector2D(2, 5), Vector2D(2, 5))));
    ASSERT_EQ(1, Geom::pointToSegmentDist(Vector2D(3, 5), Segment(Vector2D(2, 5), Vector2D(2, 5))));
    ASSERT_TRUE(fabs(Geom::pointToSegmentDist(Vector2D(-1, 0), Segment(Vector2D(0, 1), Vector2D(2, 3))) - 1.414213562) < 1.e-7);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}