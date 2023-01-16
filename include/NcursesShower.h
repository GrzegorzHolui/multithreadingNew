#pragma once

#include "Philosopher.h"


class NcursesShower {
public:
    int amountOfPhilosophers;
    Philosopher **philosopher;
    Fork **fork;
    std::vector<Fork *> forks;

    NcursesShower(int amountOfPhilosophers, Philosopher **philosophers, std::vector<Fork *> fork);

    ~NcursesShower();


    void draw();

    void drawFrame();

    void drawPhilosophers();

    void drawPhilosophersDetails();

    void drawForks();

    void drawForksDetails();
};