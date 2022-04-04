#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int count = 0;
std::mutex count_mutex;

void producer(void) {
    for (int i = 0; i < 10; i++) {
	count_mutex.lock();
	if(!count)
	    count = i;
	count_mutex.unlock();
	std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

void consumer(void) {
    for (int i = 0; i < 10; i++) {
	count_mutex.lock();
	if(count)
	    std::cout << count << "\n";
	count = 0;
	count_mutex.unlock();
	std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    
    return 0;
}
