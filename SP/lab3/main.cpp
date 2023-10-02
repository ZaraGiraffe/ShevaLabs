#include<string> 
#include<fstream>
#include<vector>
#include<set>

using namespace std;


struct Lexem {
    string name = "";
    string type = "";

    Lexem() {}

    Lexem(string _name, string _type) {
        name = _name;
        type = _type;
    }

    string to_str() {
        return "<" + name + ", " + type + ">";
    }
};



set<string> brackets;

void init_brackets() {
    ifstream bracket_file("./brackets");
    while(bracket_file.peek() != EOF) {
        char br = bracket_file.get();
        brackets.insert(string(1, br));
    }
    bracket_file.close();
}

int is_bracket(const string& now) {
    return brackets.find(now) != brackets.end();
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

        else if (is_bracket(now)) {

        }
    }

    file.close();
    return lexems;
}


void init_symbols() {
    
}


int main() {
    
}