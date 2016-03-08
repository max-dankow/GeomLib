#include <gtest/gtest.h>
#include "../Geom.h"

TEST(Vector, Operations) {
    ASSERT_EQ(Vector2D<int>(Vector2D<int>(2, 1), Vector2D<int>(-2, 0)), Vector2D<int>(-4, -1));
    ASSERT_EQ(Vector2D<int>(1, 2) - Vector2D<int>(2, 1), Vector2D<int>(-1, 1));
    ASSERT_EQ(Vector2D<double>(7.5, -1) + Vector2D<double>(2.4, 1), Vector2D<double>(9.9, 0));
    // Скалярное произведение.
    ASSERT_EQ(Vector2D<int>::scalarProd(Vector2D<int>(1, 0), Vector2D<int>(0, 100)), 0);
    ASSERT_EQ(Vector2D<int>::scalarProd(Vector2D<int>(1, 0), Vector2D<int>(0, 100)), 0);
    ASSERT_EQ(Vector2D<double>::scalarProd(Vector2D<double>(9.2, 0.78), Vector2D<double>(0, 4.444)), 3.46632);
    // Косое произведение.
    ASSERT_EQ(Vector2D<int>::exteriorProd(Vector2D<int>(1, 0), Vector2D<int>(0, 100)), 100);
    ASSERT_EQ(Vector2D<int>::exteriorProd(Vector2D<int>(-8, 0), Vector2D<int>(-8, -8)), 64);
    ASSERT_EQ(Vector2D<int>::exteriorProd(Vector2D<int>(1, 0), Vector2D<int>(-100, 0)), 0);
    // Норма.
    ASSERT_EQ(Vector2D<int>(3, -4).length(), 5);
    ASSERT_EQ(Vector2D<int>(3, 0).length(), 3);
}

TEST(Vector, Comparation) {
    ASSERT_EQ(Vector2D<double>(0, 1.0000000099), Vector2D<double>(0.000000001, 1));
    ASSERT_NE(Vector2D<double>(0, 1.0000000099), Vector2D<double>(0.001000001, 1));
}

TEST(PointToLineDist, PointToLineDist) {
    ASSERT_EQ(0, Geom<int>::pointToLineDist(Vector2D<int>(10, 0), Vector2D<int>(0, 0), Vector2D<int>(1.9, 0)));
    ASSERT_EQ(0, Geom<int>::pointToLineDist(Vector2D<int>(10, 1), Vector2D<int>(0, 0), Vector2D<int>(10, 1)));
    ASSERT_EQ(-1, Geom<double>::pointToLineDist(Vector2D<double>(10, -1), Vector2D<double>(0, 0), Vector2D<double>(1.98, 0)));
    ASSERT_EQ(16, Geom<double>::pointToLineDist(Vector2D<double>(10, 16), Vector2D<double>(0, 0), Vector2D<double>(0.3, 0)));
    ASSERT_EQ(2, Geom<int>::pointToLineDist(Vector2D<int>(2, 7), Vector2D<int>(2, 5), Vector2D<int>(4, 5)));
    ASSERT_EQ(0, Geom<int>::pointToLineDist(Vector2D<int>(0, 5), Vector2D<int>(2, 5), Vector2D<int>(4, 5)));
    EXPECT_THROW(Geom<int>::pointToLineDist(Vector2D<int>(10, 0), Vector2D<int>(10, 20), Vector2D<int>(10, 20)), std::invalid_argument);
}

TEST(PointToSegmentDist, PointToSegmentDist) {
    ASSERT_EQ(2.0, Geom<int>::pointToSegmentDist(Vector2D<int>(0, 4), Segment<int>(Vector2D<int>(2, 3), Vector2D<int>(2, 5))));
    ASSERT_EQ(0, Geom<int>::pointToSegmentDist(Vector2D<int>(2, 3), Segment<int>(Vector2D<int>(2, 3), Vector2D<int>(2, 5))));
    ASSERT_EQ(5, Geom<int>::pointToSegmentDist(Vector2D<int>(5, 9), Segment<int>(Vector2D<int>(2, 3), Vector2D<int>(2, 5))));
    ASSERT_EQ(5, Geom<int>::pointToSegmentDist(Vector2D<int>(5, 9), Segment<int>(Vector2D<int>(-2, 5), Vector2D<int>(2, 5))));
    ASSERT_EQ(0, Geom<int>::pointToSegmentDist(Vector2D<int>(5, 9), Segment<int>(Vector2D<int>(5, 9), Vector2D<int>(2, 5))));
    ASSERT_TRUE(2.828427125 - Geom<int>::pointToSegmentDist(Vector2D<int>(0, 0), Segment<int>(Vector2D<int>(2, 2), Vector2D<int>(2, 5))) < 0.000001);

    ASSERT_EQ(5, Geom<int>::pointToSegmentDist(Vector2D<int>(5, 1), Segment<int>(Vector2D<int>(2, 5), Vector2D<int>(2, 5))));
    ASSERT_EQ(0, Geom<int>::pointToSegmentDist(Vector2D<int>(2, 5), Segment<int>(Vector2D<int>(2, 5), Vector2D<int>(2, 5))));
    ASSERT_EQ(1, Geom<int>::pointToSegmentDist(Vector2D<int>(3, 5), Segment<int>(Vector2D<int>(2, 5), Vector2D<int>(2, 5))));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}