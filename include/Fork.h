#ifndef MULTITHREADINGNEW_FORK_H
#define MULTITHREADINGNEW_FORK_H


#include <atomic>
#include <mutex>
#include <condition_variable>

class Fork {
private:

    bool busy;
    int philosopherID;

    std::mutex forkMutexToLock;
    std::condition_variable condition_variable;

public:


    bool isBusy() const;

    int getPhilosopherId() const;

    void setBusy(bool busy, int philosopherID);


    Fork();
};


#endif //MULTITHREADINGNEW_FORK_H
