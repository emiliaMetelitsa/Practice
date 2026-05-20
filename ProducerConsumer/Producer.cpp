#include "Producer.h"
#include <iostream>

void Producer::Run(std::shared_ptr<Queue> queue) {

    while (true) {

        int cur_i = i;

        queue->Push([cur_i]() {
            std::cout << "Iteration: " << cur_i << std::endl;
            });

        i++;
    }
}