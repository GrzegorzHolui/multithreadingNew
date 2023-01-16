#include "../include/Fork.h"

Fork::Fork() : busy(false) {}

bool Fork::isBusy() const {
    return busy;
}


void Fork::setBusy(bool busy, int philosopherID) {
    if (!busy) {
        std::unique_lock<std::mutex> l(forkToLock);
        this->philosopherID = -1;
        this->busy = busy;
        l.unlock();
        condition_variable.notify_all();
    } else {
        std::unique_lock<std::mutex> l(forkToLock);
        condition_variable.wait(l, [this]() { return this->busy == false; });
        this->philosopherID = philosopherID;
        this->busy = busy;
        l.unlock();
    }
}

int Fork::getPhilosopherId() const {
    return philosopherID;
}




