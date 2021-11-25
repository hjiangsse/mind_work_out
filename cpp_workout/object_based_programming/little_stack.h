#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Stack{
public:
    bool push(const string&);
    bool pop(string &elem);
    bool peek(string &elem);
    string gen_snapshot();        //快照生成
    
    bool is_exist(string &elem);

    bool empty();
    bool full();
    int size() { return _stack.size(); }
private:
    vector<string> _stack;
};

inline bool
Stack::empty() {
    return _stack.empty();
}

inline bool
Stack::full() {
    return _stack.size() == _stack.max_size();
}

inline bool
Stack::is_exist(string &elem) {
    return find(_stack.begin(), _stack.end(), elem) != _stack.end();
}
