#ifndef FILEPARSER_CPP
#define FILEPARSER_CPP

#include<string>
#include<fstream>
#include<vector>

#include"errorhandler.cpp"
#include"chomskyobjects.cpp"

using namespace std;

vector<string> parse_line(string line, char delimeter) {
    vector<string> result;

    int defis = -1;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '-') {
            defis = i;
            break;
        }
    }
    if (defis == -1)
        return vector<string>();

    int arrow = -1;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '>') {
            arrow = i;
            break;
        }
    }
    if (arrow == -1 || arrow < defis)
        return vector<string>();
    
    result.push_back(line.substr(0, defis));
    if (!delimeter) {
        for (int i = arrow + 1; i < line.size(); i++) 
            result.push_back(line.substr(i, 1));
    } else {
        for (int li = arrow+1, ri = arrow+1; ri <= line.size();) {
            if (bool check = (ri == line.size()) || line[ri] == delimeter) {
                if (li < line.size()) 
                    result.push_back(line.substr(li, ri - li));
                while (ri < line.size() && line[ri] == delimeter)
                    ri++;
                li = ri;
                if (check)
                    break;
            }
            else ri++;
        }
    }

    return result;
}

ErrorHandler parse_file(string filename, vector<Rule> &rules, char delimeter = '\0') {
    ifstream fin(filename);
    if (!fin.is_open()) 
        return ErrorHandler("the file path is not correct", true);
    char buffer[100];
    while (!fin.eof()) {
        fin.getline(buffer, sizeof(buffer));
        vector<string> symbols = parse_line(string(buffer), delimeter);
        if (symbols.size() <= 1) 
            return ErrorHandler("error parsing rules", true);
        if (symbols[0][0] >= 'a')
            return ErrorHandler("starting symbol in a rule should be non-terminal", true);
        Node start(symbols[0], false);
        vector<Node> end;
        for (int i = 1; i < symbols.size(); i++)
            end.push_back(Node(symbols[i], symbols[i][0] >= 'a'));
        rules.push_back(Rule(start, end));
    }
    return ErrorHandler("-", false);
}

#endif