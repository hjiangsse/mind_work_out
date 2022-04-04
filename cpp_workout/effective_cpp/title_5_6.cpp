#include <string>

class Empty {
};

template <typename T>
class NamedObject {
public:
    /*
    NamedObject(const char *name, const T& value)
	:nameValue(name), objectValue(value)
    {
    }
    */

    NamedObject(std::string& name, const T& value)
	:nameValue(name), objectValue(value)
    {
    }
private:
    std::string &nameValue;
    T objectValue;
};

class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class HouseForSale: private Uncopyable {
public:
    HouseForSale() {}
    //HouseForSale(const HouseForSale&) = delete;
    //HouseForSale& operator=(const HouseForSale&) = delete; //disable copy assignment operator
private:
    //HouseForSale(const HouseForSale&); //disable copy constructor
    //HouseForSale& operator=(const HouseForSale&); //disable copy assignment operator
};

int main(int argc, char **argv) {
    /*
    std::string name1("Smallest prime number");
    std::string name2("Smallest prime number");
    NamedObject<int> no1(name1, 2);
    NamedObject<int> no2(name2, 3);
    no2 = no1;
    */
    HouseForSale h1;
    HouseForSale h2;
    h2 = h1;
    return 0;
}
