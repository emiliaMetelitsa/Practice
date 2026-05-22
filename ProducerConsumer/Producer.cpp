#include "Producer.h"
#include <iostream>

void Producer::Run(std::shared_ptr<Queue> queue) {

    int cur_i;

    while (true) {

        cur_i = i;

        queue->Push([cur_i]() {
            std::cout << "Iteration: " << cur_i << std::endl;
            });

        i++;
    }
}
