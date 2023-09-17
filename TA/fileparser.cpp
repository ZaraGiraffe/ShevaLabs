#ifndef FILEPARSER_CPP
#define FILEPARSER_CPP

#include<string>
#include<fstream>
#include<vector>

#include"errorhandler.cpp"
#include"chomskyobjects.cpp"

using namespace std;


ErrorHandler parse_words(string line, vector<Node> &nodes, char nodes_delimeter) {
    for (int r = 0, l = 0; r <= line.size(); r++) {
        if (r == line.size() || line[r] == nodes_delimeter) {
            if (l == r) 
                return ErrorHandler("Error near some delimeter", true);
            nodes.push_back(Node(line.substr(l, r - l)));
            l = r + 1;
        }
    } 
    return ErrorHandler("-", false);
}  


ErrorHandler parse_line(string line, vector<Rule> &rules, char rules_delimeter, char nodes_delimeter) {
    vector<string> result;

    int defis = -1;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '-') {
            defis = i;
            break;
        }
    }
    if (defis == -1)
        return ErrorHandler("Problem near the arrow", true);

    int arrow = -1;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '>') {
            arrow = i;
            break;
        }
    }
    if (arrow == -1 || arrow < defis)
        return ErrorHandler("Problem near the arrow", true);

    Node start = line.substr(0, defis);
    if (start.terminal) 
        return ErrorHandler("The start of the rule can not be terminal", true);
    
    vector<int> rules_pos = {arrow};
    for (int i = arrow + 1; i < line.size(); i++) {
        if (line[i] == rules_delimeter)
            rules_pos.push_back(i);
    }
    rules_pos.push_back(line.size());

    for (int i = 1; i < rules_pos.size(); i++) {
        int left = rules_pos[i - 1] + 1;
        int right = rules_pos[i];
        vector<Node> nodes;
        ErrorHandler ans = parse_words(line.substr(left, right - left), nodes, nodes_delimeter);
        if (ans.error)
            return ans;
        rules.push_back(Rule(start, nodes));
    }

    return ErrorHandler("-", false);
}

ErrorHandler parse_file(string filename, vector<Rule> &rules, char rules_delimeter = '|', char nodes_delimeter = ',') {
    ifstream fin(filename);
    if (!fin.is_open()) 
        return ErrorHandler("The file path is not correct", true);
    
    char buffer[100];
    while (!fin.eof()) {
        fin.getline(buffer, sizeof(buffer));
        ErrorHandler ans = parse_line(string(buffer), rules, rules_delimeter, nodes_delimeter);
        if (ans.error)
            return ans;
    }

    fin.close();
    return ErrorHandler("-", false);
}

#endif