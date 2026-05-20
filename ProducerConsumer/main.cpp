#include <iostream>
#include <queue>
#include <functional>
#include <chrono>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex m;

class Queue {

	std::mutex m;

public:

	std::queue<std::function<void()>> q;

	void Push(std::function<void()> f) {
		std::lock_guard<std::mutex> lock(m);
		q.push(f);
	}
	std::function<void()> Pop() {
		std::lock_guard<std::mutex> lock(m);
		auto op = q.front();
		q.pop();
		return op;
	}
};

class Producer {

	int i = 0;

public:

	void Run(std::shared_ptr<Queue> queue) {
		while (true) {
			int cur_i = i;
			queue->Push([cur_i]() {std::cout << "Iteration:" << cur_i << std::endl;});
			i++;
		}
	}
};

class Consumer {

public:

	void Run(std::shared_ptr<Queue> queue) {
		while (true) {
			if (!queue->q.empty()) {
				auto op = queue->Pop();
				op();
			}
		}
	}
};

int main() {
	std::shared_ptr<Queue> p = std::make_shared<Queue>();

	Producer producer;
	Consumer consumer;

	std::thread t1(&Producer::Run, &producer, p);
	std::thread t2(&Consumer::Run, &consumer, p);

	t1.join();
	t2.join();

	return 0;
}
