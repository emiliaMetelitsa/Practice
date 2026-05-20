#pragma once

#include <memory>
#include "Queue.h"

class Producer {

private:
    int i = 0;

public:
    void Run(std::shared_ptr<Queue> queue);
};