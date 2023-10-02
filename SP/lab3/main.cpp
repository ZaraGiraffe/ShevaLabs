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



set<string> punctuations;

void init_punctuation() {
    ifstream punctuation_file("./brackets");
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

        }
    }

    file.close();
    return lexems;
}


void init_symbols() {
    
}


int main() {

}