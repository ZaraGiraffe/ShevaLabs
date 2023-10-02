#include<string> 
#include<fstream>
#include<vector>
#include<set>
#include<iostream>

using namespace std;


struct Lexem {
    string name = "";
    string type = "";

    Lexem() {}

    Lexem(string _name, string _type) {
        name = _name;
        type = _type;
    }

    string to_str() const {
        return "<" + name + ", " + type + ">";
    }
};



set<string> punctuations;

void init_punctuation(const char* filename) {
    ifstream punctuation_file(filename);
    while(punctuation_file.peek() != EOF) {
        char br = punctuation_file.get();
        punctuations.insert(string(1, br));
    }
    punctuation_file.close();
}

int is_punctuation(const string& now) {
    return punctuations.find(now) != punctuations.end();
}



set<string> spaces;

void init_spaces() {
    string sp = " \t\n";
    for (char ch : sp) 
        spaces.insert(string(1, ch));
}

int is_space(const string& now) {
    return spaces.find(now) != spaces.end();
}



vector<Lexem> build_lexems(const char* filename) {
    ifstream file(filename);
    vector<Lexem> lexems;

    string now = "";
    while (file.peek() != EOF) {
        now.push_back(file.get());

        if (is_space(now)) {
            now.clear();
        }

        else if (is_punctuation(now)) {
            lexems.push_back(Lexem(now, "Punctuation"));
            now.clear();
        }

        else if (now == ".") {
            while (file.peek() == '.' && now.size() < 3)
                now.push_back(file.get());
            switch (now.size()) {
                case 1:
                    lexems.push_back(Lexem(now, "Member Access"));
                    break;
                case 2:
                    lexems.push_back(Lexem(now, "Unknown token"));
                    break;
                case 3:
                    lexems.push_back(Lexem(now, "Special token"));
            }
        }

        else if (0) {

        }
    }

    file.close();
    return lexems;
}



void print_lexems(const char* filename, const vector<Lexem>& lexems, int in_row=5) {
    ofstream file(filename);
    for (int i = 0; i < lexems.size(); i++) {
        file << lexems[i].to_str();
        file << (in_row == 0) || (i % in_row) ? " " : "\n";
    }
    file.close();
}



void init_symbols() {
    init_punctuation("./punctuation.txt");
    init_spaces();
}



int main() {
    vector<Lexem> lexems = build_lexems("./local.js");
    cout << lexems.size() << endl;
    print_lexems("./out_local.js", lexems);
}