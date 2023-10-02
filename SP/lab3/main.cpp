#include<string> 
#include<fstream>
#include<vector>
#include<set>
#include<iostream>

using namespace std;


#define PUNKT "Puntuation"
#define UNK "Unknown token"
#define MEMA "Member Access"
#define SPEC "Special token"
#define STR "String"
#define OBJ "User Object"
#define OPER "Operator"
#define PAT "Pattern"
#define COM "comment"


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



set<string> characters;

void init_characters(const char* filename) {
    ifstream file(filename);
    while (file.peek() != EOF)
        characters.insert(string(1, file.get()));
    file.close();
}

int is_character(const string& now) {
    return characters.find(now) == characters.end();
}



set<string> digits;

void init_digits(const char* filename) {
    ifstream file(filename);
    while (file.peek() != EOF)
        digits.insert(string(1, file.get()));
    file.close();
}

int is_digit(const string& now) {
    return digits.find(now) == digits.end();
}



vector<Lexem> build_lexems(const char* filename) {
    ifstream file(filename);
    vector<Lexem> lexems;

    string now = "";
    while (file.peek() != EOF) {
        now.push_back(file.get());

        if (is_space(now)) {
            cout << "in space" << endl;
        }

        else if (is_punctuation(now)) {
            cout << "in punkt" << endl;
            lexems.push_back(Lexem(now, PUNKT));
        }

        else if (now == ".") {
            cout << "in dot" << endl;
            while (file.peek() == '.' && now.size() < 3)
                now.push_back(file.get());
            switch (now.size()) {
                case 1:
                    lexems.push_back(Lexem(now, MEMA));
                    break;
                case 2:
                    lexems.push_back(Lexem(now, UNK));
                    break;
                case 3:
                    lexems.push_back(Lexem(now, SPEC));
            }

        }

        else if (now == "\"" || now == "'") {
            cout << "in string" << endl;
            while (file.peek() != EOF && file.peek() != now[0]) 
                now.push_back(file.get());
            file.get();
            lexems.push_back(Lexem(now.substr(1), STR));
        }

        else if (now == "/") {
            cout << "in div" << endl;
            if (file.peek() == '/') {
                cout << "\tin comm1" << endl;
                now.pop_back();
                while(file.peek() != EOF && file.peek() != '\n') 
                    now.push_back(file.get()); 
                lexems.push_back(Lexem(now, COM));
            } 
            else if (file.peek() == '*') {
                cout << "\tin comm2" << endl;
                now.pop_back();
                while (file.peek() != EOF) {
                    now.push_back(file.get());
                    if (now.size() >= 2 && now.substr(now.size()-2, 2) == "*/") {
                        now.pop_back(); now.pop_back();
                        break;
                    } 
                }
                lexems.push_back(Lexem(now, COM));
            }
            else if (!lexems.empty() && (lexems.back().name == ")" || lexems.back().name == "]" || lexems.back().type == OBJ)) {
                cout << "\tin oper" << endl;
                if (file.peek() == '=') 
                    now.push_back(file.get());
                lexems.push_back(Lexem(now, OPER));
            }
            else {
                cout << "\tin pattern" << endl;
                while (file.peek() != EOF && file.peek() != '/') 
                    now.push_back(file.get());
                if (is_character(string(1, file.peek())))
                    now.push_back(file.get());
                lexems.push_back(Lexem(now, PAT));
            }
        }



        now.clear();
    }

    file.close();
    return lexems;
}



void print_lexems(const char* filename, const vector<Lexem>& lexems, int in_row=2) {
    ofstream file(filename);
    for (int i = 0; i < lexems.size(); i++) {
        file << lexems[i].to_str();
        file << ((in_row == 0) || (i % in_row == 0) ? " " : "\n");
    }
    file.close();
}



void init_symbols() {
    init_punctuation("./punctuation.txt");
    init_characters("./characters.txt");
    init_digits("./digits.txt");
    init_spaces();
}



int main() {
    init_symbols();
    vector<Lexem> lexems = build_lexems("./local.js");
    cout << lexems.size() << endl;
    print_lexems("./out_local.js", lexems);
}