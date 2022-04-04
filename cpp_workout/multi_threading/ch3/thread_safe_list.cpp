#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>

template <typename T>
class SafeList {
public:
    void add_to_list(T new_value);
    bool list_contains(T value_to_find);
private:
    std::list<T> internal_list;
    std::mutex mu;
};

template <typename T>
void SafeList<T>::add_to_list(T new_value) {
    std::lock_guard<std::mutex> guard(mu);
    internal_list.push_back(new_value);
}

template <typename T>
bool SafeList<T>::list_contains(T value_to_find) {
    std::lock_guard<std::mutex> guard(mu);
    return std::find(internal_list.begin(), internal_list.end(), value_to_find) !=
	internal_list.end();
}

int main(int argc, char **argv) {
    SafeList<int> sflist;
    sflist.add_to_list(10);
    sflist.add_to_list(20);
    sflist.add_to_list(30);
    if (sflist.list_contains(20)) 
	std::cout << "Find " << 20 << " in list!" << std::endl;
    return 0;
}
