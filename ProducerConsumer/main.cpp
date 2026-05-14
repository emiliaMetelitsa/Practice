#include <iostream>
#include <queue>
#include <functional>
#include <chrono>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex m;

class DataFlow {
	std::queue<std::function<void()>> q;
	int i = 0;
public:

	void Producer(){
		while (true) {
			std::lock_guard<std::mutex> lock(m);
			int cur_i = i;
			q.push([cur_i]() {std::cout << "Iteration: " << cur_i << std::endl;});
			i++;
		}
	}

	void Consumer(){
		while (true) {
			std::lock_guard<std::mutex> lock(m);
			if (!q.empty()) {
				auto op = q.front();
				op();
				q.pop();
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
		}
	}
};

int main() {
	DataFlow test;

	std::thread t1(&DataFlow::Producer, std::ref(test));
	std::thread t2(&DataFlow::Consumer, std::ref(test));

	t1.join();
	t2.join();

	return 0;
}