#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

#include"chomsky.hpp"

using namespace std;


int main() {
	vector<Rule> rules;
    string infilename = "./in_local_dz";
    auto check = parse_file(infilename, rules);
    cout << check.message << '\n';

    if (!check.error) {
        string outfile1 = "./middle_local";
        string outfile2 = "./final_local";

        delete_null_rules(rules);
        print_all_rules(outfile1, rules);

        chomsky_normal_form(rules);
        print_all_rules(outfile2, rules);
    }
}