#pragma once

#include <queue>
#include <functional>
#include <mutex>

class Queue {

private:
    std::queue<std::function<void()>> q;
    std::mutex m;

public:
    void Push(std::function<void()> f);

    std::function<void()> Pop();

    bool Empty();
};