#include <string>
#include <thread>
#include <mutex>
#include <iostream>

class SomeData {
    int a;
    std::string b;
public:
    void do_something() {
	std::cout << "Do some workout" << std::endl;
    }
};

class DataWrapper {
private:
    SomeData data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function fn) {
	std::lock_guard<std::mutex> lock(m);
	fn(data);
    }
};

SomeData *unprotected;

void mal_func(SomeData& protected_data) {
    unprotected = &protected_data;
}

int main(int argc, char **argv) {
    DataWrapper x;
    x.process_data(mal_func);
    unprotected->do_something();
}
