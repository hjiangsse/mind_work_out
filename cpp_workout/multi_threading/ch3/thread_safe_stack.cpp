#include <iostream>
#include <stack>
#include <mutex>
#include <exception>
#include <memory>

struct empty_stack: std::exception {
    const char* what() const throw() {
	 return "GeeksforGeeks!! "
               "A Computer Science"
               " Portal For Geeks";
    }
};

template <typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other) {
	std::lock_guard<std::mutex> lock(other.m);
	data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value) {
	std::lock_guard<std::mutex> lock(m);
	data.push(new_value);
    }

    std::shared_ptr<T> pop() {
	std::lock_guard<std::mutex> lock(m);
	if(data.empty()) throw empty_stack();
	std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
	data.pop();
	return res;
    }

    void pop(T& value) {
	std::lock_guard<std::mutex> lock(m);
	if(data.empty()) throw empty_stack();
	value = data.top();
	data.pop();
    }

    bool empty() const {
	std::lock_guard<std::mutex> lock(m);
	return data.empty();
    }
};

int main(int argc, char **argv) {
    threadsafe_stack<int> ss;
    try
    {
	std::shared_ptr<int> p = ss.pop();
    }
    catch (std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }
}
