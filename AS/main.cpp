#include<vector> 
#include<iostream>

#include"longint.cpp"

using namespace std;

int main() {
    long_int a(12), b(-12);
    cout << (a + b).str() << endl;
}

