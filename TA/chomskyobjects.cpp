#ifndef CHOMSKYOBJECTS_CPP
#define CHOMSKYOBJECTS_CPP

#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct Node {
    string name;
    bool terminal;
    bool null;

    Node(string _name, bool _terminal) {
        name = _name;
        terminal = _terminal || name == "@";
        null = name == "@";
    }

    Node() {
        null = true;
    }

    Node(string _name) {
        name = _name;
        terminal = name[0] >= 'a';
        null = name == "@";
    }

    bool operator==(const Node &other) const {
        return other.name == name;
    }
};


struct Rule {
    Node start;
    vector<Node> end;

    Rule(Node _start, vector<Node> _end) {
        start = _start;
        end = _end;
    }

    Rule() {}

    string make_string(char delimeter = ',', bool all = true) {
        string res = all ? start.name + "->" : "";
        for (int i = 0; i < end.size(); i++) {
            res.append(end[i].name);
            if (i != end.size() - 1)
                res.push_back(delimeter);
        }
        return res;
    }

    bool terminal() {
        for (auto nod : end) {
            if (!nod.terminal)
                return false;
        }
        return true;
    }

    bool null() {
        if (end.size() == 1 && end[0].null)
            return true;
        return false;
    }

    vector<int> find_positions(const Node nod) {
        vector<int> res;
        for (int i = 0; i < end.size(); i++) {
            if (end[i] == nod)
                res.push_back(i);
        }
        return res;
    } 

    bool operator<(const Rule &other) {
        return start.name < other.start.name;
    }

    bool operator==(const Rule &other) {
        return start == other.start && end == other.end;
    }
};

#endif