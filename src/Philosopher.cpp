#include "../include/Philosopher.h"
#include <unistd.h>
#include <random>


int myrand(int min, int max) {
    static std::mt19937 rnd(time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

Philosopher::Philosopher(int philosopherID) {
    this->philosopherID = philosopherID;
    alive = true;
    state = philosophizes;
    progress = 0;
}

void Philosopher::setAlive(bool alive) {
    this->alive = alive;
}

int Philosopher::getProgress() {
    return progress;
}

void Philosopher::setForkLeft(Fork *forkLeft) {
    this->forkLeft = forkLeft;
}

void Philosopher::setForkRight(Fork *forkRight) {
    this->forkRight = forkRight;
}


void Philosopher::life() {
    while (alive) {
        int duration = myrand(50000, 100000);
        philosopherTimer = duration;
        state = philosophizes;
        for (int i = 0; i < 21; i++) {
            usleep(philosopherTimer);
            progress++;
        }
        progress = 0;
        state = wait;
        forkLeft->setBusy(true, philosopherID);
        forkRight->setBusy(true, philosopherID);
        state = eat;
        for (int i = 0; i < 21; i++) {
            usleep(philosopherTimer);
            progress++;
        }
        progress = 0;
        forkRight->setBusy(false, philosopherID);
        forkLeft->setBusy(false, philosopherID);
    }
}

double Philosopher::getPhilosopherTimer() {
    return philosopherTimer;
}

State Philosopher::getState() const {
    return state;
}
