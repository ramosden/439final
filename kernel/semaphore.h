#pragma once

#include "stdint.h"
#include "atomic.h"
#include "queue.h"
#include "threads.h"

class Semaphore {

    volatile uint64_t count;
    ISL spin{};
    Queue<gheith::TCB, NoLock> waiting{};

    friend class PostDownWork;

public:
    Atomic<uint32_t> ref_count{0};
    Semaphore(uint32_t count): count(count) {}

    void down();
    void up();

};
