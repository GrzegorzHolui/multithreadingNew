
#include "../include/Philosopher.h"

#include "../include/NcursesShower.h"

#include <thread>
#include <iostream>


int main() {
    int amountOfPhilosophers = 5;
    std::cout << "Podaj liczbę wątków: ";
    std::cin >> amountOfPhilosophers;

    auto **philosophers = new Philosopher *[amountOfPhilosophers];
    std::vector<Fork *> forks;
    auto *threads = new std::thread[amountOfPhilosophers];

    for (int i = 0; i < amountOfPhilosophers; i++) {
        Fork *fork = new Fork();
        forks.push_back(std::move(fork));
    }

    for (int i = 0; i < amountOfPhilosophers; i++) {
        int leftFork = i;
        int rightFork = (i + 1) % amountOfPhilosophers;
        philosophers[i] = new Philosopher(i);
        philosophers[i]->setForkLeft(forks.at(leftFork));
        philosophers[i]->setForkRight(forks.at(rightFork));
        threads[i] = std::thread(&Philosopher::life, philosophers[i]);
    }

    NcursesShower ncursesShower = NcursesShower(amountOfPhilosophers, philosophers, forks);
    ncursesShower.draw();

    for (int i = 0; i < amountOfPhilosophers; i++) {
        threads[i].join();
    }
    return 0;
}