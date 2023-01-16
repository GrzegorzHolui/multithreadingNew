#pragma once

#include "Fork.h"
#include "State.h"
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
    State state;

    //0 filozofuje, 1 je, 2 czeka
    enum State getState() const;


public:
    Philosopher(int id);

    ~Philosopher();

    double getPhilosopherTimer();

    void setAlive(bool alive);

    int getProgress();

    void setForkLeft(Fork *forkLeft);

    void setForkRight(Fork *forkRight);

    void life();
};