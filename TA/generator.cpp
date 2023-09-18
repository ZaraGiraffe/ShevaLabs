#ifndef GENERATOR_CPP
#define GENERATOR_CPP

#include<vector>
#include<set>

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
        while (index >= 26) {
            res.push_back('0' + (index % 10));
            index /= 10;
        }
        res.push_back('A' + index);
        reverse(res.begin(), res.end());
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