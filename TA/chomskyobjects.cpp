#ifndef CHOMSKYOBJECTS_CPP
#define CHOMSKYOBJECTS_CPP

#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct Node {
    string name;
    bool is_terminal;

    Node(string _name, bool terminal) {
        name = _name;
        is_terminal = terminal;
    }

    Node() {}

};


struct Rule {
    Node start;
    vector<Node> end;
    vector<Node> unique_end;
    bool isnt_recursive;

    Rule(Node _start, vector<Node> _end) {
        start = _start;
        end = _end;

        auto comp = [] (const Node a, const Node b) {return a.name < b.name;};
        unique_end = _end;
        sort(unique_end.begin(), unique_end.end(), comp);
        unique_end.erase(unique(unique_end.begin(), unique_end.end(), comp), unique_end.end());

        isnt_recursive = true;
        for (auto node : unique_end) {
            if (!node.is_terminal) {
                isnt_recursive = false;
                break;
            }
        }
    }

    Rule() {}

    string make_string(string delimeter = "") {
        string res = start.name;
        res.append("->");
        for (int i = 0; i < end.size(); i++) {
            res.append(end[i].name);
            if (i != end.size() - 1)
                res.append(delimeter);
        }
        return res;
    }

};

#endif