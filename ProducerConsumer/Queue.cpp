#include "Queue.h"

void Queue::Push(std::function<void()> f) {
    std::lock_guard<std::mutex> lock(m);
    q.push(f);
}

std::function<void()> Queue::Pop() {
    std::lock_guard<std::mutex> lock(m);

    auto op = q.front();
    q.pop();

    return op;
}

bool Queue::Empty() {
    std::lock_guard<std::mutex> lock(m);
    return q.empty();
}