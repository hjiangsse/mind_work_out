#include <vector>

using namespace std;

class Iterator {
public:
    Iterator(int *elems, int len) {
        for(int i = 0; i < len; i++) {
            _elems.push_back(elems[i]);
        }

        _length = len;
        _beg_pos = 0;
        _next = _beg_pos - 1;
    }

    int length() const { return _length; }
    int begin_pos() const { return _beg_pos; }
    int elem(int pos) const;

    bool next (int &val) const;
    void next_reset() const { _next = _beg_pos - 1; }

    vector<int>& get_elems() { return _elems; }
private:
    int _length;
    int _beg_pos;
    mutable int _next;

    static vector<int> _elems;
};