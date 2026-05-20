#include <iostream>
#include <queue>
#include <functional>
#include <chrono>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex m;

class DataFlow {

public:
	std::queue<std::function<void()>> q;
	std::mutex m;
};

class Producer {

	int i = 0;

public:
	void Run(std::shared_ptr<DataFlow> dataflow) {
		while (true) {
			std::lock_guard<std::mutex> lock(dataflow->m);
			int cur_i = i;
			dataflow->q.push([cur_i]() {std::cout << "Iteration: " << cur_i << std::endl;});
			i++;
		}
	}
};

class Consumer {

public:
	void Run(std::shared_ptr<DataFlow> dataflow) {
		while (true) {
			std::lock_guard<std::mutex> lock(dataflow->m);
			if (!dataflow->q.empty()) {
				auto op = dataflow->q.front();
				op();
				dataflow->q.pop();
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
		}
	}
};

int main() {
	std::shared_ptr<DataFlow> p = std::make_shared<DataFlow>();

	Producer producer;
	Consumer consumer;

	std::thread t1(&Producer::Run, &producer, p);
	std::thread t2(&Consumer::Run, &consumer, p);

	t1.join();
	t2.join();

	return 0;
}
