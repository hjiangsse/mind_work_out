#include <string>

/*
 * Abstract product class: Residence
 */
class Residence {
public:
    virtual ~Residence() {}
    virtual std::string Tell_Appearance() const = 0;
};

/*
 * One concrete class of Residence: Hut
 */
class Hut: public Residence {
public:
    std::string Tell_Appearance() const {
	return "Simple and Crude";
    }
};

/*
 * One concrete class of Residence: Cottage
 */
class Cottage: public Residence {
public:
    std::string Tell_Appearance() const {
	return "Clean and Warm";
    }
};

/*
 * One concrete class of Residence: Villa
 */
class Villa: public Residence {
public:
    std::string Tell_Appearance() const {
	return "Empty and Luxury";
    }
};
