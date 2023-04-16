#ifndef _blocking_lock_h_
#define _blocking_lock_h_

#include "semaphore.h"

class BlockingLock {
    Semaphore sem{1};
public:
    Atomic<uint32_t> ref_count{0};

    BlockingLock() {
        
    }

    void lock() {
        sem.down();
    }

    void unlock() {
        sem.up();
    }

    bool isMine() { return true; }
};



#endif

