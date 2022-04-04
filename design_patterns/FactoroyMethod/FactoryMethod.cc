#include <iostream>

/*
 * Abstract Product Class
 */
class Product {
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0; // "const" means this method will not change data members
                                               // this means that this method can be called on a const instance of the class
                                               // "= 0" tell that it is a pure function
};

class ConcreteProduct1: public Product {
public:
    std::string Operation() const override {
	return "{A message from ConcreteProduct 1}";
    }
};

class ConcreteProduct2: public Product {
public:
    std::string Operation() const override {
	return "{A message from ConcreteProduct 2}";
    }
};

/*
 * Abstract Creator Class
 */
class Creator {
public:
    virtual ~Creator() {}
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const {
	// call the factory method to create a Product object
	Product *product = this->FactoryMethod();
	// now, use the product
	std::string result = "Creator: the same creator's code has just worked with " + product->Operation();
	delete product;
	return result;
    }
};

class ConcreteCreator1: public Creator {
    Product* FactoryMethod() const override {
	return new ConcreteProduct1();
    }
};

class ConcreteCreator2: public Creator {
    Product* FactoryMethod() const override {
	return new ConcreteProduct2();
    }
};

int main() {
    Creator* creator1 = new ConcreteCreator1();
    std::cout << creator1->SomeOperation() << std::endl;
    Creator* creator2 = new ConcreteCreator2();
    std::cout << creator2->SomeOperation() << std::endl;

    delete creator1;
    delete creator2;
    return 0;
};
