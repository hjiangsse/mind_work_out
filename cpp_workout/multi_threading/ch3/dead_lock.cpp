#include <iostream>
#include <mutex>

using namespace std;

class BigObject {
public:
    BigObject(int val)
	:bigval(val)
    {}
    void set_val(int val) { bigval = val; }
    int get_val() { return bigval; }
private:
    int bigval;
};

void swap(BigObject& lhs, BigObject& rhs) {
    int temp = 0;
    temp = lhs.get_val();
    lhs.set_val(rhs.get_val());
    rhs.set_val(temp);
}

class BigObjectWrapper {
public:
    BigObjectWrapper(BigObject const &n_obj):obj(n_obj) {}
    BigObject& get_big_object() { return obj; }
    
    friend void swap(BigObjectWrapper& lhs, BigObjectWrapper& rhs) {
	if(&lhs == &rhs) 
	    return;
	std::lock(lhs.m, rhs.m);
	std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
	swap(lhs.obj, rhs.obj);
    }
private:
    BigObject obj;
    std::mutex m;
};

int main(int argc, char **argv) {
    BigObject b1(12);
    BigObject b2(14);

    cout << "Before swap: " << endl;
    cout << "b1: " << b1.get_val() << endl;
    cout << "b2: " << b2.get_val() << endl;

    swap(b1, b2);

    cout << "After swap: " << endl;
    cout << "b1: " << b1.get_val() << endl;
    cout << "b2: " << b2.get_val() << endl;

    BigObjectWrapper wrap1(b1);
    BigObjectWrapper wrap2(b2);

    swap(wrap1, wrap2);
    
    cout << "b1: " << wrap1.get_big_object().get_val() << endl;
    cout << "b2: " << wrap2.get_big_object().get_val() << endl;
    return 0;
}
