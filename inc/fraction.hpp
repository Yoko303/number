#ifndef ___FRACTION_HPP
#define ___FRACTION_HPP
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

template <typename T> class fraction {
public:
    fraction() : p(true), nu(0), de(1) {};
    fraction(T a, T b = 1);

    fraction& operator+=(const fraction& a);
    fraction& operator-=(const fraction& a);
    fraction& operator*=(const fraction& a);
    fraction& operator/=(const fraction& a);
    const fraction operator-() const;
    std::string to_string() const;
    const bool plus() const { return p; };
    const T nume() const { return nu; };
    const T deno() const { return de; };
private:
    bool p;
    T nu;
    T de;
};

template <typename T> const fraction<T> operator+(const fraction<T>& a, const fraction<T>& b) { fraction<T> ret = a; return ret += b; }
template <typename T> const fraction<T> operator-(const fraction<T>& a, const fraction<T>& b) { fraction<T> ret = a; return ret -= b; }
template <typename T> fraction<T> operator*(const fraction<T>& a, const fraction<T>& b) { fraction<T> ret = a; return ret *= b; }
template <typename T> fraction<T> operator/(const fraction<T>& a, const fraction<T>& b) { fraction<T> ret = a; return ret /= b; }
template <typename T> bool operator==(const fraction<T>& a, const fraction<T>& b);
template <typename T> bool operator!=(const fraction<T>& a, const fraction<T>& b) { return !(a == b); }
template <typename T> bool operator<(const fraction<T>& a, const fraction<T>& b);
template <typename T> bool operator<=(const fraction<T>& a, const fraction<T>& b) { return a == b || a < b; }
template <typename T> bool operator>=(const fraction<T>& a, const fraction<T>& b) { return !(a < b); }
template <typename T> bool operator>(const fraction<T>& a, const fraction<T>& b) { return !(a <= b); }
template <typename T> const fraction<T> abs(const fraction<T>& a) { fraction<T> ret = !a.plus() ? -a : a; return ret; }
template <typename T> std::ostream& operator<<(std::ostream& s, const fraction<T>& a) { return s << a.to_string(); }

template <typename T> T mygcd(T a, T b) {
    if(a % b == 0) return b;
    else return mygcd(b, a % b);
}

template <typename T> void reduction(T& a, T& b) {
//    std::cout << "red: " << a << ' ' << b << std::endl;
    a = abs(a);
    b = abs(b);
    T g = mygcd(a, b);
    a /= g;
    b /= g;
}

template <typename T> fraction<T>::fraction(T a, T b) {
    p = !((a >= 0) ^ (b >= 0));
    nu = abs(a);
    de = abs(b);
    reduction(nu, de);
}

template <typename T> fraction<T>& fraction<T>::operator+=(const fraction<T>& a) {
    if(!a.plus()) return *this -= -a;
    if(!this->plus()) {
        *this = a - (-*this);
        return *this;
    }
    nu = this->nu * a.de + this->de * a.nu;
    de = this->de * a.de;
    reduction(nu, de);
    return *this;
}

template <typename T> fraction<T>& fraction<T>::operator-=(const fraction<T>& a) {
    if(!a.plus()) return *this += -a;
    if(!this->plus()) {
        *this = -(a + (-*this));
        return *this;
    }
    if(abs(*this) < abs(a)) {
        *this = -(a - *this);
        return *this;
    }
    nu = this->nu * a.de - this->de * a.nu;
    de = this->de * a.de;
    reduction(nu, de);
    return *this;
}

template <typename T> fraction<T>& fraction<T>::operator*=(const fraction<T>& a) {
    bool _p = !(p ^ a.p);
    const fraction _a = abs(a);
    *this = abs(*this);
    p = _p;
    nu = this->nu * _a.nu;
    de = this->de * _a.de;
    reduction(nu, de);
    if(nu == 0 && !p) p = true;
    return *this;
}

template <typename T> fraction<T>& fraction<T>::operator/=(const fraction<T>& a) {
    bool _p = !(p ^ a.p);
    const fraction _a = abs(a);
    *this = abs(*this);
    p = _p;
    nu = this->nu * _a.de;
    de = this->de * _a.nu;
    reduction(nu, de);
    if(nu == 0 && !p) p = true;
    return *this;
}

template <typename T> const fraction<T> fraction<T>::operator-() const {
    fraction<T> ret(*this);
    if(ret.nume() != 0) ret.p = !p;
    return ret;
}

template <typename T> bool operator==(const fraction<T>& a, const fraction<T>& b) {
    if(a.plus() != b.plus()) return false;
    if(a.nume() != b.nume()) return false;
    if(a.deno() != b.deno()) return false;
    return true;
}

template <typename T> bool operator<(const fraction<T>& a, const fraction<T>& b) {
    if(!a.plus() && b.plus()) return true;
    else if(a.plus() && !b.plus()) return false;
    else if(!a.plus() && !b.plus()) return -b < -a;
    else return a.nume() * b.deno() < b.nume() * a.deno();
}

template <typename T> std::string fraction<T>::to_string() const {
    std::ostringstream s;
    if(!p) s << '-';
    s << nu;
    if(de != 1) s << '/' << de;
    return s.str();
}

#endif