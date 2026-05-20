#include <memory>
#include <thread>
#include "Queue.h"
#include "Producer.h"
#include "Consumer.h"

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
