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
}

TEST(Vector, Comparation) {
    ASSERT_EQ(Vector2D(0, 1.0000000099), Vector2D(0.000000001, 1));
    ASSERT_NE(Vector2D(0, 1.0000000099), Vector2D(0.001000001, 1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}