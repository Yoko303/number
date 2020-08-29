#include "../inc/sqrtn.hpp"
#include "../inc/fraction.hpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace {

TEST(Constructor, Default) {
    sqrtn<int> a;
    EXPECT_TRUE(a.s() == 0);
    EXPECT_TRUE(a.t() == 0);
    EXPECT_TRUE(a.n() == 0);
}

TEST(Constructor, Int) {
    sqrtn<int> a(3, 4, 7);
    EXPECT_TRUE(a.s() == 3);
    EXPECT_TRUE(a.t() == 4);
    EXPECT_TRUE(a.n() == 7);
}

TEST(to_string, Int) {
    sqrtn<int> a(3, 4, 7);
    EXPECT_STREQ(a.to_string().c_str(), "(3)+(4)sqrt(7)");
}

TEST(to_string, Frac) {
    sqrtn<fraction<int>> a(3, 4, 7);
    EXPECT_STREQ(a.to_string().c_str(), "(3)+(4)sqrt(7)");
}

TEST(Add, Int) {
    sqrtn<int> a(1, 2, 3);
    sqrtn<int> b(3, 4, 3);
    sqrtn<int> c = a + b;
    EXPECT_TRUE(c.s() == 4);
    EXPECT_TRUE(c.t() == 6);
}

TEST(Add, Frac) {
    sqrtn<fraction<int>> a(1, 2, 3);
    sqrtn<fraction<int>> b(3, 4, 3);
    sqrtn<fraction<int>> c = a + b;
    EXPECT_TRUE(c.s() == fraction<int>(4));
    EXPECT_TRUE(c.t() == fraction<int>(6));
}

TEST(Add, Self) {
    sqrtn<int> a(1, 2, 3);
    a += a;
    EXPECT_TRUE(a.s() == 2);
    EXPECT_TRUE(a.t() == 4);
}

TEST(Sub, Int) {
    sqrtn<int> a(1, 2, 3);
    sqrtn<int> b(3, 4, 3);
    sqrtn<int> c = a - b;
    EXPECT_TRUE(c.s() == -2);
    EXPECT_TRUE(c.t() == -2);
}

TEST(Sub, Frac) {
    sqrtn<fraction<int>> a(1, 2, 3);
    sqrtn<fraction<int>> b(3, 4, 3);
    sqrtn<fraction<int>> c = a - b;
    EXPECT_TRUE(c.s() == fraction<int>(-2));
    EXPECT_TRUE(c.t() == fraction<int>(-2));
}

TEST(Sub, Self) {
    sqrtn<int> a(1, 2, 3);
    a -= a;
    EXPECT_TRUE(a.s() == 0);
    EXPECT_TRUE(a.t() == 0);
}

TEST(Multi, Int) {
    sqrtn<int> a(1, 2, 3);
    sqrtn<int> b(3, 4, 3);
    sqrtn<int> c = a * b;
    EXPECT_TRUE(c.s() == 27);
    EXPECT_TRUE(c.t() == 10);
}

TEST(Multi, Frac) {
    sqrtn<fraction<int>> a(1, 2, 3);
    sqrtn<fraction<int>> b(3, 4, 3);
    sqrtn<fraction<int>> c = a * b;
    EXPECT_TRUE(c.s() == fraction<int>(27));
    EXPECT_TRUE(c.t() == fraction<int>(10));
}

TEST(Multi, Frac2) {
    sqrtn<fraction<int>> a(1, 0, 23);
    sqrtn<fraction<int>> b(-4, 1, 23);
    sqrtn<fraction<int>> c(-4, 1, 23);
    EXPECT_TRUE(a * b == c);
}

TEST(Multi, Self) {
    sqrtn<int> a(1, 2, 3);
    a *= a;
    EXPECT_TRUE(a.s() == 13);
    EXPECT_TRUE(a.t() == 4);
}

TEST(Div, Int) {
    sqrtn<int> a(1, -1, 2);
    sqrtn<int> b(1, 1, 2);
    sqrtn<int> c = a / b;
    EXPECT_TRUE(c.s() == -3);
    EXPECT_TRUE(c.t() == 2);
}

TEST(Div, Frac) {
    sqrtn<fraction<int>> a(1, -1, 2);
    sqrtn<fraction<int>> b(1, 1, 2);
    sqrtn<fraction<int>> c = a / b;
    EXPECT_TRUE(c.s() == fraction<int>(-3));
    EXPECT_TRUE(c.t() == fraction<int>(2));
}

TEST(Div, Self) {
    sqrtn<int> a(1, -1, 2);
    a /= a;
    EXPECT_TRUE(a.s() == 1);
    EXPECT_TRUE(a.t() == 0);
}

} // namespace