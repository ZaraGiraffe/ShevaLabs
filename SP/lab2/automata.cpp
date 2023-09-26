#ifndef AUTOMATA_CPP
#define AUTOMATA_CPP


#include<map> 
#include<string>
#include<vector>
#include<iostream>

using namespace std;


struct Node {
    map<char, Node*> next = map<char, Node*>();
    int terminal = 0;
    string name = "-";

    Node() {}

    Node(string _name, int _terminal) {
        name = _name;
        terminal = _terminal;
    }


};


struct FiniteAutomata {
    map<string, Node*> nodes = map<string, Node*>();
    Node* start = nullptr;

    FiniteAutomata() {}

    void create_node(string name) {
        Node* nod = new Node(name, 0);
        nodes[name] = nod;
    }

    void add_rule(string prv, char sym, string nxt) {
        if (nodes.find(prv) == nodes.end()) 
            create_node(prv);
        if (nodes.find(nxt) == nodes.end())
            create_node(nxt);
        nodes[prv]->next[sym] = nodes[nxt];
    }
    
    void mark_terminal(string name) {
        if (nodes.find(name) != nodes.end())
            nodes[name]->terminal = 1;
    }

    Node* make_word(Node* nod, string s) {
        for (int i = 0; i < s.size(); i++) {
            if (nod->next.find(s[i]) == nod->next.end()) 
                return nullptr;
            nod = nod->next[s[i]];
        }
        return nod; 
    }

    void make_start(string name) {
        if (nodes.find(name) == nodes.end())
            create_node(name);
        start = nodes[name];
    }
};


#endif