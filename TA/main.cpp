#include<iostream>
#include<fstream>
#include<string>

#include"chomsky.hpp"

using namespace std;

char buffer[100];


int main() {
	vector<Rule> rules;
    string filename = "./in_local";
    auto check = parse_file(filename, rules);
    cout << check.message << '\n';
    if (!check.error) {
        for (auto i : rules)
            cout << i.make_string() << endl;
    }
}