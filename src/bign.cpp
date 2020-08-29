#include "../inc/bign.hpp"
using namespace std;

bign::bign(int x) {
    p = x < 0 ? false : true;
    v.clear();
    x = abs(x);
    while(x > 0) {
        v.push_back(x % 10);
        x /= 10;
    }
    if(v.empty()) v.push_back(0);
}

bign::bign(const string& s) {
    int i = 0, n = s.size();
    if(s[0] == '-') {
        p = false;
        ++i;
    }
    else p = true;
    while(i < n && s[i] == '0') ++i;
    if(i == n) {
        v.push_back(0);
        return;
    }
    while(i < n) v.push_back(s[i++] - '0');
    reverse(v.begin(), v.end());
    return;
}

bign& bign::operator+=(const bign& a) {
    if(!a.plus()) return *this -= -a;
    if(!this->plus()) {
        *this = a - (-*this);
        return *this;
    }
    vector<int> av = a.v;
    if(v.size() > av.size()) av.resize(v.size());
    else if(v.size() < av.size()) v.resize(av.size());
    int carry = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        int sum = v[i] + av[i] + carry;
        carry = sum / 10;
        sum %= 10;
        v[i] = sum;
    }
    if(carry == 1) v.push_back(1);
    return *this;
}

bign& bign::operator-=(const bign& a) {
    if(!a.plus()) return *this += -a;
    if(!this->plus()) {
        *this = -(a + (-*this));
        return *this;
    }
    if(abs(*this) < abs(a)) {
        *this = -(a - *this);
        return *this;
    }
    vector<int> av = a.v;
    if(v.size() > av.size()) av.resize(v.size());
    else if(v.size() < av.size()) v.resize(av.size());
    int carry = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        v[i] -= av[i] + carry;
        if(v[i] < 0) {
            v[i] += 10;
            carry = 1;
        }
        else carry = 0;
    }
    rmzero();
    return *this;
}

bign& bign::operator*=(const bign& a) {
    bool _p = !(p ^ a.p);
    const bign tmp = *this;
    bign ret = 0;
    for(vector<int>::size_type i = 0; i < a.size(); ++i) {
        for(vector<int>::size_type j = 0; j < tmp.size(); ++j) {
            ret += bign(a[i] * tmp[j]) << (i + j);
        }
    }
    *this = ret;
    rmzero();
    p = _p;
    if(abs(*this) == 0) p = true;
    return *this;
}

bign& bign::operator/=(const bign& a) {
    bool _p = !(p ^ a.p);
    if(*this < 0) *this = -*this;
    bign a0 = a < 0 ? -a : a;
    vector<int> vtmp(1, 0);
    for(int i = this->size() - a0.size(); i >= 0; --i) {
        bign a1 = a0 << i;
        for(int j = 9; j >= 0; --j) {
            if(*this < a1 * j) continue;
            *this -= a1 * j;
            vtmp.push_back(j);
            break;
        }
    }
    reverse(vtmp.begin(), vtmp.end());
    v = vtmp;
    p = _p;
    rmzero();
    if(abs(*this) == 0) p = true;
    return *this;
}

bign& bign::operator%=(const bign& a) {
    bign b = *this / a;
    return *this -= b * a;
}

bign bign::operator-() const {
    bign ret(*this);
    if(ret != 0) ret.p = !p;
    return ret;
}

bign& bign::operator<<=(int x) {
    reverse(v.begin(), v.end());
    v.resize(v.size() + x);
    reverse(v.begin(), v.end());
    return *this;
}

bign bign::pow(int t) const {
    bign base = *this;
    bign ret = 1;
    while(t > 0) {
        if(t & 1) ret *= base;
        base *= base;
        t >>= 1;
    }
    return ret;
}

string bign::to_string() const {
    ostringstream s;
    if(!p) s << '-';
    vector<int> vr = v;
    reverse(vr.begin(), vr.end());
    for(auto& i : vr) s << i;
    return s.str();
}

bign bign::rev() const {
    vector<int>::size_type i = 0;
    vector<int> a;
    while(i < size() && v[i] == 0) ++i;
    while(i < size()) a.push_back(v[i++]);
    if(a.empty()) return bign(0);
    reverse(a.begin(), a.end());
    return bign(a); 
}

bool operator==(const bign& a, const bign& b) {
    if(a.size() != b.size() || a.plus() != b.plus()) return false;
    for(size_t i = 0; i < a.size(); ++i) {
        if(a[i] != b[i]) return false;
    }
    return true;
}

bool operator<(const bign& a, const bign& b) {
    if(a.plus() != b.plus()) return b.plus();
    if(!a.plus()) return -b < -a;
    if(a.size() < b.size()) return true;
    else if(a.size() > b.size()) return false;
    for(int i = a.size() - 1; i >= 0; --i) {
        if(a[i] < b[i]) return true;
        else if(a[i] > b[i]) return false;
    }
    return false;
}

const bign gcd_bign(const bign& a, const bign& b) {
    if(a % b == 0) return b;
    else return gcd_bign(b, a % b);
}