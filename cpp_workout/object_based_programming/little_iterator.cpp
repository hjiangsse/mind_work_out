#include "little_iterator.h"

vector<int> Iterator::_elems;

int Iterator::elem(int pos) const {
    return _elems[pos];
}

bool Iterator::next(int &val) const {
    if(_next < _beg_pos + _length - 1) {
        val = _elems[++_next];
        return true;
    }
    return false;
}