#include<string> 

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
        return "<" + name + " ," + type + ">";
    }
};


int main() {

}