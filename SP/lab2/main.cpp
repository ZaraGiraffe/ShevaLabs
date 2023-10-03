#include<iostream> 
#include<fstream>
#include<set>

#include"./automata.cpp"

using namespace std;


FiniteAutomata automata_from_file(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Can't open the" << filename << endl;
        return FiniteAutomata();
    }
    FiniteAutomata fa;
    string start;
    file >> start;
    fa.make_start(start);
    int rules;
    file >> rules;
    for (int i = 0; i < rules; i++) {
        string prv, nxt, sym;
        file >> prv >> sym >> nxt;
        fa.add_rule(prv, sym[0], nxt);
    }
    int fin;
    file >> fin;
    for (int i = 0; i < fin; i++) {
        string name;
        file >> name;
        fa.mark_terminal(name);
    }
    file.close();
    return fa;
}


int nodes_dfs(Node* now, map<Node*, int>& used, set<Node*>& last, string& res) {
    if (last.find(now) != last.end()) 
        return 1;
    used[now] = 1;
    for (auto par : now->next) {
        char ch = par.first;
        Node* nxt = par.second;
        if (used.find(nxt) == used.end()) {
            res.push_back(ch);
            int out = nodes_dfs(nxt, used, last, res);
            if (out) 
                return 1;
            else 
                res.pop_back();
        }
    }
    return 0;
}


string find_string(FiniteAutomata& fa, string& w1, string& w2) {
    Node* first = fa.make_word(fa.start, w1);
    if (!first)
        return "";
    set<Node*> last;
    for (auto par : fa.nodes) {
        Node* val = par.second;
        Node* nod = fa.make_word(val, w2);
        if (nod && nod->terminal) 
            last.insert(val);
    }  
    if (last.empty())
        return "";
    map<Node*, int> used = map<Node*, int>();
    string res = "";
    int out = nodes_dfs(first, used, last, res);
    return out ? w1 + res + w2 : "";
}


int main() {
    const char* filename = "input_local.txt";
    FiniteAutomata fa = automata_from_file(filename);

    string w1 = "ac", w2 = "bc";
    string res = find_string(fa, w1, w2);
    cout << "answer{" << res << "}" << endl;
}