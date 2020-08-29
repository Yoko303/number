#include "../inc/bign.hpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace {

TEST(Constructor, IntPlus) {
    bign a(123);
    EXPECT_EQ(a[0], 3);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 1);
    EXPECT_EQ(a.size(), 3);
    EXPECT_TRUE(a.plus());
}

TEST(Constructor, IntZero) {
    bign b(0);
    EXPECT_EQ(b[0], 0);
    EXPECT_EQ(b.size(), 1);
    EXPECT_TRUE(b.plus());
}

TEST(Constructor, IntMinus) {
    bign c(-123);
    EXPECT_EQ(c[0], 3);
    EXPECT_EQ(c[1], 2);
    EXPECT_EQ(c[2], 1);
    EXPECT_EQ(c.size(), 3);
    EXPECT_FALSE(c.plus());
}

TEST(Constructor, StrPlus) {
    string s = "15";
    bign d(s);
    EXPECT_EQ(d[0], 5);
    EXPECT_EQ(d[1], 1);
    EXPECT_EQ(d.size(), 2);
    EXPECT_TRUE(d.plus());
}

TEST(Constructor, StrMinus) {
    string s = "-15";
    bign e(s);
    EXPECT_EQ(e[0], 5);
    EXPECT_EQ(e[1], 1);
    EXPECT_EQ(e.size(), 2);
    EXPECT_FALSE(e.plus());
}

TEST(to_string, _) {
    bign a = 100;
    EXPECT_STREQ(a.to_string().c_str(), "100");
    a = 0;
    EXPECT_STREQ(a.to_string().c_str(), "0");
    a = -100;
    EXPECT_STREQ(a.to_string().c_str(), "-100");
}

TEST(Equal, _) {
    bign a = 100;
    int b = 100;
    long long c = 100;
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(c == a);
}

TEST(NotEqual, _) {
    bign a = 100;
    int b = 200;
    long long c = 200;
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b != a);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(c != a);
}

TEST(Bigger, _) {
    bign a = 200;
    int b = 100, c = 300;
    long long d = 100, e = 300;
    EXPECT_TRUE(b < a);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(d < a);
    EXPECT_TRUE(a < e);
}

TEST(Add, Loop) {
    const int range = 100;
    const int step = 1;
    for(int i = -range; i <= range; i += step) {
        for(int j = -range; j <= range; j += step) {
            bign bi = i, bj = j;
            bign expected = i + j;
            EXPECT_TRUE(bi + bj == expected);
            EXPECT_TRUE(i + bj == expected);
            EXPECT_TRUE(bi + j == expected);
        }
    }
}

TEST(Add, Random) {
    ifstream ifs("case_bign/add.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        string a, b, c;
        iss >> a >> b >> c;
        EXPECT_TRUE(bign(a) + bign(b) == bign(c));
    }
}

TEST(Add, Self) {
    bign a = 10;
    a += a;
    EXPECT_TRUE(a == 20);
}

TEST(Sub, Loop) {
    const int range = 100;
    const int step = 10;
    for(int i = -range; i <= range; i += step) {
        for(int j = -range; j <= range; j += step) {
            bign bi = i, bj = j;
            bign expected = i - j;
            EXPECT_TRUE(bi - bj == expected);
            EXPECT_TRUE(i - bj == expected);
            EXPECT_TRUE(bi - j == expected);
        }
    }
}

TEST(Sub, Random) {
    ifstream ifs("case_bign/sub.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        string a, b, c;
        iss >> a >> b >> c;
        EXPECT_TRUE(bign(a) - bign(b) == bign(c));
    }
}

TEST(Sub, Self) {
    bign a = 10;
    a -= a;
    EXPECT_TRUE(a == 0);
}

TEST(Multi, Loop) {
    const int range = 100;
    const int step = 5;
    for(int i = -range; i <= range; i += step) {
        for(int j = -range; j <= range; j += step) {
            bign bi = i, bj = j;
            bign expected = i * j;
            EXPECT_TRUE(bi * bj == expected);
            EXPECT_TRUE(i * bj == expected);
            EXPECT_TRUE(bi * j == expected);
        }
    }
}

TEST(Multi, Random) {
    ifstream ifs("case_bign/multi.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        string a, b, c;
        iss >> a >> b >> c;
        EXPECT_TRUE(bign(a) * bign(b) == bign(c));
    }
}

TEST(Multi, Self) {
    bign a = 10;
    a *= a;
    EXPECT_TRUE(a == 100);
}

TEST(Div, Loop) {
    const int range = 100;
    const int step = 10;
    for(int i = -range; i <= range; i += step) {
        for(int j = -range; j <= range; j += step) {
            if(j == 0) continue;
            bign bi = i, bj = j;
            bign expected = i / j;
            EXPECT_TRUE(bi / bj == expected);
            EXPECT_TRUE(i / bj == expected);
            EXPECT_TRUE(bi / j == expected);
        }
    }
}

TEST(Div, Random) {
    ifstream ifs("case_bign/div.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        string a, b, c;
        iss >> a >> b >> c;
        EXPECT_TRUE(bign(a) / bign(b) == bign(c));
    }
}

TEST(Div, Self) {
    bign a = 10;
    a /= a;
    EXPECT_TRUE(a == 1);
}

TEST(Remain, Loop) {
    const int range = 100;
    const int step = 10;
    for(int i = -range; i <= range; i += step) {
        for(int j = -range; j <= range; j += step) {
            if(j == 0) continue;
            bign bi = i, bj = j;
            bign expected = i % j;
            EXPECT_TRUE(bi % bj == expected);
            EXPECT_TRUE(i % bj == expected);
            EXPECT_TRUE(bi % j == expected);
        }
    }
}

TEST(Remain, Random) {
    ifstream ifs("case_bign/remain.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        string a, b, c;
        iss >> a >> b >> c;
        EXPECT_TRUE(bign(a) % bign(b) == bign(c));
    }
}

TEST(Remain, Self) {
    bign a = 10;
    a %= a;
    EXPECT_TRUE(a == 0);
}

TEST(Power, Plus) {
    bign a = 5;
    EXPECT_TRUE(a.pow(0) == 1);
    EXPECT_TRUE(a.pow(3) == 125);
    EXPECT_TRUE(a.pow(20) == bign(string("95367431640625")));
}

TEST(Power, Zero) {
    bign a = 0;
    EXPECT_TRUE(a.pow(0) == 1);
    EXPECT_TRUE(a.pow(3) == 0); // ??
}

TEST(Power, Minus) {
    bign a = -5;
    EXPECT_TRUE(a.pow(0) == 1);
    EXPECT_TRUE(a.pow(3) == -125);
}

TEST(Power, Random) {
    ifstream ifs("case_bign/power.txt", ios::in);
    string s;
    while(getline(ifs, s)) {
        istringstream iss(s);
        string a, c;
        int b;
        iss >> a >> b >> c;
        EXPECT_TRUE(bign(a).pow(b) == bign(c));
    }
}

TEST(Bign, Shift) {
    bign a = 5;
    int shift = 4;
    bign b = a << shift;
    EXPECT_TRUE(b == 50000);
}

TEST(Bign, Minus) {
    bign a = 5;
    EXPECT_TRUE(-a == -5);
    bign b = -5;
    EXPECT_TRUE(-b == 5);
}

TEST(Bign, ABS) {
    bign a = 5;
    EXPECT_TRUE(abs(a) == 5);
    bign b = -5;
    EXPECT_TRUE(abs(b) == 5);
}

} // namespace