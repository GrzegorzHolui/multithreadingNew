
#include "../include/Philosopher.h"

#include "../include/NcursesShower.h"

#include <thread>
#include <iostream>


int main() {
    int amountOfPhilosophers
            = 5;
    cout << "Podaj liczbę wątków: ";
    cin >> amountOfPhilosophers;


    Philosopher **philosophers = new Philosopher *[amountOfPhilosophers];
//    Fork *fork[amountOfPhilosophers];
    std::vector<Fork *> forks;
    std::thread *threads = new thread[amountOfPhilosophers];

    for (int i = 0; i < amountOfPhilosophers; i++) {
        Fork *fork = new Fork(i);
        forks.push_back(std::move(fork));
    }

    for (int i = 0; i < amountOfPhilosophers; i++) {
        int leftFork = i;
        int rightFork = (i + 1) % amountOfPhilosophers;
        philosophers[i] = new Philosopher(i);
        philosophers[i]->setForkRight(forks.at(rightFork));
        philosophers[i]->setForkLeft(forks.at(leftFork));
        threads[i] = std::thread(&Philosopher::life, philosophers[i]);
    }

    NcursesShower ncursesShower = NcursesShower(amountOfPhilosophers, philosophers, forks);
    ncursesShower.draw();

    for (int i = 0; i < amountOfPhilosophers; i++) {
        threads[i].join();
    }
    return 0;
}