#include <iostream>

/**
 * The interface of fly behavior, which is an abstact class
 */
class FlyBehavior {
public:
    virtual ~FlyBehavior() {};
    virtual void fly() = 0;
};

class FlyWithWings: public FlyBehavior {
public:
    void fly() {
	std::cout << "Yeah! I am flying with beautiful wings!" << std::endl;
    }
};

class FlyNoWay: public FlyBehavior {
public:
    void fly() {
	std::cout << "I believe i can not fly" << std::endl;
    }
};


/**
 * The interface of quack behavior, which is an abstact class
 */
class QuackBehavior {
public:
    virtual void quack() = 0;
    virtual ~QuackBehavior() {};
};

class Quack: public QuackBehavior {
public: 
    void quack() {
	std::cout << "Quack" << std::endl;
    }
};

class MuteQuack: public QuackBehavior {
public:
    void quack() {
	std::cout << "<<Silence>>" << std::endl;
    }
};

class Squeak: public QuackBehavior {
public:
    void quack() {
	std::cout << "Squeak" << std::endl;
    }
};

class Duck {
public:
    Duck(FlyBehavior *pFlyBehavior, QuackBehavior *pQuackBehavior)
	:flyBehavior(pFlyBehavior), quackBehavior(pQuackBehavior)
    {}

    ~Duck() {
	delete this->flyBehavior;
	delete this->quackBehavior;
    };

    void DoFly() {
	flyBehavior->fly();
    }

    void DoQuack() {
	quackBehavior->quack();
    }

    void Display() 
    {
	std::cout << "A stupid duck swim in my screem: " << std::endl;
	flyBehavior->fly();
	quackBehavior->quack();
    }

    void SetFly(FlyBehavior *pFlyBehavior) 
    {
	delete this->flyBehavior;
	this->flyBehavior = pFlyBehavior;
    }

    void SetQuack(QuackBehavior *pQuackBehavior)
    {
	delete this->quackBehavior;
	this->quackBehavior = pQuackBehavior;
    }
    
    void swim() {
	std::cout << "All duck swim in water!" << std::endl;
    }
private:
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;
};


int main(int argc, char **argv) {
    FlyBehavior *pFlyBehavior = new FlyWithWings();
    QuackBehavior *pQuackBehavior = new MuteQuack();
    Duck mallard(pFlyBehavior, pQuackBehavior);
    
    mallard.Display();

    return 0;
}
