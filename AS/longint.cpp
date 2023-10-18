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

    void normalize(vector<int>& mas) const {
        while (mas.size() > 1 && mas.back() == 0)
            mas.pop_back();
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

    vector<int> add(const vector<int>& u, const vector<int>& v) const {
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

    vector<int> sub(const vector<int>& u, const vector<int>& v) const {
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
        normalize(res);
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
        long_int b = other;
        b.sign ^= 1;
        return *this + b;
    }

    void operator+=(const long_int& other) {
        *this = *this + other;
    }

    void operator-=(const long_int& other) {
        *this = *this - other;
    }

    vector<int> mul(const vector<int>& a, const vector<int>& b) const {
        vector<int> res(a.size() + b.size());
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0, dop = 0; dop || j < b.size(); j++) {
                int bj = j < b.size() ? b[j] : 0;
                int suma = a[i] * bj + dop + res[i + j];
                res[i + j] = suma % BASE;
                dop = suma / BASE;
            }
        }
        normalize(res);
        return res;
    }

    long_int operator*(const long_int& other) const {
        long_int res;
        res.X = mul(X, other.X);
        res.sign = sign ^ other.sign;
        return res;
    }

    void operator*=(const long_int& other) {
        *this = *this * other;
    }

    vector<int> divide_2(vector<int> arr) const {
        vector<int> mas = arr;
        for (int i = mas.size() - 1, dop = 0; i >= 0; i--) {
            int now = dop * BASE + mas[i];
            dop = now & 1;
            mas[i] = now / 2;
        }
        normalize(mas);
        return mas;
    }

    vector<int> divide(const vector<int>& a, const vector<int>& b) const {
        vector<int> l = {0};
        vector<int> r = a;
        vector<int> one = {1};
        while (l != r) {
            vector<int> m = divide_2(add(add(l, r), one));
            if (less(a, mul(m, b)))
                r = sub(m, one);
            else 
                l = m;
        }
        return l;
    }

    long_int operator/(const long_int& other) const {
        if (!other) 
            return long_int(0);
        long_int res;
        res.X = divide(X, other.X);
        res.sign = sign ^ other.sign;
        return res;
    }

    void operator/=(const long_int& other) {
        *this = *this / other;
    }

    void vcout(vector<int> v) const {
    for (auto i : v) 
        cout << i << " ";
    cout << endl;
    }

    long_int operator%(const long_int& other) const {
        if (!other)
            return long_int(0);
        vector<int> arr = divide(X, other.X);
        arr = mul(arr, other.X);
        arr = sub(X, arr);
        long_int res(0);
        res.X = arr;
        if (!res)
            return res;
        if (sign)
            return other.abs() - res;
        else 
            return res;
    }

    void operator%=(const long_int& other) {
        *this = *this % other;
    } 

    long_int abs() const {
        long_int a = *this;
        a.sign = 0;
        return a;
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