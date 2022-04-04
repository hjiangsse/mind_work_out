#include <iostream>

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

/*
 * Abstract Factory class
 */
class VehicleFactory {
public:
    virtual ~VehicleFactory() {}
    virtual Vehicle* CreateVehicle() const = 0;
};

/*
 * Concrete Factory to produce automobiles
 */
class AutomobileFactory: public VehicleFactory {
public:
    Vehicle* CreateVehicle() const {
	return new Automobile();
    }
};

/*
 * Concrete Factory to produce bicycles
 */
class BicycleFactory: public VehicleFactory {
public:
    Vehicle* CreateVehicle() const {
	return new Bicycle();
    }
};

/*
 * Concrete Factory to produce tanks
 */
class TankFactory: public VehicleFactory {
public:
    Vehicle* CreateVehicle() const {
	return new Tank();
    }
};

int main() {
    VehicleFactory* tank_factory = new TankFactory();
    Vehicle* tank = tank_factory->CreateVehicle();
    std::cout << tank->move_forward() << std::endl;
    std::cout << tank->move_backward() << std::endl;
    std::cout << tank->sudden_stop() << std::endl;
    delete tank_factory;
    delete tank;

    VehicleFactory* bicycle_factory = new BicycleFactory();
    Vehicle* tank = tank_factory->CreateVehicle();
    std::cout << tank->move_forward() << std::endl;
    std::cout << tank->move_backward() << std::endl;
    std::cout << tank->sudden_stop() << std::endl;
    delete tank_factory;
    delete tank;

    return 0;
}
