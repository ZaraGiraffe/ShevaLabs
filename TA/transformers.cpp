#ifndef TRANSFORMERS_CPP
#define TRANSFORMERS_CPP

#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

#include"chomskyobjects.cpp"


void normalize_rules(vector<Rule> &rules) {
    sort(rules.begin(), rules.end());
    rules.erase(unique(rules.begin(), rules.end()), rules.end());
}


void print_all_rules(string filename, vector<Rule> &rules, char rules_delimeter = '|', char nodes_delimeter = ',') {
    ofstream outstream(filename);
    for (int l = 0, r = 0; r <= rules.size(); r++) {
        if (r == rules.size() || rules[r].start.name != rules[l].start.name) {
            for (int i = l; i < r; i++) {
                if (i != l) 
                    outstream << rules_delimeter;
                outstream << rules[i].make_string(nodes_delimeter, i == l);
            }
            l = r;
            outstream << '\n';
        }
    }
    outstream.close();
}


void delete_null_rules(vector<Rule> &rules) {
    while (true) {
        Node nod;
        for (auto it = rules.begin(); it != rules.end(); it++) {
            if (it->null()) {
                nod = it->start;
                rules.erase(it);
                break;
            }
        }
        
        if (nod.null)
            break;
        
        int len = rules.size();
        for (int i = 0; i < len; i++) {
            vector<int> pos = rules[i].find_positions(nod);
            if (!pos.empty()) {
                for (auto position : pos) {
                    Rule new_rule = rules[i];
                    new_rule.end.erase(new_rule.end.begin() + position);
                    rules.push_back(new_rule);
                }
            }
        }
    }
    normalize_rules(rules);
}


#endif