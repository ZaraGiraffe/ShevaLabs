#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

#include"chomsky.hpp"

using namespace std;

char buffer[100];


int main() {
	vector<Rule> rules;
    string infilename = "./in_local";
    auto check = parse_file(infilename, rules);
    cout << check.message << '\n';

    if (!check.error) {
        string outfilename = "./out_local";
        //ofstream outstream(outfilename);

        delete_null_rules(rules);
        //sort(rules.begin(), rules.end());
        print_all_rules(outfilename, rules);
        

        //for (auto i : rules)
        //    outstream << i.make_string(',') << endl;
    }
}