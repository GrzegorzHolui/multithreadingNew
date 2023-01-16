#include "../include/Fork.h"

Fork::Fork(int forkId) : forkID(forkId), busy(false), philosopherID(-1) {}

int Fork::getForkId() const {
    return forkID;
}

bool Fork::isBusy() const {
    return busy;
}

int Fork::getPhilosopherId() const {
    return philosopherID;
}

const std::mutex &Fork::getForkMutexToLock() const {
    return forkMutexToLock;
}

const std::condition_variable &Fork::getConditionVariable() const {
    return condition_variable;
}

void Fork::setForkId(int forkId) {
    forkID = forkId;
}

void Fork::setBusy(bool busy, int philosopherID) {
    if (busy) {
        std::unique_lock<std::mutex> l(forkMutexToLock);
        condition_variable.wait(l, [this]() { return this->busy == false; });
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

void Fork::setPhilosopherId(int philosopherId) {
    this->philosopherID = philosopherId;
}



