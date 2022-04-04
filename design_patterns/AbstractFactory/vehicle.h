#include <string.h>

/*
 * Abstract product, just define some interfaces
 */
class Vehicle {
public:
    virtual ~Vehicle() {}
    virtual std::string move_forward() const = 0;
    virtual std::string move_backward() const = 0;
    virtual std::string sudden_stop() const = 0;
};

/*
 * Concrete product 1, automobile
 */
class Automobile: public Vehicle {
public:
    std::string move_forward() const override {
	return "automobile: move forward.";
    }

    std::string move_backward() const override {
	return "automobile: move backward.";
    }
    
    std::string sudden_stop() const override {
	return "automobile: sudden stop.";
    }
};

/*
 * Concrete product 2, bicycle
 */
class Bicycle: public Vehicle {
public:
    std::string move_forward() const override {
	return "bicycle: move forward.";
    }
    
    std::string move_backward() const override {
	return "bicycle: can not move backward. dangerous";
    }
    
    std::string sudden_stop() const override {
	return "bicycle: sudden stop.";
    }
};

/*
 * Concrete product 3, tank to fire against enemy
 */
class Tank: public Vehicle {
public:
    std::string move_forward() const override {
	return "tank: move forward.";
    }

    std::string move_backward() const override {
	return "tank: move backward.";
    }
    
    std::string sudden_stop() const override {
	return "tank: sudden stop.";
    }
};
