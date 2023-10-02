#include<string> 
#include<fstream>
#include<vector>
#include<set>
#include<iostream>

using namespace std;


#define PUNKT "Punctuation"
#define UNK "Unknown token"
#define MEMA "Member Access"
#define SPEC "Special token"
#define STR "String"
#define OBJ "User Object"
#define OPER "Operator"
#define PAT "Pattern"
#define COM "Comment"
#define NUM "Number"
#define KEYW "Keyword"


#define DEBUG 0


#if DEBUG
ofstream cdeb;
#endif


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


set<string> hexes;

int init_hexes(const char* filename) {
    ifstream file(filename);
    while (file.peek() != EOF)
        hexes.insert(string(1, file.get()));
}

int is_hex_digit(string digit) {
    return hexes.find(digit) != hexes.end();
}



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
    return characters.find(now) != characters.end();
}



set<string> keywords;

void init_keywords(const char* filename) {
    ifstream file(filename);
    string word;
    while (file >> word) 
        keywords.insert(word);
    file.close();
}

int is_keyword(const string& now) {
    return keywords.find(now) != keywords.end();
}



set<string> digits;

void init_digits(const char* filename) {
    ifstream file(filename);
    while (file.peek() != EOF)
        digits.insert(string(1, file.get()));
    file.close();
}

int is_digit(const string& now) {
    return digits.find(now) != digits.end();
}



set<string> operators;

void init_operators(const char* filename) {
    ifstream file(filename);
    while (file.peek() != EOF)
        operators.insert(string(1, file.get()));
    file.close();
}

int is_operator(const string& now) {
    return operators.find(now) != operators.end();
}



vector<Lexem> build_lexems(const char* filename) {
    ifstream file(filename);
    vector<Lexem> lexems;

    string now = "";
    while (file.peek() != EOF) {
        now.push_back(file.get());

        if (is_space(now)) {
            #if DEBUG
            cdeb << "in space" << endl;
            #endif
        }

        else if (is_punctuation(now)) {
            #if DEBUG
            cdeb << "in punkt" << endl;
            #endif
            lexems.push_back(Lexem(now, PUNKT));
        }

        else if (now == ".") {
            #if DEBUG
            cdeb << "in dot" << endl;
            #endif
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
            #if DEBUG
            cdeb << "in string" << endl;
            #endif
            while (file.peek() != EOF && file.peek() != now[0]) 
                now.push_back(file.get());
            file.get();
            lexems.push_back(Lexem(now.substr(1), STR));
        }

        else if (now == "/") {
            #if DEBUG
            cdeb << "in div" << endl;
            #endif
            if (file.peek() == '/') {
                #if DEBUG
                cdeb << "\tin comm1" << endl;
                #endif
                while(file.peek() != EOF && file.peek() != '\n') 
                    now.push_back(file.get()); 
                lexems.push_back(Lexem(now.substr(2), COM));
            } 
            else if (file.peek() == '*') {
                #if DEBUG
                cdeb << "\tint comm2" << endl;
                #endif
                now.push_back(file.get());
                while (file.peek() != EOF) {
                    now.push_back(file.get());
                    if (now.size() >= 4 && now.substr(now.size()-2, 2) == "*/") 
                        break;

                }
                lexems.push_back(Lexem(now.substr(2, now.size()-4), COM));
            }
            else if (!lexems.empty() && (lexems.back().name == ")" || 
                            lexems.back().name == "]" || lexems.back().type == OBJ || 
                            lexems.back().type == NUM)) {
                #if DEBUG
                cdeb << "\tin oper" << endl;
                #endif
                if (file.peek() == '=') 
                    now.push_back(file.get());
                lexems.push_back(Lexem(now, OPER));
            }
            else {
                #if DEBUG
                cdeb << "in pattern" << endl;
                #endif
                while (file.peek() != EOF && file.peek() != '/') 
                    now.push_back(file.get());
                now.push_back(file.get());
                if (is_character(string(1, file.peek())))
                    now.push_back(file.get());
                lexems.push_back(Lexem(now, PAT));
            }
        }

        else if (is_digit(now)) {
            #if DEBUG
            cdeb << "in digit" << endl;
            #endif
            if ((now == "0") && (file.peek() == 'x')) {
                #if DEBUG
                cdeb << "\t in hex" << endl;
                #endif
                now.push_back(file.get());
                while (is_hex_digit(string(1, file.peek())))
                    now.push_back(file.get());
                lexems.push_back(Lexem(now, NUM));
            }
            else {
                #if DEBUG
                cdeb << "\tin norm digit" << endl;
                #endif
                int point = 0;
                while (is_digit(string(1, file.peek())) || (!point && (file.peek() == '.'))) {
                    if (file.peek() == '.')
                        point = 1;
                    now.push_back(file.get());
                }
                lexems.push_back(Lexem(now, NUM));
            }
        }

        else if (is_character(now)) {
            #if DEBUG
            cdeb << "in char" << endl;
            #endif
            while (is_character(string(1, file.peek())) || is_digit(string(1, file.peek()))) 
                now.push_back(file.get());
            if (is_keyword(now)) 
                lexems.push_back(Lexem(now, KEYW));
            else lexems.push_back(Lexem(now, OBJ));
        }

        else if (is_operator(now)) {
            #if DEBUG
            cdeb << "in oper" << endl;
            #endif
            while (is_operator(string(1, file.peek())))
                now.push_back(file.get());
            if (now == "=>") 
                lexems.push_back(Lexem(now, SPEC));
            else if (is_operator(now))
                lexems.push_back(Lexem(now, OPER));
            else 
                lexems.push_back(Lexem(now, UNK));
        }

        else {
            #if DEBUG
            cdeb << "in else" << endl;
            #endif
            lexems.push_back(Lexem(now, UNK));
        }
        
        #if DEBUG
        cdeb << "end " << now << endl;
        #endif

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
    init_punctuation("./punctuations.txt");
    init_characters("./characters.txt");
    init_digits("./digits.txt");
    init_keywords("./keywords.txt");
    init_spaces();
    init_hexes("./hexdigits.txt");
    init_operators("./operators.txt");
}



int main() {
    #if DEBUG 
    cdeb.open("./debug_local.txt");
    #endif

    init_symbols();
    vector<Lexem> lexems = build_lexems("./local.js");
    print_lexems("./out_local.txt", lexems);

    #if DEBUG 
    cdeb << "size: " << lexems.size() << endl;
    #endif
}