#include "little_stack.h"

bool
Stack::push(const string& elem) {
    if(full())
        return false;
    
    _stack.push_back(elem);
    return true;
}

bool
Stack::pop(string &elem) {
    if(empty())
        return false;
    
    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool
Stack::peek(string &elem) {
    if(empty())
        return false;
    
    elem = _stack.back();
    return true;
}

string
Stack::gen_snapshot() {
    string tmp;
    
    if(empty()) {
        return "||";
    }

    tmp += "|";
    for(vector<string>::iterator it = _stack.begin(); it != _stack.end(); it++) {
        tmp += *it + "|";
    }
    
    return tmp;
}