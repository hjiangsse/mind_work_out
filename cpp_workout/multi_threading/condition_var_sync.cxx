#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

int count = 0;
std::mutex count_mutex;
std::condition_variable cv;

void producer(void) {
    for (int i = 0; i <= 10; i++) {
	std::unique_lock<std::mutex> lk(count_mutex);
	count = i;
	cv.notify_one();
	lk.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void consumer(void) {
    for (int i = 0; i < 10; i++) {
	std::unique_lock<std::mutex> lk(count_mutex);
	cv.wait(lk, [](){ return (count != 0);});
	
	if(count >= 10)
	    break;

	std::cout << count << "\n";
	count = 0;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    
    return 0;
}
