#pragma once

#include "Fork.h"
#include <random>

class Philosopher {
public:
    std::mt19937 rng{std::random_device{}()};
    int philosopherID;
    double philosopherTimer;
    bool alive;
    int progress;
    Fork *forkLeft;
    Fork *forkRight;
    //0 filozofuje, 1 je, 2 czeka
    std::atomic<int> state;

public:
    Philosopher(int id);

    ~Philosopher();

    double getPhilosopherTimer();

    void setAlive(bool alive);

    int getProgress();

    void setForkLeft(Fork *forkLeft);

    void setForkRight(Fork *forkRight);

    int getState();

    void life();
};