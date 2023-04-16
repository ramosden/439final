#ifndef _barrier_h_
#define _barrier_h_

#include "atomic.h"
#include "semaphore.h"

class Barrier {
    Atomic<uint32_t> count;
    Semaphore sem{0};

public:
    Atomic<uint32_t> ref_count{0};

    Barrier(uint32_t count): count(count) {
    }

    Barrier(const Barrier&) = delete;
    
    void sync() {
        auto t = count.add_fetch(-1);
        if (t == 0) {
            sem.up();
        } else {
            sem.down();
            sem.up();
        }
    }
};

// From the little book of semaphores
class ReusableBarrier {
    uint32_t n;
    uint32_t count = 0;
    Semaphore lock{1};
    Semaphore t1{0};
    Semaphore t2{0};
public:
    Atomic<uint32_t> ref_count{0};

    ReusableBarrier(uint32_t n): n(n) {
    }

    ReusableBarrier(const ReusableBarrier&) = delete;

    void sync() {
        // phase 1
        lock.down();
        count += 1;
        if (count == n) {
            for (uint32_t i=0; i<n; i++) {
                t1.up();
            }
        }
        lock.up();
        t1.down();

        // phase 2
        lock.down();
        count -= 1;
        if (count == 0) {
            for (uint32_t i=0; i < n; i++) {
                t2.up();
            }
        }
        lock.up();
        t2.down();
    }
};
        
        
        

#endif

