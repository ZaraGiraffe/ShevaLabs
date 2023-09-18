#ifndef GENERATOR_CPP
#define GENERATOR_CPP

#include<vector>
#include<set>
#include<string>

using namespace std;

typedef long long ll;

#include"chomskyobjects.cpp"


struct NodesGenerator {
    set<int> idx;

    NodesGenerator(vector<Rule> &rules) {
        for (auto rule : rules) {
            idx.insert(nodeToIndex(rule.start));
            for (auto node : rule.end) {
                if (!node.terminal)
                idx.insert(nodeToIndex(node));
            }
        }
    }

    NodesGenerator() {}

    int nodeToIndex(Node nod) {
        string name = nod.name;
        ll num = 0;
        for (int i = name.size() - 1; i >= 0; i--) {
            if (i) 
                num = 10ll * num + (name[i] - '0');
            else 
                num = 26ll * num + (name[i] - 'A');
        }
        return num;
    }

    Node indexToNode(int index) {
        string res = "";
        res.push_back('A' + (index % 26));
        index /= 26;
        if (index)
            res += to_string(index);
        return Node(res);
    }

    int mex() {
        auto it = idx.begin();
        for (int i = 0; it != idx.end(); i++, it++) {
            if (i != *it) 
                return i;
        }
        return idx.size();
    }

    Node generate() {
        int index = mex();
        idx.insert(index);
        return indexToNode(index);
    }
};



#endif