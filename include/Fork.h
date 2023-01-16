#ifndef MULTITHREADINGNEW_FORK_H
#define MULTITHREADINGNEW_FORK_H


#include <atomic>
#include <mutex>
#include <condition_variable>

class Fork {
private:
    int forkID;
//    std::atomic<bool> busy;
    bool busy;
    int philosopherID;

    std::mutex forkMutexToLock;
    std::condition_variable condition_variable;

public:
    void setForkId(int forkId);

    void setPhilosopherId(int philosopherId);

    Fork(int forkId);

    int getForkId() const;

    bool isBusy() const;

    int getPhilosopherId() const;

    const std::mutex &getForkMutexToLock() const;

    const std::condition_variable &getConditionVariable() const;

    void setBusy(bool busy, int philosopherID);


};


#endif //MULTITHREADINGNEW_FORK_H
