#include <string>

class Wife {
public:
    virtual ~Wife() {}
    virtual std::string Tell_Greeting() const = 0;
};

class JapanWife: public Wife {
    std::string Tell_Greeting() const {
	return "こんにちは";
    }
};

class ChinaWife: public Wife {
    std::string Tell_Greeting() const {
	return "你好";
    }
};

class RussiaWife: public Wife {
    std::string Tell_Greeting() const {
	return "Привет";
    }
};
