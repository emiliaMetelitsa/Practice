#include "Consumer.h"

void Consumer::Run(std::shared_ptr<Queue> queue) {

    while (true) {

        if (!queue->Empty()) {

            auto op = queue->Pop();
            op();
        }
    }
}