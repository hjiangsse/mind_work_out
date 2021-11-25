#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void fly(int num) {
	std::cout << "This is the " << num << "th pig flying in the sky" << endl; 
}

int main() {
	std::vector<std::thread> m_threads;
	for(int i = 0; i < 10; i++) {
		std::thread t(fly, i);
		m_threads.push_back(t);
	}
	
	for(std::vector<std::thread>::iterator it = m_threads.begin(); it != m_threads.end(); it++) {
		(*it).join();
	}
	
	std::cout << "After threads finish!" << endl;
	return 0;
}