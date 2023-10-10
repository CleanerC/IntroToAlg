#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool legalBrackets(string line) {
    vector<char> brackets;

    for(auto& C : line) {
        switch (C) {
        case '{':
        case '(':
        case '[':
            brackets.push_back(C);
            break;
        case '}':
            if (brackets.empty() || brackets.back() != '{') {
                return false;
            }
            brackets.pop_back();
            break;
        case ')':
            if (brackets.empty() || brackets.back() != '(') {
                return false;
            }
            brackets.pop_back();
            break;
        case ']':
            if (brackets.empty() || brackets.back() != '[') {
                return false;
            }
            brackets.pop_back();
            break;
        }
    }
    return brackets.empty();
}

int main(int argc, char** argv) {
    string line = argv[1];
    
    cout << (legalBrackets(line) ? "legal" : "illegal") <<endl;

    return 0;
}

