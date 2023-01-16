#include "../include/Philosopher.h"
#include <unistd.h>
#include <ncurses.h>
#include <random>

using namespace std;


int myrand(int min, int max) {
    static mt19937 rnd(time(nullptr));
    return uniform_int_distribution<>(min, max)(rnd);
}

Philosopher::Philosopher(int philosopherID) {
    this->philosopherID = philosopherID;
    alive = true;
    state = 0;
    progress = 0;
}

Philosopher::~Philosopher() = default;


bool Philosopher::isAlive() {
    return alive;
}

void Philosopher::setAlive(bool alive) {
    this->alive = alive;
}

int Philosopher::getProgress() {
    return progress;
}

void Philosopher::setProgress(int progress) {
    this->progress = progress;
}

void Philosopher::setForkLeft(Fork *forkLeft) {
    this->forkLeft = forkLeft;
}

void Philosopher::setForkRight(Fork *forkRight) {
    this->forkRight = forkRight;
}

int Philosopher::getState() {
    return state;
}


int Philosopher::getPhilosopherId() const {
    return philosopherID;
}

void Philosopher::setState(int state) {
    this->state = state;
}

//0 filozofuje, 1 je, 2 czeka
void Philosopher::life() {
    while (alive) {
        int duration = myrand(50000, 200000);
        philosopherTimer = duration;

        state = 0;
        for (int i = 0; i < 50; i++) {
            usleep(philosopherTimer);
            progress++;
        }
        progress = 0;
        state = 2;
        takeForks();
        state = 1;
        for (int i = 0; i < 50; i++) {
            usleep(philosopherTimer);
            progress++;
        }
        progress = 0;
        releaseForks();
    }

    return;
}

void Philosopher::takeForks() {
    forkRight->setBusy(true, philosopherID);
    forkLeft->setBusy(true, philosopherID);
}

void Philosopher::releaseForks() {
    forkLeft->setBusy(false, philosopherID);
    forkRight->setBusy(false, philosopherID);
}

double Philosopher::getPhilosopherTimer() {
    return philosopherTimer;
}
