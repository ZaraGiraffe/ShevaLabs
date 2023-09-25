#ifndef LONGINT_CPP
#define LONGINT_CPP

#include<vector>
#include<string>

#define BASE 1000
#define LENGTH 3

using namespace std;


struct long_int {
    vector<int> X;
    int sign;

    long_int() {
        X = {0};
        sign = 0;
    }

    long_int(int num) {
        if (num == 0) {
            X = {0};
            sign = 0;
            return;
        }
        sign = 0;
        if (num < 0) {
            sign = 1;
            num = -num;
        }
        while (num > 0) {
            X.push_back(num % BASE);
            num /= BASE;
        }
    }

    void normilize() {
        while (X.size() > 1 && X.back() == 0)
            X.pop_back();
    }

    static bool equal(const vector<int>& a, const vector<int>& b) {
        if (a.size() != b.size()) 
            return false;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) 
                return false;
        }
        return true;
    }

    bool operator==(const long_int& other) const {
        if (sign != other.sign) 
            return false;
        return equal(X, other.X);
    }

    bool operator!=(const long_int& other) const {
        return !(*this == other);
    }

    static bool less(const vector<int> a, const vector<int> b) {
        if (a.size() < b.size()) 
            return true;
        if (a.size() > b.size()) 
            return false;
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] > b[i])
                return false;
            if (a[i] < b[i])
                return true;    
        }
        return false;
    } 

    bool operator<(const long_int& other) const {
        if (sign && !other.sign)
            return true;
        if (!sign && other.sign)
            return false;
        if (*this == other) 
            return false;
        int les = less(this->X, other.X);
        return les ^ sign;
    }

    bool operator>(const long_int& other) const {
        return *this < other;
    }

    bool operator<=(const long_int& other) const {
        return *this == other || *this < other;
    }

    bool operator>=(const long_int& other) const {
        return *this == other || *this > other;
    }

    operator bool() const {
        return X.size() == 1 && X[0] == 0 ? false : true;
    }

    bool operator!() const {
        return X.size() == 1 && X[0] == 0 ? true : false;
    }

    static vector<int> add(const vector<int>& u, const vector<int>& v) {
        vector<int> res;
        for (int i = 0, dop = 0; i < max(v.size(), u.size()) || dop; i++) {
            int u1 = i < u.size() ? u[i] : 0;
            int v1 = i < v.size() ? v[i] : 0;
            int now = dop + u1 + v1;
            if (now >= BASE) {
                now -= BASE;
                dop = 1;
            }
            else 
                dop = 0;
            res.push_back(now);
        }
        return res;
    }

    static vector<int> sub(const vector<int>& u, const vector<int>& v) {
        vector<int> res;
        for (int i = 0, dop = 0; i < u.size(); i++) {
            int v1 = i < v.size() ? v[i] : 0;
            int now = u[i] - v1 - dop;
            if (now < 0) {
                dop = 1;
                now += BASE;
            }
            else 
                dop = 0;
            res.push_back(now);
        }
        while (res.size() > 1 && res.back() == 0) 
            res.pop_back();
        return res;
    }

    long_int operator+(const long_int& other) const {
        long_int now;
        if (sign == other.sign) {
            now.X = add(X, other.X);
            now.sign = sign;
        }
        else {
            if (equal(X, other.X)) 
                return long_int();
            int les = less(other.X, X);
            now.X = les ? sub(X, other.X) : sub(other.X, X);
            now.sign = 1 ^ les ^ sign;
        }
        return now;
    }

    long_int operator-(const long_int& other) const {
        long_int b = const_cast<long_int&>(other);
        b.sign ^= 1;
        return *this + b;
    }

    void operator+=(const long_int& other) {
        *this = *this + other;
    }

    void operator-=(const long_int& other) {
        *this = *this - other;
    }
    
    string str() const {
        string res;
        if (sign) 
            res.push_back('-');
        for (int i = X.size() - 1; i >= 0; i--) {
            string now = to_string(X[i]);
            if (i != X.size() - 1 && now.size() != LENGTH)
                now = string(LENGTH - now.size(), '0') + now;
            res += now;
        }
        return res;
    }
};

#endif