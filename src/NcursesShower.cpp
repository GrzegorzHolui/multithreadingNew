#include "../include/NcursesShower.h"
#include "ncurses.h"

using namespace std;

NcursesShower::NcursesShower(int amountOfPhilosophers, Philosopher **philosopher, vector<Fork *> forks) {
    this->amountOfPhilosophers = amountOfPhilosophers;
    this->philosopher = philosopher;
    this->forks = forks;

    initscr();
    noecho();
    curs_set(0);
}

NcursesShower::~NcursesShower() {
    endwin();
}


void NcursesShower::draw() {
    int c;
    nodelay(stdscr, TRUE);

    while ((c = getch()) != 27) {
        drawFrame();
        drawPhilosophers();
        drawForks();
        refresh();
    }

    for (int i = 0; i < amountOfPhilosophers; i++)
        philosopher[i]->setAlive(false);

    endwin();
}

void NcursesShower::drawFrame() {
    move(1, 37);
    printw("Filozofowie");
    move(1, 66);
    printw("Widelce");

    for (int i = 0; i < amountOfPhilosophers; i++) {
        move(3 + i * 4, 27);
        addch(i + '0');
        attron(COLOR_PAIR((i % 6) + 1));
        move(3 + i * 4, 30);
        addch('[');
        move(3 + i * 4, 51);
        addch(']');
        attroff(COLOR_PAIR((i % 6) + 1));
        attron(COLOR_PAIR(7));
        move(5 + i * 4, 59);
        addch('W');
        addch(i + '0');
        printw(" Wolny");
        attroff(COLOR_PAIR(7));
    }

    move(8, 0);
    printw("'$'  jedzenie");
    move(9, 0);
    printw("'-'  filozofowanie");
}

void NcursesShower::drawPhilosophers() {
    for (int i = 0; i < amountOfPhilosophers; i++) {
        attron(COLOR_PAIR((i % 6) + 1));
        int progress = philosopher[i]->getProgress();
        State state = philosopher[i]->getState();
        double timer = philosopher[i]->getPhilosopherTimer();
        char c;
        std::string printWait = "--------Czeka-------";
        if (state == philosophizes) {
            c = '-';
        } else {
            c = '$';
        }
        if (state == wait) {
            move(3 + i * 4, 31);
            printw("----Czeka---");
            move(3 + i * 4, 52);
            printw("%1.2f%s", 0.00, "s");
        } else {
            for (int j = 0; j < 20; j++) {
                move(3 + i * 4, 31 + j);
                if (progress > j) {
                    addch(c);
                } else {
                    addch(' ');
                }
                move(3 + i * 4, 52);
                double timeLeft = ((21 - progress) * timer) / 1000000;
                printw("%1.2f%s", timeLeft, "s");
            }
        }
        attroff(COLOR_PAIR((i % 6) + 1));
    }
}

void NcursesShower::drawForks() {
    for (int i = 0; i < amountOfPhilosophers; i++) {
        if (forks[i]->isBusy()) {
            int philID = forks[i]->getPhilosopherId();
            attron(COLOR_PAIR(7));
            move(5 + i * 4, 59);
            addch('W');
            addch(i + '0');
            printw("  zabrany przez: ");
            addch('F');
            addch(philID + '0');
            attroff(COLOR_PAIR(7));
        } else {
            attron(COLOR_PAIR(7));
            move(5 + i * 4, 59);
            addch('W');
            addch(i + '0');
            printw(" Wolny             ");
            attroff(COLOR_PAIR(7));
        }
    }
}