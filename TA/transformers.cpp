#ifndef TRANSFORMERS_CPP
#define TRANSFORMERS_CPP

#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

#include"chomskyobjects.cpp"
#include"generator.cpp"


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
            if (r != rules.size())
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

Rule transform_rule(Rule rule, vector<Node> p, Node new_node) {
    vector<Node> vec;
    for (int i = 0; i < rule.end.size(); i++) {
        if (i < rule.end.size() - 1 && rule.end[i] == p[0] && rule.end[i + 1] == p[1]) {
            vec.push_back(new_node);
            i++;
        }
        else 
            vec.push_back(rule.end[i]);
    }
    return Rule(rule.start, vec);
}

void make_rules_smaller(vector<Rule> &rules, NodesGenerator &generator) {
    while (true) {
        int ind = -1;
        for (int i = 0; i < rules.size(); i++) {
            if (rules[i].end.size() > 2) {
                ind = i; 
                break; 
            }
        }
        if (ind == -1)
            break;
        
        int rsize = rules[ind].end.size();
        vector<Node> p = {rules[ind].end[rsize-2], rules[ind].end[rsize-1]};
        Node new_node = generator.generate();

        while (true) {
            ind = -1;
            for (int i = 0; i < rules.size(); i++) {
                if (rules[i].end.size() > 2 && rules[i].contain_two_nodes(p)) {
                    ind = i;
                    break;
                }
            }
            if (ind == -1)
                break;
            
            Rule changed_old_rule = transform_rule(rules[ind], p, new_node);
            Rule new_rule(new_node, p);
            rules.erase(rules.begin() + ind);
            rules.push_back(changed_old_rule);
            rules.push_back(new_rule);
        }
    }

    normalize_rules(rules);
}

Rule update_rule(Rule &rule, Node old_node, Node new_node) {
    vector<Node> new_end;
    for (int i = 0; i < rule.end.size(); i++) {
        if (rule.end[i] == old_node)
            new_end.push_back(new_node);
        else 
            new_end.push_back(rule.end[i]);
    }
    return Rule(rule.start, new_end);
}

void update_small_rules(vector<Rule> &rules, NodesGenerator &generator) {
    while (true) {
        Node term("@");
        for (auto rule : rules) {
            if (rule.end.size() == 2) {
                if (rule.end[0].terminal) {
                    term = rule.end[0];
                    break;
                }
                else if (rule.end[1].terminal) {
                    term = rule.end[1];
                    break;
                }
            } 
        }
        if (term.null) 
            break;
        
        Node new_node = generator.generate();
        while (true) {
            int ind = -1;
            for (int i = 0; i < rules.size(); i++) {
                if (rules[i].end.size() > 1 && rules[i].contain_node(term)) {
                    ind = i;
                    break;
                }
            }
            if (ind == -1)
                break;

            Rule new_rule = update_rule(rules[ind], term, new_node);
            rules.erase(rules.begin() + ind);
            rules.push_back(new_rule);
            vector<Node> small_end = {term};
            rules.push_back(Rule(new_node, small_end));
        }
    }

    normalize_rules(rules);
}

void chomsky_normal_form(vector<Rule> &rules) {
    NodesGenerator generator(rules);
    make_rules_smaller(rules, generator);
    update_small_rules(rules, generator);
}


#endif