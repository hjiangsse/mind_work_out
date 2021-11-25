#include "little_matrix.h"

bool Matrix::set_item(unsigned int i, unsigned int j, int val) {
    if((i > (_nrow - 1)) || (j > (_ncol - 1)))
        return false;
    
    int *pos = _pmat + (_ncol * i + j);
    *pos = val;
    return true;
}

int Matrix::get_item(unsigned int i, unsigned int j) {
    int *pos = _pmat + (_ncol * i + j);
    return *pos;
}

bool Matrix::check_location(const Location& loc) {
    if (loc.get_row_index() > (_nrow - 1))
        return false;
    if (loc.get_col_index() > (_ncol - 1))
        return false;
    return true;
}

string Matrix::get_view(const Location& start, const Location& end) {
    string res = "";
    if(!check_location(start) || !check_location(end))
        return res;

    for(int i = start.get_row_index(); i <= end.get_row_index(); i++) {
        for(int j = start.get_col_index(); j <= end.get_col_index(); j++) {
            res += std::to_string(get_item(i, j)) + "|";
        }
        res += "\n";
    }

    return res;
}

