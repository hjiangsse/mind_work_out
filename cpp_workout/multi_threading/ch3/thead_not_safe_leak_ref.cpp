/*******************************************************************************
 * 泄露的指针或者引用导致并发不再安全
 *******************************************************************************/
#include <iostream>
#include <mutex>

class some_data {
public:
    some_data(int a, std::string b):
	a(a), b(b)
    {}
    void show() { std::cout << a << " " << b << std::endl; }
private:
    int a;
    std::string b;
};

class data_wrapper {
public:
    data_wrapper(some_data dt)
        :data(dt) {
    }
    
    template<typename Function>
    void process_data(Function func) {
	std::lock_guard<std::mutex> l(mu);
	func(data);
    }
private:
    some_data data;
    std::mutex mu;
};

some_data* unprotected;
void mal_func(some_data& protected_data) {
    unprotected = &protected_data;
}

int main(int argc, char **argv) {
    data_wrapper x(some_data(1, "hjiang"));
    x.process_data(mal_func);
    unprotected->show();
    return 0;
}
