#include "../include/Philosopher.h"
#include <unistd.h>
#include <random>

using namespace std;

int myrand(int min, int max) {
    static mt19937 rnd(time(nullptr));
    return uniform_int_distribution<>(min, max)(rnd);
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
        int duration = myrand(5000, 10000);
        philosopherTimer = duration;
        state = philosophizes;
        for (int i = 0; i < 50; i++) {
            usleep(philosopherTimer);
            progress++;
        }
        progress = 0;
        state = wait;
        forkRight->setBusy(true, philosopherID);
        forkLeft->setBusy(true, philosopherID);
        state = eat;
        for (int i = 0; i < 50; i++) {
            usleep(philosopherTimer);
            progress++;
        }
        progress = 0;
        forkLeft->setBusy(false, philosopherID);
        forkRight->setBusy(false, philosopherID);
    }
}

double Philosopher::getPhilosopherTimer() {
    return philosopherTimer;
}

State Philosopher::getState() const {
    return state;
}
