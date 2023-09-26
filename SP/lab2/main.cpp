#include<iostream> 
#include<fstream>
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


int main() {
    
}