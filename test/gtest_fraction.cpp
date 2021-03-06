#include "../inc/fraction.hpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace {

TEST(Constructor, Default) {
    fraction<int> a;
    EXPECT_TRUE(a.plus());
    EXPECT_TRUE(a.nume() == 0);
    EXPECT_TRUE(a.deno() == 1);
}

TEST(Constructor, IntPlus) {
    fraction<int> a(5);
    EXPECT_TRUE(a.plus());
    EXPECT_TRUE(a.nume() == 5);
    EXPECT_TRUE(a.deno() == 1);
}

TEST(Constructor, IntZero) {
    fraction<int> a(0);
    EXPECT_TRUE(a.plus());
    EXPECT_TRUE(a.nume() == 0);
    EXPECT_TRUE(a.deno() == 1);
}

TEST(Constructor, IntMinus) {
    fraction<int> a(-5);
    EXPECT_FALSE(a.plus());
    EXPECT_TRUE(a.nume() == 5);
    EXPECT_TRUE(a.deno() == 1);
}

TEST(Constructor, FracPlus1) {
    fraction<int> a(5, 2);
    EXPECT_TRUE(a.plus());
    EXPECT_TRUE(a.nume() == 5);
    EXPECT_TRUE(a.deno() == 2);
}

TEST(Constructor, FracPlus2) {
    fraction<int> a(-5, -2);
    EXPECT_TRUE(a.plus());
    EXPECT_TRUE(a.nume() == 5);
    EXPECT_TRUE(a.deno() == 2);
}

TEST(Constructor, FracMinus1) {
    fraction<int> a(-5, 2);
    EXPECT_FALSE(a.plus());
    EXPECT_TRUE(a.nume() == 5);
    EXPECT_TRUE(a.deno() == 2);
}

TEST(Constructor, FracMinus2) {
    fraction<int> a(5, -2);
    EXPECT_FALSE(a.plus());
    EXPECT_TRUE(a.nume() == 5);
    EXPECT_TRUE(a.deno() == 2);
}

TEST(Constructor, FracGCD) {
    fraction<int> a(100, 250);
    EXPECT_TRUE(a.plus());
    EXPECT_TRUE(a.nume() == 2);
    EXPECT_TRUE(a.deno() == 5);
}

TEST(to_string, Frac) {
    fraction<int> a(3, 4);
    EXPECT_STREQ(a.to_string().c_str(), "3/4");
    fraction<int> b(-3, 4);
    EXPECT_STREQ(b.to_string().c_str(), "-3/4");
}

TEST(to_string, Int) {
    fraction<int> a(3);
    EXPECT_STREQ(a.to_string().c_str(), "3");
    fraction<int> b(-3);
    EXPECT_STREQ(b.to_string().c_str(), "-3");
}

TEST(Equal, _) {
    fraction<int> a(3, 4);
    fraction<int> b(30, 40);
    EXPECT_TRUE(a == b);
}

TEST(NotEqual, _) {
    fraction<int> a(3, 4);
    fraction<int> b(30, 41);
    EXPECT_TRUE(a != b);
}

TEST(Bigger, _) {
    fraction<int> a(30, 41);
    fraction<int> b(31, 41);
    EXPECT_TRUE(a < b);
}

TEST(Add, Random) {
    ifstream ifs("case_fraction/add.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        int an, ad, bn, bd, cn, cd;
        iss >> an >> ad >> bn >> bd >> cn >> cd;
        fraction<int> a(an, ad);
        fraction<int> b(bn, bd);
        fraction<int> c(cn, cd);
        EXPECT_TRUE(a + b == c);
    }
}

TEST(Add, Self) {
    fraction<int> a(2, 5);
    a += a;
    fraction<int> b(4, 5);
    EXPECT_TRUE(a == b);
}

TEST(Sub, Random) {
    ifstream ifs("case_fraction/sub.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        int an, ad, bn, bd, cn, cd;
        iss >> an >> ad >> bn >> bd >> cn >> cd;
        fraction<int> a(an, ad);
        fraction<int> b(bn, bd);
        fraction<int> c(cn, cd);
        EXPECT_TRUE(a - b == c);
    }
}

TEST(Sub, Self) {
    fraction<int> a(2, 5);
    a -= a;
    fraction<int> b(0, 1);
    EXPECT_TRUE(a == b);
}

TEST(Multi, Random) {
    ifstream ifs("case_fraction/multi.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        int an, ad, bn, bd, cn, cd;
        iss >> an >> ad >> bn >> bd >> cn >> cd;
        fraction<int> a(an, ad);
        fraction<int> b(bn, bd);
        fraction<int> c(cn, cd);
        EXPECT_TRUE(a * b == c);
    }
}

TEST(Multi, Self) {
    fraction<int> a(2, 5);
    a *= a;
    fraction<int> b(4, 25);
    EXPECT_TRUE(a == b);
}

TEST(Div, Random) {
    ifstream ifs("case_fraction/div.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        int an, ad, bn, bd, cn, cd;
        iss >> an >> ad >> bn >> bd >> cn >> cd;
        fraction<int> a(an, ad);
        fraction<int> b(bn, bd);
        fraction<int> c(cn, cd);
        EXPECT_TRUE(a / b == c);
    }
}

TEST(Div, Self) {
    fraction<int> a(2, 5);
    a /= a;
    fraction<int> b(1, 1);
    EXPECT_TRUE(a == b);
}

} // namespace