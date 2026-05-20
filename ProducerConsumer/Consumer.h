#pragma once

#include <memory>
#include "Queue.h"

class Consumer {

public:
    void Run(std::shared_ptr<Queue> queue);
};