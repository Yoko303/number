#ifndef ___SQRTN_HPP
#define ___SQRTN_HPP
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "fraction.hpp"

template <typename T> class sqrtn {
public:
    sqrtn() : _s(0), _t(0), _n(0) {};
    sqrtn(T s, T t, T n) : _s(s), _t(t), _n(n) {};

    sqrtn& operator+=(const sqrtn& a) { _s += a.s(); _t += a.t(); return *this; };
    sqrtn& operator-=(const sqrtn& a) { _s -= a.s(); _t -= a.t(); return *this; };
    sqrtn& operator*=(const sqrtn& a);
    sqrtn& operator/=(const sqrtn& a);
//    const sqrtn operator-() const;
    std::string to_string() const;
    const T& s() const { return _s; }
    const T& t() const { return _t; }
    const T& n() const { return _n; }
private:
    T _s;  // s+t*sqrt(n);
    T _t;
    T _n;
};

template <typename T> const sqrtn<T> operator+(const sqrtn<T>& a, const sqrtn<T>& b) { sqrtn<T> ret = a; return ret += b; }
template <typename T> const sqrtn<T> operator-(const sqrtn<T>& a, const sqrtn<T>& b) { sqrtn<T> ret = a; return ret -= b; }
template <typename T> sqrtn<T> operator*(const sqrtn<T>& a, const sqrtn<T>& b) { sqrtn<T> ret = a; return ret *= b; }
template <typename T> sqrtn<T> operator/(const sqrtn<T>& a, const sqrtn<T>& b) { sqrtn<T> ret = a; return ret /= b; }
template <typename T> bool operator==(const sqrtn<T>& a, const sqrtn<T>& b);
template <typename T> bool operator!=(const sqrtn<T>& a, const sqrtn<T>& b) { return !(a == b); }
template <typename T> bool operator<(const sqrtn<T>& a, const sqrtn<T>& b);
template <typename T> bool operator<=(const sqrtn<T>& a, const sqrtn<T>& b) { return a == b || a < b; }
template <typename T> bool operator>=(const sqrtn<T>& a, const sqrtn<T>& b) { return !(a < b); }
template <typename T> bool operator>(const sqrtn<T>& a, const sqrtn<T>& b) { return !(a <= b); }
template <typename T> std::ostream& operator<<(std::ostream& s, const sqrtn<T>& a) { return s << a.to_string(); }

template <typename T> sqrtn<T>& sqrtn<T>::operator*=(const sqrtn<T>& a) {
    sqrtn<T> tmp = *this;
    T ns = tmp.s() * a.s() + _n * tmp.t() * a.t();
    T nt = tmp.s() * a.t() + tmp.t() * a.s();
    _s = ns;
    _t = nt;
    return *this;
}

template <typename T> sqrtn<T>& sqrtn<T>::operator/=(const sqrtn<T>& a) {
    const sqrtn<T> tmp = *this;
    T deno = a.s() * a.s() - _n * a.t() * a.t();
    T numes = tmp.s() * a.s() - _n * tmp.t() * a.t();
    T numet = tmp.t() * a.s() - tmp.s() * a.t();
    _s = numes / deno;
    _t = numet / deno;
    return *this;
}

template <typename T> std::string sqrtn<T>::to_string() const {
    std::ostringstream os;
    os << "(" << _s << ")+(" << _t << ")sqrt(" << _n << ")";
    return os.str();
}

template <typename T> bool operator==(const sqrtn<T>& a, const sqrtn<T>& b) {
    if(a.s() != b.s()) return false;
    if(a.t() != b.t()) return false;
    return true;
}

template <typename T> bool operator<(const sqrtn<T>& a, const sqrtn<T>& b) {
    if(a == b) return false;
    if(a.s() < b.s() && a.t() < b.t()) return true;
    if(a.s() > b.s() && b.t() < a.t()) return false;
    if(a.s() > b.s() && b.t() > a.t()) return (a.s()-b.s())*(a.s()-b.s()) < a.n()*(b.t()-a.t())*(b.t()-a.t());
    else return a.n()*(b.t()-a.t())*(b.t()-a.t()) < (a.s()-b.s())*(a.s()-b.s());
}


#endif