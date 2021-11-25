#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cassert>

using namespace std;

void do_something() {
    std::cout << "Do something fun!" << std::endl;
}

void do_something_else() {
    std::cout << "Do something meaningful!" << std::endl;
}

class backgroud_task {
public:
    void operator() () const {
	do_something();
	do_something_else();
    }
};

class LessThan {
public:
    LessThan(int val): _val(val) {}
    int comp_val() const { return _val; }    //read basic
    void comp_val(int nval) { _val = nval; } //write basic

    bool operator() (int _value) const;
private:
    int _val;
};

inline bool LessThan::operator() (int _value) const {
    return _value < _val;
}

int count_less_than(const vector<int> &vec, int comp) {
    LessThan lt(comp);

    int count = 0;
    for(int ix = 0; ix < vec.size(); ++ix) {
	if(lt(vec[ix])) {
	    ++count;
	}
    }
    return count;
}

struct func {
    int& i;
    func(int& _i):i(_i) {}
    void operator()() {
	/*
	for(unsigned int j = 0; j < 100; j++) {
	    do_something();
	}
        */
	std::cout << std::this_thread::get_id() << std::endl;
    }
};

class thread_guard {
public:
    explicit thread_guard(std::thread& t_):
	t(t_)
    {}
    ~thread_guard() {
	if(t.joinable()) {
	    t.join();
	}
    }

    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
private:
    std::thread& t;
};

int main() {
    int some_local_state = 0;
    func my_func(some_local_state);

    std::thread my_thread1(my_func);
    std::thread my_thread2(my_func);
    my_thread1.join();
    my_thread2.join();
    
    //thread_guard g(my_thread);
    
    //my_thread.detach();
    //backgroud_task f;
    //std::thread my_thread{backgroud_task()};
    /*
    std::thread my_thread([] {
	do_something();
	do_something_else();
    });
    */
    //my_thread.join();

    /*
    int ia[16] = { 17, 12, 44, 9, 18, 45, 6, 14,
	23, 67, 9, 0, 27, 55, 8, 16 };
    vector<int> vec(ia, ia+16);
    int comp_val = 20;

    cout << "Number of elements less than "
	 << comp_val << " are "
	 << count_less_than(vec, comp_val) << endl;
    */
    return 0;
}
