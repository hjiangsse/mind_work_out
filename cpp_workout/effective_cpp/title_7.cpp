class TimeKeeper {
public:
    TimeKeeper() {}
    ~TimeKeeper() {}
};

class AtomicClock: public TimeKeeper {
};

class WaterClock: public TimeKeeper {
};

TimeKeeper * KepperFactory(int t) {
    if (t == 0) {
	AtomicClock *pAtomicClock = new AtomicClock();
	return pAtomicClock;
    }

    if (t == 1) {
	WaterClock *pWaterClock = new WaterClock();
	return pWaterClock;
    }

    return 0;
}

int main(int argc, char **argv) {
    TimeKeeper *pTmKp = KepperFactory(0);
    delete pTmKp;
    return 0;
}
