#include "../include/Fork.h"

Fork::Fork() : busy(false), philosopherID(-1) {}

bool Fork::isBusy() const {
    return busy;
}

int Fork::getPhilosopherId() const {
    return philosopherID;
}

void Fork::setBusy(bool busy, int philosopherID) {
    if (busy) {
        std::unique_lock<std::mutex> l(forkMutexToLock);
        condition_variable.wait(l, [this]() { return !this->busy; });
        this->philosopherID = philosopherID;
        this->busy = busy;
        l.unlock();
    } else {
        std::unique_lock<std::mutex> l(forkMutexToLock);
        this->philosopherID = -1;
        this->busy = busy;
        l.unlock();
        condition_variable.notify_all();
    }
}




