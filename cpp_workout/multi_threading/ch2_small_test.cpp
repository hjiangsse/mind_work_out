#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <numeric>
#include <string>
#include <functional>

using namespace std;

int main() {
    cout << std::thread::hardware_concurrency() << endl;
    int arr[3] = {1, 2, 3};
    vector<int> m_vec(arr, arr + 3);

    vector<int>::iterator start = m_vec.begin();
    vector<int>::iterator end = m_vec.end();

    cout << std::accumulate(start, end, 0) << endl;
    return 0;
}
