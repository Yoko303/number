#ifndef ___BIGN_HPP
#define ___BIGN_HPP
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

class bign {
public:
    bign(int x = 0);
    bign(const std::string& s);
    bign(std::vector<int> v, bool p = true) : v(v), p(p) {};

    bign& operator+=(const bign& a);
    bign& operator-=(const bign& a);
    bign& operator*=(const bign& a);
    bign& operator/=(const bign& a);
    bign& operator%=(const bign& a);
    bign operator-() const;

    bign& operator<<=(int a);
    bign operator<<(int a) const { bign ret(*this); return ret <<= a; };

    const int& operator[](std::size_t i) const { return v[i]; };
    int& operator[](std::size_t i) { return v[i]; };

    bign pow(int x) const;
    std::string to_string() const;
    std::vector<int>::size_type size() const { return v.size(); };
    bign rev() const;
    const bool plus() const { return p; };
private:
    std::vector<int> v;
    bool p;
    void rmzero() { while(v.size() > 1 && v.back() == 0) v.pop_back(); };
};

inline const bign operator+(const bign& a, const bign& b) { bign ret = a; return ret += b; }
inline const bign operator-(const bign& a, const bign& b) { bign ret = a; return ret -= b; }
inline const bign operator*(const bign& a, const bign& b) { bign ret = a; return ret *= b; }
inline const bign operator/(const bign& a, const bign& b) { bign ret = a; return ret /= b; }
inline const bign operator%(const bign& a, const bign& b) { bign ret = a; return ret %= b; }
inline std::ostream& operator<<(std::ostream& s, const bign& a) { return s << a.to_string(); }
bool operator==(const bign& a, const bign& b);
inline bool operator!=(const bign& a, const bign& b) { return !(a == b); }
bool operator<(const bign& a, const bign& b);
inline bool operator<=(const bign& a, const bign& b) { return a == b || a < b; }
inline bool operator>=(const bign& a, const bign& b) { return !(a < b); }
inline bool operator>(const bign& a, const bign& b) { return !(a <= b); }
inline const bign abs(const bign& a) { bign ret = a < 0 ? -a : a; return ret; }
const bign gcd_bign(const bign& a, const bign& b);

#endif