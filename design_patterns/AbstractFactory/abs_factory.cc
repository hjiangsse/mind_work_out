#include <iostream>
#include "residence.h"
#include "vehicle.h"
#include "wife.h"

class CharacterCreate {
public:
    virtual Residence* ResidenceProduce() = 0;
    virtual Vehicle* VehicleProduce() = 0;
    virtual Wife* WifeProduce() = 0;
};

// v1: hut + tank + japanwife
class V1Create: public CharacterCreate {
    Residence* ResidenceProduce() {
	return new Hut();
    }

    Vehicle* VehicleProduce() {
	return new Tank();
    }

    Wife* WifeProduce() {
	return new JapanWife();
    }
};

// v2: villa + bicycle + chinawife
class V2Create: public CharacterCreate {
    Residence* ResidenceProduce() {
	return new Villa();
    }

    Vehicle* VehicleProduce() {
	return new Bicycle();
    }

    Wife* WifeProduce() {
	return new ChinaWife();
    }
};

// v3: villa + bicycle + russiawife
class V3Create: public CharacterCreate {
    Residence* ResidenceProduce() {
	return new Villa();
    }

    Vehicle* VehicleProduce() {
	return new Bicycle();
    }

    Wife* WifeProduce() {
	return new RussiaWife();
    }
};

void TellCharactorMessage(CharacterCreate *pCreator) {
    Residence* pResidence = pCreator->ResidenceProduce();
    Vehicle* pVehicle = pCreator->VehicleProduce();
    Wife* pWife = pCreator->WifeProduce();

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "The residence of this charactor is: " << pResidence->Tell_Appearance() << std::endl;
    std::cout << "His " << pVehicle->move_forward() << std::endl;
    std::cout << "His " << pVehicle->move_backward() << std::endl;
    std::cout << "His " << pVehicle->sudden_stop() << std::endl;
    std::cout << "His wife greeting is: " << pWife->Tell_Greeting() << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    
    delete pResidence;
    delete pVehicle;
    delete pWife;
}

int main() {
    V1Create* pV1 = new V1Create();
    TellCharactorMessage(pV1);

    V2Create* pV2 = new V2Create();
    TellCharactorMessage(pV2);

    V3Create* pV3 = new V3Create();
    TellCharactorMessage(pV3);

    delete pV1;
    delete pV2;
    delete pV3;
    return 0;
}
