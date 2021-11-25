#include <string>
#include <iostream>
#include <vector>

#include "little_stack.h"
#include "little_matrix.h"
#include "little_iterator.h"

using namespace std;

void test_class();
void test_stack();
void test_metrix();
void test_iterator();

void print_string_vec(const string& vec_name, const vector<string>& vec);
int sum(const Iterator &iter);

int main(int argc, char **argv) {
    //test_stack();
    //test_metrix();
    test_iterator();
    return 0;
}

void test_iterator() {
    int nums[] = {1, 2, 3, 4};
    int nums_len = sizeof(nums) / sizeof(int);
    Iterator iter(nums, nums_len);
    cout << sum(iter) << endl;
    /*
    vector<int>& elem_ref = iter.get_elems();
    for(vector<int>::iterator it = elem_ref.begin(); it != elem_ref.end(); it++) {
        cout << *it << endl;
        *it = *it * 2;
    }

    for(vector<int>::iterator it = elem_ref.begin(); it != elem_ref.end(); it++) {
        cout << *it << endl;
    }
    */
}

int sum(const Iterator &iter) {
    if(!iter.length())
        return 0;

    int val = 0;
    int sum = 0;
    iter.next_reset();
    while(iter.next(val))
        sum += val;
    
    return sum;
}

void test_metrix() {
    Matrix m(4,4);
    m.set_item(0, 0, 10);
    m.set_item(3, 3, 11);
    Location start(0, 0);
    Location end(3,3);
    cout << m.get_view(start, end) << endl;

    /*
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << m.get_item(i, j) << endl;
        }
    }
    */
}

void test_stack() {
    Stack* pstack = new(Stack);
    cout << "The size when initialize: " << pstack->size() << endl;
    cout << "The snapshot when initialize: " << pstack->gen_snapshot() << endl;
    string pooh[4] = {"hjiang", "zhang", "jiang", "work"};
    for(int i = 0; i < 4; i++) {
        pstack->push(pooh[i]);
    }
    cout << "The snapshot after insert: " << pstack->gen_snapshot() << endl;
    string tmp;
    pstack->pop(tmp);
    cout << "The snapshot after pop: " << pstack->gen_snapshot() << endl;

    string value("shang");
    bool m_b = pstack->is_exist(value);
    if(m_b) {
        cout << value << " exist!" << endl;
    } else {
        cout << value << " not exist!" << endl;
    }
    free(pstack);
}

void test_class() {
    string pooh[4] = {"hjiang", "zhang", "jiang", "work"};
    for(int i = 0; i < 4; i++) {
        cout << pooh[i] << endl;
    }

    string dummy("dummy");
    vector<string> svec1(4);
    print_string_vec("svec1", svec1);

    vector<string> svec2(4, dummy);
    print_string_vec("svec2", svec2);

    vector<string> svec3(pooh, pooh + 4);
    print_string_vec("svec3", svec3);

    if(svec2 != svec3) {
        cout << "svec2 and svec3 not equal!" << endl;
    }
}

void print_string_vec(const string& vec_name, const vector<string>& vec) {
    cout << "---------" << vec_name << " begin" <<"-----------" << endl;
    for(vector<string>::const_iterator it = vec.begin(); it != vec.end(); it++) {
        cout << *it << endl;
    }
    cout << "---------" << vec_name << " end" << "------------" << endl;
}