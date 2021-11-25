#include <string>
#include <iostream>

using namespace std;

class Location {
public:
    Location(unsigned int i = 0, unsigned int j = 0) 
        :x(i), y(j)
    {
    }

    inline unsigned int get_row_index() const { return x; }
    inline unsigned int get_col_index() const { return y; }
private:
    unsigned int x, y;
};

class Matrix {
public:
    Matrix(unsigned int nrow = 0,unsigned int ncol = 0)
        :_nrow(nrow), _ncol(ncol) 
    {
        _pmat = (int *)malloc((_nrow * _ncol) * sizeof(int));

        for(int i = 0; i < _nrow; i++) {
            for(int j = 0; j < _ncol; j++) {
                int *pos = _pmat + i * _nrow + j;
                *pos = 0;
            }
        }
    }

    ~Matrix() {
        free(_pmat);
    }

    bool set_item(unsigned int i, unsigned int j, int val);
    int get_item(unsigned int i, unsigned int j);
    string get_view(const Location& start, const Location& end);
private:
    bool check_location(const Location& loc);
    unsigned int _nrow, _ncol;
    int *_pmat;
};